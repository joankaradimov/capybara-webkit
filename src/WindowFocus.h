#include "WindowCommand.h"

class WindowFocus : public WindowCommand {
  Q_OBJECT

  public:
    WindowFocus(WebPageManager *, QStringList &arguments, QObject *parent = 0);

  protected:
    virtual Response* windowFound(WebPage *);
};

