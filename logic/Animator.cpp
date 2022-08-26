#include "Animator.h"
#include "../entities/skeleton/point/point_utils.h"
#include "bool_animation/VisibilityAnimation.h"

#include <utility>
#include <QGraphicsOpacityEffect>

Animator::Animator(CartoonScene* cartoonScene, QVector<Frame> frames)
    : cartoon_scene_(cartoonScene), frames_(std::move(frames)) {
  MakeAnimation();
  QObject::connect(parallel_animation_group_, &QAbstractAnimation::finished, [this]() {
    emit this->AnimationFinished();
  });
}

void Animator::Play() {
  parallel_animation_group_->start(QAbstractAnimation::DeleteWhenStopped);
}

void Animator::MakeAnimation() {
  QVector<Body*> bodiesOnScene = cartoon_scene_->GetBodies();
  parallel_animation_group_ = new QParallelAnimationGroup(cartoon_scene_);
  for (int i = 0; i < bodiesOnScene.size(); i++) {
    Body* body = bodiesOnScene[i];
    parallel_animation_group_->addAnimation(SkeletonProperties(body, i));
  }
}

QParallelAnimationGroup* Animator::SkeletonProperties(Body* body, int bodyIndex) {
  QParallelAnimationGroup* parallelAnimation = new QParallelAnimationGroup(cartoon_scene_);
  QVector<Point*> SkeletonOfPoints = body->GetSkeleton().GetPoints();
  MainPoint* mainPoint = body->GetSkeleton().GetMainPoint();
  parallelAnimation->addAnimation(MainPointProperties(mainPoint, bodyIndex));
  for (int i = 1; i < SkeletonOfPoints.size(); i++) {
    parallelAnimation->addAnimation(SidePointProperties(dynamic_cast<SidePoint*>(SkeletonOfPoints[i]), bodyIndex, i));
  }
  return parallelAnimation;
}

QSequentialAnimationGroup* Animator::MainPointProperties(MainPoint* mainPoint,
                                                         int bodyIndex) {
  QSequentialAnimationGroup* sequantialAnimation = new QSequentialAnimationGroup(cartoon_scene_);
  for (int i = 0; i < frames_.size() - 1; i++) {
    QParallelAnimationGroup* parallelAnimation = new QParallelAnimationGroup(cartoon_scene_);
    PointSnapshot startPoint = frames_[i].GetSnapshots()[bodyIndex].GetSkeleton().GetPointSnapshots()[0];
    PointSnapshot endPoint = frames_[i + 1].GetSnapshots()[bodyIndex].GetSkeleton().GetPointSnapshots()[0];
    auto* posAnimation = new QPropertyAnimation(mainPoint, "pos");
    posAnimation->setDuration(1000);
    posAnimation->setStartValue(QPointF(startPoint.coord1, startPoint.coord2));
    posAnimation->setEndValue(QPointF(endPoint.coord1, endPoint.coord2));
    posAnimation->setEasingCurve(QEasingCurve::Linear);
    parallelAnimation->addAnimation(posAnimation);

    auto* scaleAnimation = new QPropertyAnimation(mainPoint, "scale");
    double startScale = frames_[i].GetSnapshots()[bodyIndex].GetScale();
    double endScale = frames_[i + 1].GetSnapshots()[bodyIndex].GetScale();
    scaleAnimation->setDuration(1000);
    scaleAnimation->setStartValue(startScale);
    scaleAnimation->setEndValue(endScale);
    parallelAnimation->addAnimation(scaleAnimation);

    auto* zValueAnimation = new QPropertyAnimation(mainPoint, "z");
    double startValue = frames_[i].GetSnapshots()[bodyIndex].GetZIndex();
    double endValue = frames_[i + 1].GetSnapshots()[bodyIndex].GetZIndex();
    zValueAnimation->setDuration(1000);
    zValueAnimation->setStartValue(startValue);
    zValueAnimation->setEndValue(endValue);
    parallelAnimation->addAnimation(zValueAnimation);


    auto visibleAnimation = new VisibilityAnimation(frames_[i].GetSnapshots()[bodyIndex].IsVisible(), mainPoint);
    parallelAnimation->addAnimation(visibleAnimation);
    sequantialAnimation->addAnimation(parallelAnimation);
  }
  auto visibleAnimation = new VisibilityAnimation(frames_.last().GetSnapshots()[bodyIndex].IsVisible(), mainPoint);
  sequantialAnimation->addAnimation(visibleAnimation);
  return sequantialAnimation;
}

QSequentialAnimationGroup* Animator::SidePointProperties(SidePoint* sidePoint,
                                                         int bodyIndex,
                                                         int pointIndex) {
  QSequentialAnimationGroup* sequantialAnimation = new QSequentialAnimationGroup(cartoon_scene_);
  for (int i = 0; i < frames_.size() - 1; i++) {
    auto* angleAnimation = new QPropertyAnimation(sidePoint, "angle");
    PointSnapshot startPoint = frames_[i].GetSnapshots()[bodyIndex].GetSkeleton().GetPointSnapshots()[pointIndex];
    PointSnapshot endPoint = frames_[i + 1].GetSnapshots()[bodyIndex].GetSkeleton().GetPointSnapshots()[pointIndex];
    double startAngle = startPoint.coord2;
    double endAngle = NormalizeSecondAngle(startAngle, endPoint.coord2);
    angleAnimation->setDuration(1000);
    angleAnimation->setStartValue(startAngle);
    angleAnimation->setEndValue(endAngle);
    sequantialAnimation->addAnimation(angleAnimation);
  }
  return sequantialAnimation;
}

double Animator::NormalizeSecondAngle(double first_angle, double second_angle) {
  const double pi = std::numbers::pi;
  double a = 2 * pi + second_angle;
  double b = second_angle;
  double c = second_angle - 2 * pi;
  double differences[]{abs(first_angle - a), abs(first_angle - b), abs(first_angle - c)};
  if (differences[0] < differences[1]) {
    if (differences[0] < differences[2])
      return a;
    return c;
  }
  if (differences[1] < differences[2])
    return b;
  return c;
}







