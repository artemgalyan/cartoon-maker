
#include "Animator.h"

Animator::Animator(CartoonScene *cartoonScene, QVector<Frame> frames) : cartoonScene_(cartoonScene), frames_(frames) {
}
void Animator::Play() {
  auto bodiesOnScene = cartoonScene_->GetBodies();
  for (int i = 0; i < bodiesOnScene.size(); i++) {

    auto body = bodiesOnScene[i];
    FillPropertiesForBody(i, body);
  }
}
void Animator::FillPropertiesForBody(int index, Body *&body) {
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
        propertyAnimationForBodies.insert(index, property);
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
      }
    }
  }
}

