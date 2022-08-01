
#ifndef CARTOON_MAKER_LOGIC_ANIMATOR_H_
#define CARTOON_MAKER_LOGIC_ANIMATOR_H_

#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include "../ui/CartoonScene.h"
class Animator {
  // TODO: Create this class
 public:
  Animator(CartoonScene *cartoonScene, QVector <Frame> frames);
  QMap<int, QVector<QPropertyAnimation*>>  GetPropertiesMap() const{
    return propertyAnimationForBodies;
  }
  void Play();



 private:
  void FillPropertiesForBody(int index, Body *&body);
  QVector <Frame> frames_;
  QMap<int, QVector<QPropertyAnimation*>> propertyAnimationForBodies;
  CartoonScene *cartoonScene_;
  //QSequentialAnimationGroup* animationGroup;
  //QParallelAnimationGroup * parallel_animation_group;
};

#endif //CARTOON_MAKER_LOGIC_ANIMATOR_H_
