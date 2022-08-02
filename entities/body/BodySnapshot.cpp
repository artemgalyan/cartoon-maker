#include "BodySnapshot.h"

#include <utility>

SkeletonSnapshot BodySnapshot::GetSkeleton() const {
  return skeleton_;
}

bool BodySnapshot::IsVisible() const {
  return isVisible_;
}

BodySnapshot::BodySnapshot(SkeletonSnapshot skeleton, bool is_visible)
    : skeleton_(std::move(skeleton)), isVisible_(is_visible) {}

BodySnapshot::BodySnapshot(const Body& body) :
  skeleton_(SkeletonSnapshot(body.GetSkeleton())),
  isVisible_(body.IsVisible()) {}

void BodySnapshot::SetVisible(bool visible) {
  isVisible_ = visible;
}

double BodySnapshot::GetZIndex() const {
  return skeleton_.GetZIndex();
}

void BodySnapshot::SetZIndex(double z) {
  skeleton_.SetZIndex(z);
}

double BodySnapshot::GetScale() const {
  return skeleton_.GetScale();
}

void BodySnapshot::SetScale(double scale) {
  skeleton_.SetScale(scale);
}

QDataStream& operator>>(QDataStream& ds, BodySnapshot& s) {
  return ds >> s.isVisible_ >> s.skeleton_;
}

QDataStream& operator<<(QDataStream& ds, const BodySnapshot& s) {
  return ds << s.isVisible_ << s.skeleton_;
}