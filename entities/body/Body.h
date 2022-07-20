#ifndef CARTOON_MAKER_ENTITIES_BODY_BODY_H_
#define CARTOON_MAKER_ENTITIES_BODY_BODY_H_

#include "../skeleton/Skeleton.h"
#include "../../logic/images/Image.h"
#include <QGraphicsScene>

class Body {
  // TODO: function Image <-> ID; -MakeBody() : void; fix constructor
 public:
  Body(Skeleton, QVector<Image *>/*, function Image -> ID*/);
  QString GetBodyType() const;
  const Skeleton &GetSkeleton() const;
  void AddTo(QGraphicsScene *scene) const;
 private:
  Skeleton skeleton_;
  QVector<Image *> images_;
  const QString type_;
};

#endif //CARTOON_MAKER_ENTITIES_BODY_BODY_H_
