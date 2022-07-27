#include "SkeletonSnapshot.h"

#include "Skeleton.h"

const QVector<PointSnapshot> &SkeletonSnapshot::GetPointSnapshots() const {
  return snapshots_;
}

SkeletonSnapshot::SkeletonSnapshot(const Skeleton &s) {
  auto points = s.GetPoints();
  for (auto point : points) {
    snapshots_.push_back(PointSnapshot::CreateSnapshotOf(point));
  }
  zIndex_ = s.GetMainPoint()->zValue();
}

double SkeletonSnapshot::GetZIndex() const { return zIndex_; }
