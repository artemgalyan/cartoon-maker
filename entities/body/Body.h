#ifndef CARTOON_MAKER_ENTITIES_BODY_BODY_H_
#define CARTOON_MAKER_ENTITIES_BODY_BODY_H_

#include "../skeleton/Skeleton.h"
#include <QImage>
#include <QGraphicsScene>

class Body {
  // TODO: function Image <-> ID; -MakeBody() : void; fix constructor
 public:
  Body(const Skeleton &, QVector<QImage *>/*, function Image -> ID*/);
  QString GetBodyType();
  const Skeleton &GetSkeleton();
  void AddTo(QGraphicsScene *scene) const;
 private:
  Skeleton skeleton_;
  QVector<QImage *> images_;
  const QString type_;
};

#endif //CARTOON_MAKER_ENTITIES_BODY_BODY_H_
