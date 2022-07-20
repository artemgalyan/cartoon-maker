#include "Image.h"

Image::Image(const QPixmap &image, const QPointF &offset) : image_(image), offset_(offset) {}

const QPixmap &Image::GetImage() const {
  return image_;
}

QPointF Image::GetOffset() const {
  return offset_;
}
