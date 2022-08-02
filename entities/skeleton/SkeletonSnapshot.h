#ifndef CARTOON_MAKER_ENTITIES_SKELETON_SKELETONSNAPSHOT_H_
#define CARTOON_MAKER_ENTITIES_SKELETON_SKELETONSNAPSHOT_H_

#include "point/PointSnapshot.h"
class Skeleton;

#include <QVector>

class SkeletonSnapshot {
 public:
  explicit SkeletonSnapshot() = default;
  explicit SkeletonSnapshot(const Skeleton&);
  [[nodiscard]] const QVector<PointSnapshot>& GetPointSnapshots() const;
  [[nodiscard]] double GetZIndex() const;
  void SetZIndex(double z);
  void SetScale(double s);
  [[nodiscard]] double GetScale() const;
  friend QDataStream& operator>>(QDataStream&, SkeletonSnapshot&);
  friend QDataStream& operator<<(QDataStream&, const SkeletonSnapshot&);
 private:
  double zIndex_;
  double scale_;
  QVector<PointSnapshot> snapshots_;
};

#endif //CARTOON_MAKER_ENTITIES_SKELETON_SKELETONSNAPSHOT_H_
