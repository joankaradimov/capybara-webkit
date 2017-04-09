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

  private:
    void writeResponse(Response *response);

    QTcpSocket *m_socket;
    CommandParser *m_commandParser;
    CommandFactory *m_commandFactory;
    bool m_pageSuccess;
};
