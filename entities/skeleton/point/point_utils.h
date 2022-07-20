#ifndef CARTOON_MAKER_ENTITIES_SKELETON_POINT_UTILS_H_
#define CARTOON_MAKER_ENTITIES_SKELETON_POINT_UTILS_H_

#include <QPointF>

class PointUtils {
 public:
  static double GetDistance(QPointF a, QPointF b = QPointF(0, 0)) {
    double dx = a.x() - b.x();
    double dy = a.y() - b.y();
    return sqrt(dx * dx + dy * dy);
  }
  static double GetAngle(QPointF point) {
    double distance = sqrt(point.x() * point.x() + point.y() * point.y());
    double cosAngle = point.x() / distance;
    double angle = acos(cosAngle);
    if (point.y() < 0) {
      angle = 2 * std::numbers::pi - angle;
    }
    return angle;
  }
};

#endif //CARTOON_MAKER_ENTITIES_SKELETON_POINT_UTILS_H_
