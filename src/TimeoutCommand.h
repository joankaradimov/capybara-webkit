#include "SocketCommand.h"
#include <QObject>
#include <QStringList>

class Response;
class WebPageManager;
class PageLoadingCommand;
class QTimer;

/* Decorates a command with a timeout.
 *
 * If the timeout, using a QTimer is reached before
 * the command is finished, the load page load will
 * be stopped and failure response will be issued.
 *
 */
class TimeoutCommand : public QObject {
  Q_OBJECT
 
  public:
    TimeoutCommand(SocketCommand *command, WebPageManager *page);
    virtual Response* start();

  public slots:
    void commandTimeout();
    void pageLoadingFromCommand();
    void startTimeout();
    void pendingLoadFinished(bool);
    void pendingLoadFinishedForPageLoad(bool success);

  protected:
    void startCommand();

  private:
    WebPageManager *m_manager;
    QTimer *m_timer;
    SocketCommand *m_command;
    Response *m_pendingResponse;
    Response *m_response;
    bool m_pageLoadingFromCommand;
    bool m_timedOut;
    QEventLoop m_wait_loop;

  signals:
    void finished(Response *response);
};
