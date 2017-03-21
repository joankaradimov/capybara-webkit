#include "SetTimeout.h"
#include "WebPageManager.h"
#include "ErrorMessage.h"

SetTimeout::SetTimeout(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {
}

Response* SetTimeout::start() {
  QString timeoutString = arguments()[0];
  bool ok;
  int timeout = timeoutString.toInt(&ok);

  if (ok) {
    manager()->setTimeout(timeout);
    return finish(true);
  } else {
    return finish(false, new ErrorMessage("Invalid value for timeout"));
  }
}
