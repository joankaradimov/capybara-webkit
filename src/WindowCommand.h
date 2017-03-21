#ifndef WINDOW_COMMAND_H
#define WINDOW_COMMAND_H

#include "SocketCommand.h"

class WindowCommand : public SocketCommand {
  Q_OBJECT

  public:
    WindowCommand(WebPageManager *, QStringList &arguments, QObject *parent = 0);
    Response* start();

  protected:
    virtual Response* windowFound(WebPage *) = 0;

  private:
    Response* findWindow(QString);
    Response* windowNotFound();
};

#endif
