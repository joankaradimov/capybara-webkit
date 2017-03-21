#include "JavascriptPromptMessages.h"
#include "WebPage.h"
#include "WebPageManager.h"
#include "JsonSerializer.h"

JavascriptPromptMessages::JavascriptPromptMessages(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {}

Response* JavascriptPromptMessages::start()
{
  JsonSerializer serializer;
  QByteArray json = serializer.serialize(page()->promptMessages());
  return finish(true, json);
}
