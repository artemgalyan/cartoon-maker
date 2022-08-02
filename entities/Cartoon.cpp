#include "Cartoon.h"

Cartoon::Cartoon(QVector<QString> enitites, QVector<Frame> frames)
    : entities_(std::move(enitites)), frames_(std::move(frames)) {}

const QVector<QString> &Cartoon::GetEntities() const {
  return entities_;
}

const QVector<Frame> &Cartoon::GetFrames() const {
  return frames_;
}

QDataStream& operator>>(QDataStream& ds, Cartoon& c) {
  return ds >> c.entities_ >> c.frames_;
}

QDataStream& operator<<(QDataStream& ds, const Cartoon& c) {
  return ds << c.entities_ << c.frames_;
}