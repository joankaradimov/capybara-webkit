#include "WindowFocus.h"
#include "WebPage.h"

WindowFocus::WindowFocus(WebPageManager *manager, QStringList &arguments, QObject *parent) : WindowCommand(manager, arguments, parent) {
}

Response* WindowFocus::windowFound(WebPage *page) {
  page->setFocus();
  return finish(true);
}
