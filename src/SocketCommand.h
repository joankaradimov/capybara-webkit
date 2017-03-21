#ifndef SOCKET_COMMAND_H
#define SOCKET_COMMAND_H

#include <QObject>
#include <QStringList>
#include "Response.h"

class WebPage;
class WebPageManager;
class Response;
class ErrorMessage;

class SocketCommand : public QObject {
  Q_OBJECT

  public:
    SocketCommand(WebPageManager *, QStringList &arguments, QObject *parent = 0);
    virtual Response* start() = 0;
    virtual QString toString() const;

  protected:
    WebPage *page() const;
    const QStringList &arguments() const;
    WebPageManager *manager() const;

    Response* finish(bool success);
    Response* finish(bool success, QString message);
    Response* finish(bool success, QByteArray message);
    Response* finish(bool success, ErrorMessage *message);

  private:
    QStringList m_arguments;
    WebPageManager *m_manager;

};

#endif
