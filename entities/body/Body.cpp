#include "Body.h"

#include <utility>
QString Body::GetBodyType() const {
  return type_;
}

const Skeleton &Body::GetSkeleton() const {
  return skeleton_;
}

void Body::AddTo(QGraphicsScene *scene) const {
  scene->addItem(skeleton_.GetMainPoint());
}

Body::Body(Skeleton skeleton, QVector<Image *> images) : skeleton_(std::move(skeleton)), images_(std::move(images)) {}
