#include "WindowSize.h"
#include "WebPage.h"
#include "WebPageManager.h"
#include "JsonSerializer.h"

WindowSize::WindowSize(WebPageManager *manager, QStringList &arguments, QObject *parent) : WindowCommand(manager, arguments, parent) {
}

Response* WindowSize::windowFound(WebPage *page) {
  QSize size = page->viewportSize();
  QVariantList elements;
  elements << size.width();
  elements << size.height();
  JsonSerializer serializer;
  QByteArray json = serializer.serialize(elements);
  return finish(true, json);
}
