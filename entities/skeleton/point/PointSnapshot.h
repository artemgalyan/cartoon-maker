#ifndef CARTOON_MAKER_ENTITIES_SKELETON_POINT_POINTSNAPSHOT_H_
#define CARTOON_MAKER_ENTITIES_SKELETON_POINT_POINTSNAPSHOT_H_

#include "MainPoint.h"
#include "SidePoint.h"

struct PointSnapshot {
  double coord1;
  double coord2;
  const bool isStaightMovement;
  explicit PointSnapshot(const MainPoint&);
  explicit PointSnapshot(const SidePoint&);
  static PointSnapshot CreateSnapshotOf(const Point* point);
};

#endif //CARTOON_MAKER_ENTITIES_SKELETON_POINT_POINTSNAPSHOT_H_
