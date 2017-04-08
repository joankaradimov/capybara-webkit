#include "Server.h"
#include "IgnoreDebugOutput.h"
#include "StdinNotifier.h"
#include "WebPageManager.h"
#include <QApplication>
#include <QStyleFactory>
#include <iostream>
#ifdef Q_OS_UNIX
  #include <unistd.h>
#endif

int main() {
#ifdef Q_OS_UNIX
  if (setpgid(0, 0) < 0) {
    std::cerr << "Unable to set new process group." << std::endl;
    return 1;
  }
#endif

  Server server(0);
  StdinNotifier notifier;
  ignoreDebugOutput();

  QObject::connect(&notifier, SIGNAL(eof()), server.manager(), SLOT(quit()));

  if (server.start()) {
    std::cout << "Capybara-webkit server started, listening on port: " << server.server_port() << std::endl;
    return server.manager()->exec();
  } else {
    std::cerr << "Couldn't start capybara-webkit server" << std::endl;
    return 1;
  }
}
