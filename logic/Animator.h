#ifndef CARTOON_MAKER_LOGIC_ANIMATOR_H_
#define CARTOON_MAKER_LOGIC_ANIMATOR_H_

#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

#include "../ui/CartoonScene.h"

class Animator : public QObject {
  Q_OBJECT
 public:
  Animator(CartoonScene* cartoonScene, QVector<Frame> frames);
  void Play();
 signals:
  void AnimationFinished();
 private:
  static double NormalizeSecondAngle(double first_angle, double second_angle);
  void MakeAnimation();
  QParallelAnimationGroup* SkeletonProperties(Body* body, int bodyIndex);
  QSequentialAnimationGroup* MainPointProperties(MainPoint* mainPoint, int bodyIndex);
  QSequentialAnimationGroup* SidePointProperties(SidePoint* sidePoint, int bodyIndex, int pointIndex);
  QVector<Frame> frames_;
  CartoonScene* cartoon_scene_;
  QParallelAnimationGroup* parallel_animation_group_;

};

#endif //CARTOON_MAKER_LOGIC_ANIMATOR_H_
