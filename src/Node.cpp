#include "Node.h"
#include "WebPage.h"
#include "WebPageManager.h"
#include "InvocationResult.h"

Node::Node(WebPageManager *manager, QStringList &arguments, QObject *parent) : JavascriptCommand(manager, arguments, parent) {
}

Response* Node::start() {
  QStringList functionArguments(arguments());
  QString functionName = functionArguments.takeFirst();
  QString allowUnattached = functionArguments.takeFirst();
  InvocationResult result = page()->invokeCapybaraFunction(functionName, allowUnattached == "true", functionArguments);
  if (functionName == "focus") {
    page()->setCurrentFrameParent(page()->currentFrame()->parentFrame());
  }
  return finish(&result);
}

QString Node::toString() const {
  QStringList functionArguments(arguments());
  return QString("Node.") + functionArguments.takeFirst();
}
