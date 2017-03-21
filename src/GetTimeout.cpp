#include "GetTimeout.h"
#include "WebPageManager.h"

GetTimeout::GetTimeout(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {
}

Response* GetTimeout::start() {
  return finish(true, QString::number(manager()->getTimeout()));
}
