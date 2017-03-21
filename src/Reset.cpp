#include "Reset.h"
#include "WebPage.h"
#include "WebPageManager.h"

Reset::Reset(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {
}

Response* Reset::start() {
  manager()->reset();

  return finish(true);
}

