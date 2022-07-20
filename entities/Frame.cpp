#include "Frame.h"


const QVector<BodySnapshot> &Frame::GetSnapshots() const {
  return snapshots_;
}
Frame::Frame(QVector<BodySnapshot> s) : snapshots_(std::move(s)) {

}
