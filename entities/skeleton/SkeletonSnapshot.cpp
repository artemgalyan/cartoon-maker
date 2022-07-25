#include "SkeletonSnapshot.h"

#include "Skeleton.h"

SkeletonSnapshot::SkeletonSnapshot(QVector<PointSnapshot> p) : snapshots_(std::move(p)) {}

const QVector<PointSnapshot>& SkeletonSnapshot::GetPointSnapshots() const {
  return snapshots_;
}

SkeletonSnapshot::SkeletonSnapshot(const Skeleton &s) {
  auto points = s.GetPoints();
  for (auto point: points){
    snapshots_.push_back(PointSnapshot::CreateSnapshotOf(point));
  }
}
