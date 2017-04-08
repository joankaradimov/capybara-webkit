#include <QObject>

class QTcpServer;
class WebPageManager;

class Server : public QObject {
  Q_OBJECT

  public:
    Server(QObject *parent);
    bool start();
    quint16 server_port() const;
    WebPageManager* manager();

  public slots:
    void handleConnection();

  private:
    QTcpServer *m_tcp_server;
    WebPageManager* m_manager;
};

