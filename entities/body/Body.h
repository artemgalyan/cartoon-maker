#ifndef CARTOON_MAKER_ENTITIES_BODY_BODY_H_
#define CARTOON_MAKER_ENTITIES_BODY_BODY_H_

#include "../skeleton/Skeleton.h"
#include "../../logic/images/Image.h"
#include <QGraphicsScene>

class Body {
 public:
  explicit Body(const Skeleton &, QVector<Image *>, QHash<Image *, int>, QString);
  //Body(const Body &)=default;
  Body& operator=(const Body&) = default;
  [[nodiscard]] QString GetBodyType() const;
  [[nodiscard]] const Skeleton &GetSkeleton() const;
  void AddTo(QGraphicsScene *scene) const;
  [[nodiscard]] Body *Clone() const;
 private:
  static double ToDegrees(double rad);
  void ConnectImagesToPoints();
  Skeleton skeleton_;
  QVector<Image *> images_;
  QHash<Image *, int> indexFromImage_;
  QString type_;
};

#endif //CARTOON_MAKER_ENTITIES_BODY_BODY_H_
