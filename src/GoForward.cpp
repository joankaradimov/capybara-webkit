#include "GoForward.h"
#include "SocketCommand.h"
#include "WebPage.h"
#include "WebPageManager.h"

GoForward::GoForward(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {
}

Response* GoForward::start() {
  page()->triggerAction(QWebPage::Forward);
  return finish(true);
}
