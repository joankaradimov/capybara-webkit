#include "AllowUrl.h"
#include "SocketCommand.h"
#include "WebPage.h"
#include "WebPageManager.h"

AllowUrl::AllowUrl(
  WebPageManager *manager,
  QStringList &arguments,
  QObject *parent
) : SocketCommand(manager, arguments, parent) {
}

Response* AllowUrl::start() {
  manager()->allowUrl(arguments()[0]);
  return finish(true);
}
