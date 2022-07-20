#include "SkeletonSnapshot.h"

SkeletonSnapshot::SkeletonSnapshot(QVector<PointSnapshot> p) : snapshots_(std::move(p)) {}

const QVector<PointSnapshot>& SkeletonSnapshot::GetPointSnapshots() const {
  return snapshots_;
}
