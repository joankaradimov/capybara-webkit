#include "EnableLogging.h"
#include "WebPageManager.h"

EnableLogging::EnableLogging(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {
}

Response* EnableLogging::start() {
  manager()->enableLogging();
  return finish(true);
}
