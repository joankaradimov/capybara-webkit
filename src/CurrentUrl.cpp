#include "CurrentUrl.h"
#include "WebPage.h"
#include "WebPageManager.h"

CurrentUrl::CurrentUrl(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {
}

Response* CurrentUrl::start() {
  QStringList arguments;
  QVariant result = page()->currentFrame()->evaluateJavaScript("window.location.toString()");
  QString url = result.toString();
  return finish(true, url);
}

