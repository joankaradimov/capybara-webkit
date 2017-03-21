#include "WindowOpen.h"
#include "SocketCommand.h"
#include "WebPage.h"
#include "WebPageManager.h"

WindowOpen::WindowOpen(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {
}

Response* WindowOpen::start() {
  manager()->createPage();
  return finish(true);
}
