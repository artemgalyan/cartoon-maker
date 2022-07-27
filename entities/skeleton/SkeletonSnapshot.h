#ifndef CARTOON_MAKER_ENTITIES_SKELETON_SKELETONSNAPSHOT_H_
#define CARTOON_MAKER_ENTITIES_SKELETON_SKELETONSNAPSHOT_H_

#include "point/PointSnapshot.h"
class Skeleton;

#include <QVector>

class SkeletonSnapshot {
 public:
  explicit SkeletonSnapshot(const Skeleton&);
  [[nodiscard]] const QVector<PointSnapshot>& GetPointSnapshots() const;
  [[nodiscard]] double GetZIndex() const;
 private:
  double zIndex_;
  QVector<PointSnapshot> snapshots_;
};

#endif //CARTOON_MAKER_ENTITIES_SKELETON_SKELETONSNAPSHOT_H_
