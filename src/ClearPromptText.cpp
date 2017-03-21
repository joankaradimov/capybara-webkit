#include "ClearPromptText.h"
#include "WebPage.h"
#include "WebPageManager.h"

ClearPromptText::ClearPromptText(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {}

Response* ClearPromptText::start()
{
  page()->setPromptText(QString());
  return finish(true);
}
