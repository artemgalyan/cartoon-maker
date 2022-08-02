#include "VisibilityAnimation.h"

int VisibilityAnimation::duration() const {
  return 0;
}

void VisibilityAnimation::updateCurrentTime(int currentTime) {
  item_->setVisible(value_);
}

VisibilityAnimation::VisibilityAnimation(bool value, QGraphicsItem* item) : value_(value), item_(item) {}