#include "PointSnapshot.h"

#include "point_utils.h"

PointSnapshot::PointSnapshot(const MainPoint &p) : isStraightMovement(true) {
  coord1 = p.x();
  coord2 = p.y();
}

PointSnapshot::PointSnapshot(const SidePoint &p) : isStraightMovement(false) {
  coord1 = PointUtils::GetDistance(p.pos());
  coord2 = PointUtils::GetAngle(p.pos());
}

PointSnapshot PointSnapshot::CreateSnapshotOf(const Point *point) {
  if (auto p = dynamic_cast<const MainPoint*>(point); p != nullptr) {
    return PointSnapshot(*p);
  }
  if (auto p = dynamic_cast<const SidePoint*>(point); p != nullptr) {
    return PointSnapshot(*p);
  }
  throw std::invalid_argument("Bad point pointer!");
}
