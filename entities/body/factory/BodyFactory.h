#ifndef CARTOON_MAKER_ENTITIES_BODY_FACTORY_BODYFACTORY_H_
#define CARTOON_MAKER_ENTITIES_BODY_FACTORY_BODYFACTORY_H_

#include "../Body.h"
#include "../../skeleton/point/MainPoint.h"
#include "../../skeleton/point/SidePoint.h"



class BodyFactory {
  // TODO: Create BodyFactory class
 public:
  [[nodiscard]] Body* CreateByType(QString& type) const;
  static void Initialize();
  static BodyFactory *Instance();
 private:
  void LoadModels();
  void LoadModelByType(const QString& fileName);
  BodyFactory() = default;
  QVector<Body> models_;
  static BodyFactory *instance_;
};

#endif //CARTOON_MAKER_ENTITIES_BODY_FACTORY_BODYFACTORY_H_
