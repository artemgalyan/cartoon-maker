#ifndef CARTOON_MAKER_ENTITIES_SKELETON_SKELETONSNAPSHOT_H_
#define CARTOON_MAKER_ENTITIES_SKELETON_SKELETONSNAPSHOT_H_

#include "point/PointSnapshot.h"

#include <QVector>

class SkeletonSnapshot {
 public:
  explicit SkeletonSnapshot(QVector<PointSnapshot>);
  [[nodiscard]] const QVector<PointSnapshot>& GetPointSnapshots() const;
 private:
  QVector<PointSnapshot> snapshots_;
};

#endif //CARTOON_MAKER_ENTITIES_SKELETON_SKELETONSNAPSHOT_H_
