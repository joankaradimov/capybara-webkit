#include "GetWindowHandle.h"
#include "WebPage.h"
#include "WebPageManager.h"
#include <QStringList>

GetWindowHandle::GetWindowHandle(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {
}

Response* GetWindowHandle::start() {
  return finish(true, page()->uuid());
}
