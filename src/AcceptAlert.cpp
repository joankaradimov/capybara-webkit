#include "AcceptAlert.h"
#include "SocketCommand.h"
#include "WebPage.h"
#include "WebPageManager.h"

AcceptAlert::AcceptAlert(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {
}

Response* AcceptAlert::start() {
  return finish(true, page()->acceptAlert(arguments()[0]));
}
