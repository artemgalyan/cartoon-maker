#ifndef CARTOON_MAKER_ENTITIES_SKELETON_POINT_POINTSNAPSHOT_H_
#define CARTOON_MAKER_ENTITIES_SKELETON_POINT_POINTSNAPSHOT_H_

#include "MainPoint.h"
#include "SidePoint.h"

struct PointSnapshot {
  double coord1;
  double coord2;
  friend QDataStream& operator>>(QDataStream& ds, PointSnapshot& ps) {
    return ds >> ps.coord1 >> ps.coord2;
  }
  friend QDataStream& operator<<(QDataStream& ds, const PointSnapshot& ps) {
    return ds << ps.coord1 << ps.coord2;
  }
};

#endif //CARTOON_MAKER_ENTITIES_SKELETON_POINT_POINTSNAPSHOT_H_
