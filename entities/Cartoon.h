#ifndef CARTOON_MAKER_ENTITIES_CARTOON_H_
#define CARTOON_MAKER_ENTITIES_CARTOON_H_

#include <QVector>
#include <QString>

#include "Frame.h"

class Cartoon {
 public:
  explicit Cartoon(QVector<QString>, QVector<Frame>);
  [[nodiscard]] const QVector<QString>& GetEntities() const;
  [[nodiscard]] const QVector<Frame>& GetFrames() const;
  friend QDataStream& operator>>(QDataStream&, Cartoon&);
  friend QDataStream& operator<<(QDataStream&, const Cartoon&);
 private:
  QVector<QString> entities_;
  QVector<Frame> frames_;
};

#endif //CARTOON_MAKER_ENTITIES_CARTOON_H_
