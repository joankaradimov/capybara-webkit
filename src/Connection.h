#include <QObject>

class QTcpSocket;
class WebPage;
class SocketCommand;
class Response;
class CommandParser;
class CommandFactory;
class WebPageManager;

class Connection : public QObject {
  Q_OBJECT

  public:
    Connection(QTcpSocket *socket, WebPageManager *manager, QObject *parent = 0);

  public slots:
    void commandReady(SocketCommand *command);
    void pendingLoadFinished(bool success);

  private:
    void startCommand(SocketCommand *);
    void writeResponse(Response *response);

    QTcpSocket *m_socket;
    WebPageManager *m_manager;
    CommandParser *m_commandParser;
    CommandFactory *m_commandFactory;
    bool m_pageSuccess;
};
