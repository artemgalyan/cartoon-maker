#ifndef CARTOON_MAKER_LOGIC_IMAGES_FACTORY_IMAGEFACTORY_H_
#define CARTOON_MAKER_LOGIC_IMAGES_FACTORY_IMAGEFACTORY_H_

#include <QString>
#include <QMap>
#include <utility>
#include "../Image.h"

class ImageFactory {
 public:
  [[nodiscard]] QVector<Image *> GetImagesByKey(QString key) const;
  static ImageFactory &Instance();
 private:
  explicit ImageFactory() {}
  QMap<QString, QVector<Image *>> images_;
  static ImageFactory *instance_;
};

#endif //CARTOON_MAKER_LOGIC_IMAGES_FACTORY_IMAGEFACTORY_H_
