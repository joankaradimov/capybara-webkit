#include "SocketCommand.h"
#include "WebPage.h"
#include "WebPageManager.h"
#include "ErrorMessage.h"

SocketCommand::SocketCommand(WebPageManager *manager, QStringList &arguments, QObject *parent) : QObject(parent) {
  m_manager = manager;
  m_arguments = arguments;
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

void SocketCommand::finish(bool success) {
  emit finished(new Response(success, this));
}

void SocketCommand::finish(bool success, QString message) {
  emit finished(new Response(success, message, this));
}

void SocketCommand::finish(bool success, QByteArray message) {
  emit finished(new Response(success, message, this));
}

void SocketCommand::finish(bool success, ErrorMessage *message) {
  emit finished(new Response(success, message, this));
}
