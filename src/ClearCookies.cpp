#include "ClearCookies.h"
#include "WebPage.h"
#include "WebPageManager.h"
#include "NetworkCookieJar.h"
#include <QNetworkCookie>

ClearCookies::ClearCookies(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {}

Response* ClearCookies::start()
{
  manager()->cookieJar()->clearCookies();
  return finish(true);
}
