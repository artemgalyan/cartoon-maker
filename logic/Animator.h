
#ifndef CARTOON_MAKER_LOGIC_ANIMATOR_H_
#define CARTOON_MAKER_LOGIC_ANIMATOR_H_

#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include "../ui/CartoonScene.h"
class Animator {
  // TODO: Create this class
 public:
  Animator(CartoonScene* cartoonScene, QVector<Frame> frames);
  void Play();
 private:
  void MakeAnimation();
  QParallelAnimationGroup* SkeletonProperties(Body* body, int bodyIndex);
  QSequentialAnimationGroup* MainPointProperties(MainPoint* mainPoint, int bodyIndex);
  QSequentialAnimationGroup* SidePointProperties(SidePoint* sidePoint, int bodyIndex, int pointIndex);
  QVector<Frame> frames_;
  CartoonScene* cartoonScene_;
  QParallelAnimationGroup* parallelAnimationGroup_;

};

#endif //CARTOON_MAKER_LOGIC_ANIMATOR_H_
