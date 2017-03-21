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
  m_command->setParent(this);

  m_manager = manager;
  m_timer = new QTimer(this);
  m_timer->setSingleShot(true);
  connect(m_timer, SIGNAL(timeout()), this, SLOT(commandTimeout()));
  connect(m_manager, SIGNAL(loadStarted()), this, SLOT(startTimeout()));
}

void TimeoutCommand::start() {
  QApplication::processEvents();
  if (m_manager->isLoading()) {
    m_manager->logger() << "waiting for load to finish";
    connect(m_manager, SIGNAL(pageFinished(bool)), this, SLOT(pendingLoadFinished(bool)));
    startTimeout();
  } else {
    startCommand();
  }
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
    emit finished(response);
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
    emit finished(new Response(false, message, this));
  }
}

void TimeoutCommand::commandTimeout() {
  disconnect(m_manager, SIGNAL(loadStarted()), this, SLOT(startTimeout()));
  disconnect(m_manager, SIGNAL(pageFinished(bool)), this, SLOT(pendingLoadFinished(bool)));
  m_timedOut = true;
  m_manager->currentPage()->triggerAction(QWebPage::Stop);
  QString message = QString("Request timed out after %1 second(s)").arg(m_manager->getTimeout());
  emit finished(new Response(false, new ErrorMessage("TimeoutError", message), this));
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
	  emit finished(m_pendingResponse);
	} else {
	  QString message = m_manager->currentPage()->failureString();
	  emit finished(new Response(false, new ErrorMessage(message), this));
	}
      }
    }
  }
}

void TimeoutCommand::pageLoadingFromCommand() {
  m_manager->logger() << m_command->toString() << "started page load";
  m_pageLoadingFromCommand = true;
}
