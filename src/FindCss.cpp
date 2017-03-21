#include "FindCss.h"
#include "WebPage.h"
#include "WebPageManager.h"
#include "InvocationResult.h"

FindCss::FindCss(WebPageManager *manager, QStringList &arguments, QObject *parent) : JavascriptCommand(manager, arguments, parent) {
}

Response* FindCss::start() {
  InvocationResult result = page()->invokeCapybaraFunction("findCss", true, arguments());
  return finish(&result);
}

