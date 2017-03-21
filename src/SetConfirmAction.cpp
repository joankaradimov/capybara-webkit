#include "SetConfirmAction.h"
#include "WebPage.h"
#include "WebPageManager.h"

SetConfirmAction::SetConfirmAction(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {}

Response* SetConfirmAction::start()
{
  QString index;
  switch (arguments().length()) {
    case 2:
      index = page()->setConfirmAction(arguments()[0], arguments()[1]);
      break;
    default:
      page()->setConfirmAction(arguments()[0]);
  }

  return finish(true, index);
}
