#include "Command.h"
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
class TimeoutCommand : public Command {
  Q_OBJECT
 
  public:
   TimeoutCommand(Command *command, WebPageManager *page, QObject *parent = 0);
  virtual void start();

  public slots:
    void commandTimeout();
    void commandFinished(Response *response);
    void pageLoadingFromCommand();
    void pendingLoadFinished(bool);
    void pageLoadingFromCommandForPageLoad();
    void pendingLoadFinishedForPageLoad(bool success);
    void commandFinishedForPageLoad(Response *response);

  protected:
    void startCommand();
    void startTimeout();

  private:
    WebPageManager *m_manager;
    QTimer *m_timer;
    Command *m_command;
    Response *m_pendingResponse;
    bool m_pageLoadingFromCommand;

  signals:
    void finishedForPageLoad(Response *response);
};
