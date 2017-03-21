#include "SetSkipImageLoading.h"
#include "WebPage.h"
#include "WebPageManager.h"

SetSkipImageLoading::SetSkipImageLoading(WebPageManager *manager, QStringList &arguments, QObject *parent) :
  SocketCommand(manager, arguments, parent) {
}

Response* SetSkipImageLoading::start() {
  page()->setSkipImageLoading(arguments().contains("true"));
  return finish(true);
}
