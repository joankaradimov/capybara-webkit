#include "Status.h"
#include "WebPage.h"
#include "WebPageManager.h"
#include <sstream>

Status::Status(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {
}

Response* Status::start() {
  int status = page()->getLastStatus();
  return finish(true, QString::number(status));
}

