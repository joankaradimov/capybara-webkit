#include "TimeoutCommand.h"
#include "SocketCommand.h"
#include "WebPageManager.h"
#include "WebPage.h"
#include "ErrorMessage.h"
#include <QTimer>
#include <QApplication>

TimeoutCommand::TimeoutCommand(SocketCommand *command, WebPageManager *manager, QObject *parent) : Command(parent) {
  m_command = command;
  m_pageLoadingFromCommand = false;
  m_pendingResponse = NULL;
  m_command->setParent(this);

  m_manager = manager;
  m_timer = new QTimer(this);
  m_timer->setSingleShot(true);
  connect(m_timer, SIGNAL(timeout()), this, SLOT(commandTimeout()));
  connect(m_manager, SIGNAL(loadStarted()), this, SLOT(pageLoadingFromCommand()));
}

void TimeoutCommand::start() {
  QApplication::processEvents();
  if (m_manager->isLoading()) {
    m_manager->logger() << this->toString() << "waiting for load to finish";
    connect(m_manager, SIGNAL(pageFinished(bool)), this, SLOT(pendingLoadFinished(bool)));
    startTimeout();
  } else {
    startCommand();
  }
}

void TimeoutCommand::startCommand() {
  connect(this, SIGNAL(finishedForPageLoad(Response *)), this, SLOT(commandFinished(Response *)));

  m_manager->logger() << "Started" << m_command->toString();
  connect(m_command, SIGNAL(finished(Response *)), this, SLOT(commandFinishedForPageLoad(Response *)));
  connect(m_manager, SIGNAL(loadStarted()), this, SLOT(pageLoadingFromCommandForPageLoad()));
  connect(m_manager, SIGNAL(pageFinished(bool)), this, SLOT(pendingLoadFinishedForPageLoad(bool)));
  m_command->start();
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
    disconnect(m_manager, SIGNAL(loadStarted()), this, SLOT(pageLoadingFromCommand()));
    finish(false, new ErrorMessage(m_manager->currentPage()->failureString()));
  }
}

void TimeoutCommand::pageLoadingFromCommand() {
  startTimeout();
}

void TimeoutCommand::commandTimeout() {
  disconnect(m_manager, SIGNAL(loadStarted()), this, SLOT(pageLoadingFromCommand()));
  disconnect(m_manager, SIGNAL(pageFinished(bool)), this, SLOT(pendingLoadFinished(bool)));
  disconnect(this, SIGNAL(finishedForPageLoad(Response *)), this, SLOT(commandFinished(Response *)));
  m_manager->currentPage()->triggerAction(QWebPage::Stop);
  QString message = QString("Request timed out after %1 second(s)").arg(m_manager->getTimeout());
  finish(false, new ErrorMessage("TimeoutError", message));
}

void TimeoutCommand::commandFinished(Response *response) {
  disconnect(m_timer, SIGNAL(timeout()), this, SLOT(commandTimeout()));
  disconnect(m_manager, SIGNAL(loadStarted()), this, SLOT(pageLoadingFromCommand()));
  emit finished(response);
}

void TimeoutCommand::pendingLoadFinishedForPageLoad(bool success) {
  if (m_pageLoadingFromCommand) {
    m_pageLoadingFromCommand = false;
    if (m_pendingResponse) {
      m_manager->logger() << "Page load from command finished";
      if (success) {
        emit finishedForPageLoad(m_pendingResponse);
      } else {
        QString message = m_manager->currentPage()->failureString();
        emit finishedForPageLoad(new Response(false, new ErrorMessage(message), this));
      }
    }
  }
}

void TimeoutCommand::pageLoadingFromCommandForPageLoad() {
  m_manager->logger() << m_command->toString() << "started page load";
  m_pageLoadingFromCommand = true;
}

void TimeoutCommand::commandFinishedForPageLoad(Response *response) {
  disconnect(m_manager, SIGNAL(loadStarted()), this, SLOT(pageLoadingFromCommandForPageLoad()));
  m_manager->logger() << "Finished" << m_command->toString() << "with response" << response->toString();

  if (m_pageLoadingFromCommand) {
    m_pendingResponse = response;
  } else {
    emit finishedForPageLoad(response);
  }
}
