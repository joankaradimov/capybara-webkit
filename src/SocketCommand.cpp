#include "SocketCommand.h"
#include "TimeoutCommand.h"
#include "WebPage.h"
#include "WebPageManager.h"
#include "ErrorMessage.h"

SocketCommand::SocketCommand(WebPageManager *manager, QStringList &arguments, QObject *parent) : QObject(parent) {
  m_manager = manager;
  m_arguments = arguments;
}

Response* SocketCommand::execute() {
  m_timeoutCommand = new TimeoutCommand(this, m_manager);
  return m_timeoutCommand->execute();
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
