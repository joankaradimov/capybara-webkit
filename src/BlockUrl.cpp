#include "BlockUrl.h"
#include "SocketCommand.h"
#include "WebPage.h"
#include "WebPageManager.h"

BlockUrl::BlockUrl(
  WebPageManager *manager,
  QStringList &arguments,
  QObject *parent
) : SocketCommand(manager, arguments, parent) {
}

Response* BlockUrl::start() {
  manager()->blockUrl(arguments()[0]);
  return finish(true);
}
