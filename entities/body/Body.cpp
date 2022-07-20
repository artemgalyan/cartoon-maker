#include "Body.h"
QString Body::GetBodyType() {
  return type_;
}

const Skeleton &Body::GetSkeleton() {
  return skeleton_;
}

void Body::AddTo(QGraphicsScene *scene) const {
  QVector<Point *> skeletonPoints = skeleton_.GetPoints(); //MainPoint is skeletonPoints[0]
  scene->addItem(skeletonPoints[0]);
}

Body::Body(const Skeleton &skeleton, QVector<QImage *> images) : skeleton_(skeleton), images_(images) {

}
