#ifndef CARTOON_MAKER_ENTITIES_BODY_FACTORY_BODYFACTORY_H_
#define CARTOON_MAKER_ENTITIES_BODY_FACTORY_BODYFACTORY_H_

#include <QDataStream>
#include <QDir>
#include <QDirIterator>
#include <QTemporaryFile>
#include "../Body.h"
#include "../../skeleton/point/MainPoint.h"
#include "../../skeleton/point/SidePoint.h"

class BodyFactory {
 public:
  [[nodiscard]] Body *CreateByType(const QString &type) const;
  static void Initialize();
  static BodyFactory *Instance();
 private:
  void LoadModels();
  void LoadModelByType(const QString &subDirName);
  BodyFactory();
  QVector<Body> models_;
  static BodyFactory *instance_;
};

#endif //CARTOON_MAKER_ENTITIES_BODY_FACTORY_BODYFACTORY_H_
