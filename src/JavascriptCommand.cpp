#include "JavascriptCommand.h"
#include "WebPageManager.h"
#include "InvocationResult.h"

JavascriptCommand::JavascriptCommand(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {
}

Response* JavascriptCommand::finish(InvocationResult *result) {
  if (result->hasError())
    return SocketCommand::finish(false, result->errorMessage());
  else {
    QString message = result->result().toString();
    return SocketCommand::finish(true, message);
  }
}
