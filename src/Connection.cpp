#include "Connection.h"
#include "WebPage.h"
#include "WebPageManager.h"
#include "CommandParser.h"
#include "CommandFactory.h"
#include "SocketCommand.h"
#include "ErrorMessage.h"

#include <QTcpSocket>

Connection::Connection(QTcpSocket *socket, WebPageManager *manager, QObject *parent) :
    QObject(parent) {
  m_socket = socket;
  m_manager = manager;
  m_commandFactory = new CommandFactory(m_manager, this);
  m_commandParser = new CommandParser(socket, m_commandFactory, this);
  connect(m_socket, SIGNAL(readyRead()), m_commandParser, SLOT(checkNext()));
  connect(m_commandParser, SIGNAL(commandReady(SocketCommand *)), this, SLOT(commandReady(SocketCommand *)));
}

void Connection::commandReady(SocketCommand *command) {
  m_manager->logger() << "Received" << command->toString();

  Response* response = command->execute();
  writeResponse(response);

  m_manager->logger() << "Wrote response" << response->isSuccess() << response->message();
}

void Connection::writeResponse(Response *response) {
  if (response->isSuccess())
    m_socket->write("ok\n");
  else
    m_socket->write("failure\n");

  QByteArray messageUtf8 = response->message();
  QString messageLength = QString::number(messageUtf8.size()) + "\n";
  m_socket->write(messageLength.toLatin1());
  m_socket->write(messageUtf8);
}
