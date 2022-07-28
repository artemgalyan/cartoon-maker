#include "Skeleton.h"
#include "point/MainPoint.h"

#include <exception>

Skeleton::Skeleton(QVector<Point *> points) : points_(std::move(points)) {}

const QVector<Point *> &Skeleton::GetPoints() const {
  return points_;
}

MainPoint *Skeleton::GetMainPoint() const {
  if (points_.isEmpty()) {
    throw std::logic_error("Points are empty!");
  }
  return dynamic_cast<MainPoint *>(points_[0]);
}

Skeleton::Skeleton(const Skeleton &s) noexcept {
  points_ = s.points_;
}

Skeleton Skeleton::Clone() const {
  QVector<Point *> points;
  for (int i = 0; i < points_.size(); ++i) {
    Point *parent = nullptr;
    if (i != 0) {
      auto parentIndex = points_.indexOf(points_[i]->parentItem());
      parent = points[parentIndex];
    }
    points.push_back(points_[i]->Clone(parent));
  }
  return Skeleton(points);
}

void Skeleton::SetVisible(bool visible) const {
  GetMainPoint()->setVisible(visible);
}

bool Skeleton::IsVisible() const {
  if (points_.isEmpty()) {
    return false;
  }
  return GetMainPoint()->isVisible();
}

void Skeleton::LoadSnapshot(const SkeletonSnapshot &snapshot) {
  auto pointSnapshots = snapshot.GetPointSnapshots();
  if (pointSnapshots.isEmpty())
    return;

  GetMainPoint()->setPos(pointSnapshots[0].coord1, pointSnapshots[0].coord2);
  GetMainPoint()->setScale(snapshot.GetScale());
  GetMainPoint()->setZValue(snapshot.GetZIndex());
  for (int i = 1; i < pointSnapshots.count(); ++i) {
    auto point = dynamic_cast<SidePoint *>(points_[i]);
    if (point != nullptr) {
      point->SetAngle(pointSnapshots[i].coord2);
    }
  }
}
double Skeleton::GetScale() const {
  return GetMainPoint()->scale();
}
