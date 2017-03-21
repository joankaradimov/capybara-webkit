#include "SocketCommand.h"

class QWebFrame;

class FrameFocus : public SocketCommand {
  Q_OBJECT

  public:
    FrameFocus(WebPageManager *, QStringList &arguments, QObject *parent = 0);
    virtual Response* start();

  private:
    void findFrames();

    Response* focusParent();

    Response* focusIndex(int index);
    bool isFrameAtIndex(int index);

    Response* focusId(QString id);

    Response* success();
    Response* frameNotFound();

    QList<QWebFrame *> frames;
};

