#include "NullCommand.h"
#include "WebPage.h"
#include "WebPageManager.h"
#include "ErrorMessage.h"
#include "SocketCommand.h"

NullCommand::NullCommand(WebPageManager* manager, QString name, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {
  m_name = name;
}

Response* NullCommand::start() {
  QString failure = QString("[Capybara WebKit] Unknown command: ") + m_name + "\n";
  return finish(false, new ErrorMessage(failure));
}

