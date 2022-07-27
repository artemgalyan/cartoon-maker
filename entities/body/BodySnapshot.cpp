#include "BodySnapshot.h"

#include <utility>

SkeletonSnapshot BodySnapshot::GetSkeleton() const {
  return skeleton_;
}

bool BodySnapshot::IsVisible() const {
  return isVisible_;
}

BodySnapshot::BodySnapshot(SkeletonSnapshot skeleton, bool isVisible)
    : skeleton_(std::move(skeleton)), isVisible_(isVisible), zIndex_(skeleton_.GetZIndex()) {}

BodySnapshot::BodySnapshot(const Body& body) :
  skeleton_(SkeletonSnapshot(body.GetSkeleton())),
  isVisible_(body.IsVisible()), zIndex_(skeleton_.GetZIndex()) {}

void BodySnapshot::SetVisible(bool visible) {
  isVisible_ = visible;
}

double BodySnapshot::GetZIndex() const {
  return zIndex_;
}

void BodySnapshot::SetZIndex(double z) {
  zIndex_ = z;
}
