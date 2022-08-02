#ifndef CARTOON_MAKER_ENTITIES_FRAME_H_
#define CARTOON_MAKER_ENTITIES_FRAME_H_

#include <QVector>

#include "body/BodySnapshot.h"

class Frame {
 public:
  explicit Frame() = default;
  explicit Frame(QVector<BodySnapshot>);
  [[nodiscard]] const QVector<BodySnapshot>& GetSnapshots() const;
  void AddBodySnapshot(const BodySnapshot& s);
  friend QDataStream& operator>>(QDataStream&, Frame&);
  friend QDataStream& operator<<(QDataStream&, const Frame&);
 private:
  QVector<BodySnapshot> snapshots_;
};

#endif //CARTOON_MAKER_ENTITIES_FRAME_H_
