#ifndef CARTOON_MAKER_ENTITIES_BODY_FACTORY_BODYFACTORY_H_
#define CARTOON_MAKER_ENTITIES_BODY_FACTORY_BODYFACTORY_H_

#include "../Body.h"

class BodyFactory {
  // TODO: Create BodyFactory class
 public:
  Body* CreateByType(const QString& type) const;
  void Initialize();
  static BodyFactory *Instance();
 private:
  void LoadModels();
  BodyFactory() = default;
  QVector<Body> models_;
  static BodyFactory *instance_;
};

#endif //CARTOON_MAKER_ENTITIES_BODY_FACTORY_BODYFACTORY_H_
