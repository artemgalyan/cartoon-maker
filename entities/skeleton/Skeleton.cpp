#include "Skeleton.h"
#include "point/MainPoint.h"

#include <exception>

Skeleton::Skeleton(QVector<Point *> points) : points_(std::move(points)) {}

const QVector<Point *> &Skeleton::GetPoints() const {
  return points_;
}

MainPoint* Skeleton::GetMainPoint() const {
  if (points_.isEmpty()){
    throw std::logic_error("Points are empty!");
  }
  return dynamic_cast<MainPoint*>(points_[0]);
}

Skeleton::Skeleton(const Skeleton &s) noexcept {
  points_ = s.points_;
}
