#include "ImageFactory.h"

ImageFactory *ImageFactory::instance_ = nullptr;

QVector<Image *> ImageFactory::GetImagesByKey(QString key) const {
  return images_.at(key);
}

ImageFactory &ImageFactory::Instance() {
  if (instance_ == nullptr) {
    instance_ = new ImageFactory(images_);
  }
  return *instance_;
}
