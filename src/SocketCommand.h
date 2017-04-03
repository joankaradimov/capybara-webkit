#ifndef SOCKET_COMMAND_H
#define SOCKET_COMMAND_H

#include <QObject>
#include <QStringList>
#include "Response.h"

class WebPage;
class WebPageManager;
class Response;
class TimeoutCommand;
class ErrorMessage;

class SocketCommand : public QObject {
  Q_OBJECT

  public:
    SocketCommand(WebPageManager *, QStringList &arguments, QObject *parent = 0);
    Response* execute();
    virtual QString toString() const;

  protected:
    WebPage *page() const;
    const QStringList &arguments() const;
    WebPageManager *manager() const;
    virtual Response* start() = 0;
    void startCommand();

    Response* finish(bool success);
    Response* finish(bool success, QString message);
    Response* finish(bool success, QByteArray message);
    Response* finish(bool success, ErrorMessage *message);

    Response *m_response;
    QEventLoop m_wait_loop;

  private:
    QStringList m_arguments;
    WebPageManager *m_manager;
    QTimer *m_timer;
    Response *m_pendingResponse;
    bool m_pageLoadingFromCommand;
    bool m_timedOut;

  public slots:
    void commandTimeout();
    void pageLoadingFromCommand();
    void startTimeout();
    void pendingLoadFinished(bool);
    void pendingLoadFinishedForPageLoad(bool success);
};

#endif
