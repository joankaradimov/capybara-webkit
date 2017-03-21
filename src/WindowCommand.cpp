#include "WindowCommand.h"
#include "WebPage.h"
#include "WebPageManager.h"
#include "ErrorMessage.h"

WindowCommand::WindowCommand(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {
}

Response* WindowCommand::start() {
  return findWindow(arguments()[0]);
}

Response* WindowCommand::findWindow(QString selector) {
  foreach(WebPage *page, manager()->pages()) {
    if (page->matchesWindowSelector(selector)) {
      return windowFound(page);
    }
  }

  return windowNotFound();
}

Response* WindowCommand::windowNotFound() {
  return finish(false, new ErrorMessage("NoSuchWindowError", "Unable to locate window."));
}
