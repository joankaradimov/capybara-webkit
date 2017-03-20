#include "SocketCommand.h"

class NullCommand : public SocketCommand {
  Q_OBJECT

  public:
    NullCommand(WebPageManager* manager, QString name, QStringList &arguments, QObject *parent = 0);
    virtual void start();

  private:
    QString m_name;
};
