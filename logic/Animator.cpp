
#include "Animator.h"

#include <utility>

Animator::Animator(CartoonScene *cartoonScene, QVector<Frame> frames)
    : cartoonScene_(cartoonScene), frames_(std::move(frames)) {
  BodiesProperties();
  MakeParallelAnimation();
}
/*void Animator::Play() {
  auto bodiesOnScene = cartoonScene_->GetBodies();
  for (int i = 0; i < bodiesOnScene.size(); i++) {

    auto body = bodiesOnScene[i];
    FillPropertiesForBody(i, body);
  }
}*/
/*void Animator::FillPropertiesForBody(int index, Body *&body) {
  QVector<QPropertyAnimation *> property;
  for (int i = 0; i < frames_.size() - 1; i++) {
    auto bodiesSnapshotCurrent = frames_[i].GetSnapshots();
    auto bodiesSnapshotNext = frames_[i + 1].GetSnapshots();
    for (int j = 0; j < bodiesSnapshotCurrent.size(); j++) {
      if (bodiesSnapshotCurrent[j].IsVisible() == bodiesSnapshotNext[j].IsVisible()) {
        auto currentSkeleton = bodiesSnapshotCurrent[j].GetSkeleton().GetPointSnapshots();
        auto nextSkeleton = bodiesSnapshotNext[j].GetSkeleton().GetPointSnapshots();

        QPropertyAnimation *pPosAnimation1 = new QPropertyAnimation(body->GetSkeleton().GetMainPoint(), "pos");
        pPosAnimation1->setDuration(1000);
        pPosAnimation1->setStartValue(QPointF(currentSkeleton[0].coord1, currentSkeleton[0].coord2));
        pPosAnimation1->setEndValue(QPoint(nextSkeleton[0].coord1, nextSkeleton[0].coord2));
        pPosAnimation1->setEasingCurve(QEasingCurve::Linear);
        property.push_back(pPosAnimation1);
        propertyAnimationForBodies.insert(index, property);*/
//animationGroup->addAnimation(pPosAnimation1);
/*auto bodySkeleton = body->GetSkeleton().GetPoints();

for (int k = 1; k < bodySkeleton.size(); k++) {
  QPropertyAnimation *pPosAnimation2 = new QPropertyAnimation(bodySkeleton[k], "pos");
  pPosAnimation2->setDuration(1000);
  pPosAnimation2->setStartValue;
  pPosAnimation2->setEndValue(QPoint(nextSkeleton[k].coord1, nextSkeleton[k].coord2));
  pPosAnimation2->setEasingCurve(QEasingCurve::Linear);
  animationGroup->addAnimation(pPosAnimation2);

}*/
/*}
}
}
}*/

void Animator::BodiesProperties() {
  QVector<Body *> bodiesOnScene = cartoonScene_->GetBodies();
  for (int i = 0; i < bodiesOnScene.size(); i++) {
    Body *body = bodiesOnScene[i];
    propertyAnimationForBodies[i] = SkeletonProperties(body, i);
  }
}
QVector<QPropertyAnimation *> Animator::SkeletonProperties(Body *body, int bodyIndex) {
  QVector<Point *> SkeletonOfPoints = body->GetSkeleton().GetPoints();
  QVector<QPropertyAnimation *> propertyAnimationOfBody;
  MainPoint *mainPoint = body->GetSkeleton().GetMainPoint();
  MainPointProperties(mainPoint, bodyIndex, propertyAnimationOfBody);
  for (int i = 1; i < SkeletonOfPoints.size(); i++) {
    SidePointProperties(SkeletonOfPoints[i], bodyIndex, i, propertyAnimationOfBody);
  }
  return propertyAnimationOfBody;
}

QVector<QPropertyAnimation *> Animator::MainPointProperties(MainPoint *mainPoint,
                                                            int bodyIndex,
                                                            QVector<QPropertyAnimation *> propertyAnimationOfBody) {
  for (int i = 0; i < frames_.size() - 1; i++) {
    PointSnapshot startPoint = frames_[i].GetSnapshots()[bodyIndex].GetSkeleton().GetPointSnapshots()[0];
    PointSnapshot endPoint = frames_[i + 1].GetSnapshots()[bodyIndex].GetSkeleton().GetPointSnapshots()[0];
    auto *pPosAnimation1 = new QPropertyAnimation(mainPoint, "pos");
    pPosAnimation1->setDuration(1000);
    pPosAnimation1->setStartValue(QPointF(startPoint.coord1, startPoint.coord2));
    pPosAnimation1->setEndValue(QPointF(endPoint.coord1, endPoint.coord2));
    pPosAnimation1->setEasingCurve(QEasingCurve::Linear);
    propertyAnimationOfBody.push_back(pPosAnimation1);
  }
  return propertyAnimationOfBody;
}

QVector<QPropertyAnimation *> Animator::SidePointProperties(Point *sidePoint,
                                                            int bodyIndex,
                                                            int pointIndex,
                                                            QVector<QPropertyAnimation *> propertyAnimationOfBody) {
  return propertyAnimationOfBody;

}
void Animator::MakeParallelAnimation() {
  parallelAnimationGroup = new QParallelAnimationGroup(cartoonScene_);

  for (QMap<int, QVector<QPropertyAnimation *>>::iterator it = propertyAnimationForBodies.begin();
       it != propertyAnimationForBodies.end(); ++it) {
    QVector<QPropertyAnimation *> bodyProperties = it.value();
    parallelAnimationGroup->addAnimation(MakeBodyAnimation(bodyProperties));
  }
}
QSequentialAnimationGroup *Animator::MakeBodyAnimation(QVector<QPropertyAnimation *> bodyProperties) {

  auto *animationBody = new QSequentialAnimationGroup(cartoonScene_);
  for (int i = 0; i < bodyProperties.size(); i++) {
    animationBody->addAnimation(bodyProperties[i]);
  }
  return animationBody;
}
QParallelAnimationGroup *Animator::GetParallelAnimation() {
  return parallelAnimationGroup;
}




