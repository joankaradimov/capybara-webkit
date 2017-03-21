#include "GoBack.h"
#include "SocketCommand.h"
#include "WebPage.h"
#include "WebPageManager.h"

GoBack::GoBack(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {
}

Response* GoBack::start() {
  page()->triggerAction(QWebPage::Back);
  return finish(true);
}
