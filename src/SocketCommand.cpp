#include "SocketCommand.h"
#include "WebPage.h"
#include "WebPageManager.h"
#include "ErrorMessage.h"

SocketCommand::SocketCommand(WebPageManager *manager, QStringList &arguments, QObject *parent) : QObject(parent) {
  m_manager = manager;
  m_arguments = arguments;
}

Response* SocketCommand::execute() {
  if (m_manager->currentPage()->isLastLoadSuccess()) {
    m_pageLoadingFromCommand = false;
    m_timedOut = false;
    m_pendingResponse = NULL;
    m_response = NULL;
    m_timer = new QTimer(this);

    m_manager->processEvents();
    startTimeout();
    if (m_manager->isLoading()) {
      m_manager->logger() << "waiting for load to finish";
      connect(m_manager, SIGNAL(pageFinished(bool)), this, SLOT(pendingLoadFinished(bool)));
      m_wait_loop.exec();
      disconnect(m_manager, SIGNAL(pageFinished(bool)), this, SLOT(pendingLoadFinished(bool)));
    }

    if (m_response == NULL) {
      connect(m_manager, SIGNAL(pageFinished(bool)), this, SLOT(pendingLoadFinishedForPageLoad(bool)));

      connect(m_manager, SIGNAL(loadStarted()), this, SLOT(pageLoadingFromCommand()));

      m_manager->logger() << "Started" << toString();
      Response* response = start();
      m_manager->logger() << "Finished" << toString() << "with response" << response->toString();

      disconnect(m_manager, SIGNAL(loadStarted()), this, SLOT(pageLoadingFromCommand()));

      if (m_pageLoadingFromCommand) {
	m_pendingResponse = response;
      } else {
	disconnect(m_timer, SIGNAL(timeout()), this, SLOT(commandTimeout()));
	m_response = response;
      }
    }

    if (m_response == NULL) {
      m_wait_loop.exec();
    }
  } else {
    QString message = m_manager->currentPage()->failureString();
    m_response = new Response(false, new ErrorMessage(message));
  }

  m_manager->currentPage()->resetLastLoadSuccess();
  return m_response;
}

WebPage *SocketCommand::page() const {
  return m_manager->currentPage();
}

const QStringList &SocketCommand::arguments() const {
  return m_arguments;
}

WebPageManager *SocketCommand::manager() const {
  return m_manager;
}

QString SocketCommand::toString() const {
  QString result;
  QTextStream(&result) << metaObject()->className() << QString("(") << m_arguments.join(", ") << QString(")");
  return result;
}

Response* SocketCommand::finish(bool success) {
  return new Response(success, this);
}

Response* SocketCommand::finish(bool success, QString message) {
  return new Response(success, message, this);
}

Response* SocketCommand::finish(bool success, QByteArray message) {
  return new Response(success, message, this);
}

Response* SocketCommand::finish(bool success, ErrorMessage *message) {
  return new Response(success, message, this);
}

void SocketCommand::startTimeout() {
  m_timer->setSingleShot(true);
  connect(m_timer, SIGNAL(timeout()), this, SLOT(commandTimeout()));

  int timeout = m_manager->getTimeout();
  if (timeout > 0) {
    m_timer->start(timeout * 1000);
  }
}

void SocketCommand::pendingLoadFinished(bool success) {
  if (!success) {
    disconnect(m_timer, SIGNAL(timeout()), this, SLOT(commandTimeout()));
    ErrorMessage* message = new ErrorMessage(m_manager->currentPage()->failureString());
    m_response = new Response(false, message, this);
  }
  m_wait_loop.quit();
}

void SocketCommand::commandTimeout() {
  m_timedOut = true;
  m_manager->currentPage()->triggerAction(QWebPage::Stop);
  QString message = QString("Request timed out after %1 second(s)").arg(m_manager->getTimeout());
  m_response = new Response(false, new ErrorMessage("TimeoutError", message), this);
  m_wait_loop.quit();
}

void SocketCommand::pendingLoadFinishedForPageLoad(bool success) {
  if (m_pageLoadingFromCommand) {
    m_pageLoadingFromCommand = false;
    if (m_pendingResponse) {
      m_manager->logger() << "Page load from command finished";
      if (!m_timedOut) {
        disconnect(m_timer, SIGNAL(timeout()), this, SLOT(commandTimeout()));
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

void SocketCommand::pageLoadingFromCommand() {
  m_manager->logger() << toString() << "started page load";
  m_pageLoadingFromCommand = true;
}
