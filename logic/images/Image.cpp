#include "Image.h"

#include <utility>

Image::Image(QPixmap image, const QPointF &offset) : image_(std::move(image)), offset_(offset) {}

const QPixmap &Image::GetImage() const {
  return image_;
}

QPointF Image::GetOffset() const {
  return offset_;
}
