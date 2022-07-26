#include "frameview.h"

#include <utility>

FrameView::FrameView(int index, QPixmap image, QWidget *parent)
    : QLabel(parent), index_(index), image_(std::move(image)) {
  resize(image_.size());
  setPixmap(image_);
}

void FrameView::mousePressEvent(QMouseEvent *e) {
  emit Clicked(index_);
  QLabel::mousePressEvent(e);
}

int FrameView::GetIndex() const {
  return index_;
}

void FrameView::SetIndex(int newIndex) {
  index_ = newIndex;
}
