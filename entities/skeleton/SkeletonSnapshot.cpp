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
