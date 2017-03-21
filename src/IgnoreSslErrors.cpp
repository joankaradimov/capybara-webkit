#include "IgnoreSslErrors.h"
#include "WebPage.h"
#include "WebPageManager.h"

IgnoreSslErrors::IgnoreSslErrors(WebPageManager *manager, QStringList &arguments, QObject *parent) :
  SocketCommand(manager, arguments, parent) {
}

Response* IgnoreSslErrors::start() {
  manager()->setIgnoreSslErrors(true);
  return finish(true);
}

