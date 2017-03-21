#include "ConsoleMessages.h"
#include "WebPage.h"
#include "WebPageManager.h"
#include "JsonSerializer.h"

ConsoleMessages::ConsoleMessages(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {
}

Response* ConsoleMessages::start() {
  JsonSerializer serializer;
  QByteArray json = serializer.serialize(page()->consoleMessages());
  return finish(true, json);
}

