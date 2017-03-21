#include "CommandFactory.h"
#include "NullCommand.h"
#include "Visit.h"
#include "FindXpath.h"
#include "Reset.h"
#include "Node.h"
#include "Evaluate.h"
#include "Execute.h"
#include "FrameFocus.h"
#include "Header.h"
#include "Render.h"
#include "Body.h"
#include "Status.h"
#include "Headers.h"
#include "SetCookie.h"
#include "ClearCookies.h"
#include "GetCookies.h"
#include "SetProxy.h"
#include "ConsoleMessages.h"
#include "CurrentUrl.h"
#include "SetTimeout.h"
#include "GetTimeout.h"
#include "WindowResize.h"
#include "IgnoreSslErrors.h"
#include "SetSkipImageLoading.h"
#include "WindowFocus.h"
#include "GetWindowHandles.h"
#include "GetWindowHandle.h"
#include "WebPageManager.h"
#include "Authenticate.h"
#include "EnableLogging.h"
#include "SetConfirmAction.h"
#include "SetPromptAction.h"
#include "SetPromptText.h"
#include "ClearPromptText.h"
#include "JavascriptAlertMessages.h"
#include "JavascriptConfirmMessages.h"
#include "JavascriptPromptMessages.h"
#include "SetUrlBlacklist.h"
#include "Version.h"
#include "Title.h"
#include "FindCss.h"
#include "WindowClose.h"
#include "WindowOpen.h"
#include "WindowSize.h"
#include "WindowMaximize.h"
#include "GoBack.h"
#include "GoForward.h"
#include "AcceptAlert.h"
#include "FindModal.h"
#include "SetUnknownUrlMode.h"
#include "AllowUrl.h"
#include "BlockUrl.h"

CommandFactory::CommandFactory(WebPageManager *manager, QObject *parent) : QObject(parent) {
  m_manager = manager;
}

#define CHECK_COMMAND(expectedName) \
  if (strcmp(#expectedName, name) == 0) { \
    return new expectedName(m_manager, arguments, this); \
  }

SocketCommand *CommandFactory::createCommand(const char *name, QStringList &arguments) {
  CHECK_COMMAND(Visit)
  CHECK_COMMAND(FindXpath)
  CHECK_COMMAND(Reset)
  CHECK_COMMAND(Node)
  CHECK_COMMAND(Evaluate)
  CHECK_COMMAND(Execute)
  CHECK_COMMAND(FrameFocus)
  CHECK_COMMAND(Header)
  CHECK_COMMAND(Render)
  CHECK_COMMAND(Body)
  CHECK_COMMAND(Status)
  CHECK_COMMAND(Headers)
  CHECK_COMMAND(SetCookie)
  CHECK_COMMAND(ClearCookies)
  CHECK_COMMAND(GetCookies)
  CHECK_COMMAND(SetProxy)
  CHECK_COMMAND(ConsoleMessages)
  CHECK_COMMAND(CurrentUrl)
  CHECK_COMMAND(WindowResize)
  CHECK_COMMAND(IgnoreSslErrors)
  CHECK_COMMAND(SetSkipImageLoading)
  CHECK_COMMAND(WindowFocus)
  CHECK_COMMAND(GetWindowHandles)
  CHECK_COMMAND(GetWindowHandle)
  CHECK_COMMAND(Authenticate)
  CHECK_COMMAND(EnableLogging)
  CHECK_COMMAND(SetConfirmAction)
  CHECK_COMMAND(SetPromptAction)
  CHECK_COMMAND(SetPromptText)
  CHECK_COMMAND(ClearPromptText)
  CHECK_COMMAND(JavascriptAlertMessages)
  CHECK_COMMAND(JavascriptConfirmMessages)
  CHECK_COMMAND(JavascriptPromptMessages)
  CHECK_COMMAND(GetTimeout)
  CHECK_COMMAND(SetTimeout)
  CHECK_COMMAND(SetUrlBlacklist)
  CHECK_COMMAND(Title)
  CHECK_COMMAND(Version)
  CHECK_COMMAND(FindCss)
  CHECK_COMMAND(WindowClose)
  CHECK_COMMAND(WindowOpen)
  CHECK_COMMAND(WindowSize)
  CHECK_COMMAND(WindowMaximize)
  CHECK_COMMAND(GoBack)
  CHECK_COMMAND(GoForward)
  CHECK_COMMAND(AcceptAlert)
  CHECK_COMMAND(FindModal)
  CHECK_COMMAND(SetUnknownUrlMode)
  CHECK_COMMAND(AllowUrl)
  CHECK_COMMAND(BlockUrl)
  return new NullCommand(m_manager, QString(name), arguments, this);
}
