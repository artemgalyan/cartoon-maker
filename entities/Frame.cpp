#include "Frame.h"


const QVector<BodySnapshot> &Frame::GetSnapshots() const {
  return snapshots_;
}
Frame::Frame(QVector<BodySnapshot> s) : snapshots_(std::move(s)) {}

void Frame::AddBodySnapshot(const BodySnapshot &s) {
  snapshots_.push_back(s);
}

QDataStream& operator>>(QDataStream& ds, Frame& frame) {
  return ds >> frame.snapshots_;
}

QDataStream& operator<<(QDataStream& ds, const Frame& frame) {
  return ds << frame.snapshots_;
}