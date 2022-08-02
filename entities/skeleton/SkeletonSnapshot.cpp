#include "SkeletonSnapshot.h"

#include "Skeleton.h"

const QVector<PointSnapshot>& SkeletonSnapshot::GetPointSnapshots() const {
  return snapshots_;
}

SkeletonSnapshot::SkeletonSnapshot(const Skeleton& s) {
  scale_ = s.GetScale();
  auto points = s.GetPoints();
  for (auto point : points) {
    snapshots_.push_back(point->CreateSnapshot());
  }
  zIndex_ = s.GetMainPoint()->zValue();
}

double SkeletonSnapshot::GetZIndex() const { return zIndex_; }

double SkeletonSnapshot::GetScale() const {
  return scale_;
}

void SkeletonSnapshot::SetZIndex(double z) {
  zIndex_ = z;
}
void SkeletonSnapshot::SetScale(double s) {
  scale_ = s;
}

QDataStream& operator>>(QDataStream& ds, SkeletonSnapshot& s) {
  return ds >> s.zIndex_ >> s.scale_ >> s.snapshots_;
}

QDataStream& operator<<(QDataStream& ds, const SkeletonSnapshot& s) {
  return ds << s.zIndex_ << s.scale_ << s.snapshots_;
}