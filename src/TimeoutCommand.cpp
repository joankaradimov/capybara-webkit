#include "TimeoutCommand.h"
#include "SocketCommand.h"
#include "WebPageManager.h"
#include "WebPage.h"
#include "ErrorMessage.h"
#include <QTimer>
#include <QApplication>

TimeoutCommand::TimeoutCommand(SocketCommand *command, WebPageManager *manager) {
  m_command = command;
  m_pageLoadingFromCommand = false;
  m_timedOut = false;
  m_pendingResponse = NULL;
  m_response = NULL;
  m_command->setParent(this);

  m_manager = manager;
  m_timer = new QTimer(this);
  m_timer->setSingleShot(true);
  connect(m_timer, SIGNAL(timeout()), this, SLOT(commandTimeout()));
  connect(m_manager, SIGNAL(loadStarted()), this, SLOT(startTimeout()));
}

Response* TimeoutCommand::execute() {
  QApplication::processEvents();
  if (m_manager->isLoading()) {
    m_manager->logger() << "waiting for load to finish";
    connect(m_manager, SIGNAL(pageFinished(bool)), this, SLOT(pendingLoadFinished(bool)));
    startTimeout();
  } else {
    startCommand();
  }

  if (m_response == NULL) {
    m_wait_loop.exec();
  }
  return m_response;
}

void TimeoutCommand::startCommand() {
  connect(m_manager, SIGNAL(loadStarted()), this, SLOT(pageLoadingFromCommand()));
  connect(m_manager, SIGNAL(pageFinished(bool)), this, SLOT(pendingLoadFinishedForPageLoad(bool)));

  m_manager->logger() << "Started" << m_command->toString();
  Response* response = m_command->start();
  m_manager->logger() << "Finished" << m_command->toString() << "with response" << response->toString();

  disconnect(m_manager, SIGNAL(loadStarted()), this, SLOT(pageLoadingFromCommand()));

  if (m_pageLoadingFromCommand) {
    m_pendingResponse = response;
  } else {
    disconnect(m_timer, SIGNAL(timeout()), this, SLOT(commandTimeout()));
    disconnect(m_manager, SIGNAL(loadStarted()), this, SLOT(startTimeout()));
    m_response = response;
    m_wait_loop.quit();
  }
}

void TimeoutCommand::startTimeout() {
  int timeout = m_manager->getTimeout();
  if (timeout > 0) {
    m_timer->start(timeout * 1000);
  }
}

void TimeoutCommand::pendingLoadFinished(bool success) {
  disconnect(m_manager, SIGNAL(pageFinished(bool)), this, SLOT(pendingLoadFinished(bool)));
  if (success) {
    startCommand();
  } else {
    disconnect(m_timer, SIGNAL(timeout()), this, SLOT(commandTimeout()));
    disconnect(m_manager, SIGNAL(loadStarted()), this, SLOT(startTimeout()));
    ErrorMessage* message = new ErrorMessage(m_manager->currentPage()->failureString());
    m_response = new Response(false, message, this);
    m_wait_loop.quit();
  }
}

void TimeoutCommand::commandTimeout() {
  disconnect(m_manager, SIGNAL(loadStarted()), this, SLOT(startTimeout()));
  disconnect(m_manager, SIGNAL(pageFinished(bool)), this, SLOT(pendingLoadFinished(bool)));
  m_timedOut = true;
  m_manager->currentPage()->triggerAction(QWebPage::Stop);
  QString message = QString("Request timed out after %1 second(s)").arg(m_manager->getTimeout());
  m_response = new Response(false, new ErrorMessage("TimeoutError", message), this);
  m_wait_loop.quit();
}

void TimeoutCommand::pendingLoadFinishedForPageLoad(bool success) {
  if (m_pageLoadingFromCommand) {
    m_pageLoadingFromCommand = false;
    if (m_pendingResponse) {
      m_manager->logger() << "Page load from command finished";
      if (!m_timedOut) {
        disconnect(m_timer, SIGNAL(timeout()), this, SLOT(commandTimeout()));
        disconnect(m_manager, SIGNAL(loadStarted()), this, SLOT(startTimeout()));
	if (success) {
	  m_response = m_pendingResponse;
	} else {
	  QString message = m_manager->currentPage()->failureString();
	  m_response = new Response(false, new ErrorMessage(message), this);
	}
	m_wait_loop.quit();
      }
    }
  }
}

void TimeoutCommand::pageLoadingFromCommand() {
  m_manager->logger() << m_command->toString() << "started page load";
  m_pageLoadingFromCommand = true;
}
