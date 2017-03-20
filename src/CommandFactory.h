#include <QObject>

class SocketCommand;
class WebPage;
class WebPageManager;

class CommandFactory : public QObject {
  Q_OBJECT

  public:
    CommandFactory(WebPageManager *, QObject *parent = 0);
    SocketCommand *createCommand(const char *name, QStringList &arguments);

  private:
    WebPageManager *m_manager;
};

