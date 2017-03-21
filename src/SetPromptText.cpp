#include "SetPromptText.h"
#include "WebPage.h"
#include "WebPageManager.h"

SetPromptText::SetPromptText(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {}

Response* SetPromptText::start()
{
  page()->setPromptText(arguments()[0]);
  return finish(true);
}
