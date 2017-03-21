#include "Headers.h"
#include "WebPage.h"
#include "WebPageManager.h"
#include "JsonSerializer.h"

Headers::Headers(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {
}

Response* Headers::start() {
  JsonSerializer serializer;
  QByteArray json = serializer.serialize(page()->pageHeaders());
  return finish(true, json);
}

