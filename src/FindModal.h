#include "SocketCommand.h"

class FindModal : public SocketCommand {
  Q_OBJECT

  public:
    FindModal(WebPageManager *, QStringList &arguments, QObject *parent = 0);
    virtual Response* start();

  public slots:
    void handleModalReady();

  private:
    Response* buildModalResponse();

    QTimer *m_timer;
};
