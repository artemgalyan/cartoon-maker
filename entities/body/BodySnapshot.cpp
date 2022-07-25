#include "BodySnapshot.h"

#include <utility>

SkeletonSnapshot BodySnapshot::GetSkeleton() const {
  return skeleton_;
}

bool BodySnapshot::IsVisible() const {
  return isVisible_;
}

BodySnapshot::BodySnapshot(SkeletonSnapshot skeleton, bool isVisible)
    : skeleton_(std::move(skeleton)), isVisible_(isVisible) {}

BodySnapshot::BodySnapshot(const Body& body) :
  skeleton_(SkeletonSnapshot(body.GetSkeleton())),
  isVisible_(body.IsVisible()) {}
