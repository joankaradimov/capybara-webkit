#include "Visit.h"
#include "SocketCommand.h"
#include "WebPage.h"
#include "WebPageManager.h"

Visit::Visit(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {
}

Response* Visit::start() {
  QUrl requestedUrl = QUrl::fromEncoded(arguments()[0].toUtf8(), QUrl::TolerantMode);
  page()->currentFrame()->load(QUrl(requestedUrl));
  return finish(true);
}
