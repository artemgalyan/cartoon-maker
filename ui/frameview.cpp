#include "frameview.h"

FrameView::FrameView(int index, QPixmap image, QWidget* parent) : QLabel(parent), index_(index), image_(image)
{
  resize(image_.size());
  setPixmap(image_);
  show();
}

void FrameView::mousePressEvent(QMouseEvent *e)
{
  emit Clicked(index_);
  QLabel::mousePressEvent(e);
}
