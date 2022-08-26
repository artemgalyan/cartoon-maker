#include "BodySnapshot.h"

#include <utility>

SkeletonSnapshot BodySnapshot::GetSkeleton() const {
  return skeleton_;
}

bool BodySnapshot::IsVisible() const {
  return is_visible_;
}

BodySnapshot::BodySnapshot(SkeletonSnapshot skeleton, bool is_visible)
    : skeleton_(std::move(skeleton)), is_visible_(is_visible) {}

BodySnapshot::BodySnapshot(const Body& body) :
  skeleton_(SkeletonSnapshot(body.GetSkeleton())),
  is_visible_(body.IsVisible()) {}

void BodySnapshot::SetVisible(bool visible) {
  is_visible_ = visible;
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
  return ds >> s.is_visible_ >> s.skeleton_;
}

QDataStream& operator<<(QDataStream& ds, const BodySnapshot& s) {
  return ds << s.is_visible_ << s.skeleton_;
}