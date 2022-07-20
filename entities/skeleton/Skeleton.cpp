#include "Skeleton.h"

Skeleton::Skeleton(QVector<Point *> points) : points_(std::move(points)) {}

const QVector<Point *> &Skeleton::GetPoints() const {
  return points_;
}
