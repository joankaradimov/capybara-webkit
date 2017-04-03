#include "FindModal.h"
#include "SocketCommand.h"
#include "WebPage.h"
#include "WebPageManager.h"
#include "ErrorMessage.h"

FindModal::FindModal(WebPageManager *manager, QStringList &arguments, QObject *parent)
  : SocketCommand(manager, arguments, parent) {
}

Response* FindModal::start() {
  if (page()->modalCount() == 0) {
    m_timer = new QTimer(this);
    m_timer->setSingleShot(true);
    double timeout = arguments()[1].toDouble();
    if (timeout > 0) {
      m_timer->start(timeout * 1000);
    }

    connect(page(), SIGNAL(modalReady()), SLOT(handleModalReady()));
    connect(m_timer, SIGNAL(timeout()), &m_wait_loop, SLOT(quit()));

    m_wait_loop.exec();

    disconnect(m_timer, SIGNAL(timeout()), &m_wait_loop, SLOT(quit()));
    disconnect(page(), SIGNAL(modalReady()), this, SLOT(handleModalReady()));

    if (m_response != Q_NULLPTR) {
      return m_response;
    } else { // TODO: use TimeoutError, maybe
      return finish(false, new ErrorMessage("ModalNotFound", "Timed out waiting for modal dialog"));
    }
  } else {
    return buildModalResponse();
  }
}

Response* FindModal::buildModalResponse() {
  QString message = page()->modalMessage();
  if (message.isNull()) {
    return finish(false, new ErrorMessage("ModalNotFound", "Unable to find modal dialog"));
  } else {
    return finish(true, message);
  }
}

void FindModal::handleModalReady() {
  m_response = buildModalResponse();
  m_wait_loop.quit();
}
