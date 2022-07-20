#ifndef CARTOON_MAKER_ENTITIES_SKELETON_SKELETON_H_
#define CARTOON_MAKER_ENTITIES_SKELETON_SKELETON_H_

#include <QVector>

#include "point/point.h"

class Skeleton {
 public:
  explicit Skeleton(QVector<Point*> points);;
  [[nodiscard]] const QVector<Point*>& GetPoints() const;
 private:
  QVector<Point*> points_;
};

#endif //CARTOON_MAKER_ENTITIES_SKELETON_SKELETON_H_
