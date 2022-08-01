
#ifndef CARTOON_MAKER_LOGIC_ANIMATOR_H_
#define CARTOON_MAKER_LOGIC_ANIMATOR_H_

#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include "../ui/CartoonScene.h"
class Animator {
  // TODO: Create this class
 public:
  Animator(CartoonScene *cartoonScene, QVector<Frame> frames);
  QParallelAnimationGroup *GetParallelAnimation();
  //void Play();

 private:
  void MakeParallelAnimation();
  QSequentialAnimationGroup *MakeBodyAnimation(QVector<QPropertyAnimation *> bodyProperties);
  void BodiesProperties();
  QVector<QPropertyAnimation *> SkeletonProperties(Body *body, int bodyIndex);
  QVector<QPropertyAnimation *> MainPointProperties(MainPoint *mainPoint,
                                                    int bodyIndex,
                                                    QVector<QPropertyAnimation *> propertyAnimationOfBody);
  QVector<QPropertyAnimation *> SidePointProperties(Point *sidePoint,
                                                    int bodyIndex,
                                                    int pointIndex,
                                                    QVector<QPropertyAnimation *> propertyAnimationOfBody);
  //void FillPropertiesForBody(int index, Body *&body);
  QVector<Frame> frames_;
  QMap<int, QVector<QPropertyAnimation *>> propertyAnimationForBodies;
  CartoonScene *cartoonScene_;
  //QSequentialAnimationGroup* animationGroup;
  QParallelAnimationGroup *parallelAnimationGroup;
};

#endif //CARTOON_MAKER_LOGIC_ANIMATOR_H_
