#include "Body.h"
#include "WebPage.h"
#include "WebPageManager.h"

Body::Body(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {
}

Response* Body::start() {
  if (page()->contentType().contains("html"))
    return finish(true, page()->currentFrame()->toHtml());
  else
    return finish(true, page()->body());
}
