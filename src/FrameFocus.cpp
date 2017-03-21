#include "FrameFocus.h"
#include "SocketCommand.h"
#include "WebPage.h"
#include "WebPageManager.h"
#include "ErrorMessage.h"

FrameFocus::FrameFocus(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {
}

Response* FrameFocus::start() {
  switch(arguments().length()) {
    case 1:
      return focusId(arguments()[0]);
    case 2:
      return focusIndex(arguments()[1].toInt());
    default:
      return focusParent();
  }
}

void FrameFocus::findFrames() {
  frames = page()->currentFrame()->childFrames();
}

Response* FrameFocus::focusIndex(int index) {
  findFrames();
  if (isFrameAtIndex(index)) {
    frames[index]->setFocus();
    page()->setCurrentFrameParent(frames[index]->parentFrame());
    return success();
  } else {
    return frameNotFound();
  }
}

bool FrameFocus::isFrameAtIndex(int index) {
  return 0 <= index && index < frames.length();
}

Response* FrameFocus::focusId(QString name) {
  findFrames();
  for (int i = 0; i < frames.length(); i++) {
    if (frames[i]->frameName().compare(name) == 0) {
      frames[i]->setFocus();
      page()->setCurrentFrameParent(frames[i]->parentFrame());
      return success();
    }
  }

  return frameNotFound();
}

Response* FrameFocus::focusParent() {
  // if (page()->currentFrame()->parentFrame() == 0) {
  if (page()->currentFrameParent() == 0) {
    return finish(false, new ErrorMessage("Already at parent frame."));
  } else {
    // page()->currentFrame()->parentFrame()->setFocus();
    page()->currentFrameParent()->setFocus();
    page()->setCurrentFrameParent(page()->currentFrameParent()->parentFrame());
    return success();
  }
}

Response* FrameFocus::frameNotFound() {
  return finish(false, new ErrorMessage("Unable to locate frame."));
}

Response* FrameFocus::success() {
  return finish(true);
}
