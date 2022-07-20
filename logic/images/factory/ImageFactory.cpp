#include "ImageFactory.h"

ImageFactory *ImageFactory::instance_ = nullptr;

QVector<Image *> ImageFactory::GetImagesByKey(QString key) const {
  return images_.operator[](key);
}

ImageFactory &ImageFactory::Instance() {
  if (instance_ == nullptr) {
    instance_ = new ImageFactory();
  }
  return *instance_;
}
