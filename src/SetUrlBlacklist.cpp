
#include "SetUrlBlacklist.h"
#include "WebPageManager.h"
#include "WebPage.h"
#include "NetworkAccessManager.h"

SetUrlBlacklist::SetUrlBlacklist(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {
}

Response* SetUrlBlacklist::start() {
  manager()->setUrlBlacklist(arguments());
  return finish(true);
}

