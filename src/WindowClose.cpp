#include "WindowClose.h"
#include "WebPage.h"

WindowClose::WindowClose(WebPageManager *manager, QStringList &arguments, QObject *parent) : WindowCommand(manager, arguments, parent) {
}

Response* WindowClose::windowFound(WebPage *page) {
  page->remove();
  return finish(true);
}
