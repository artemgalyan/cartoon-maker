#ifndef CARTOON_MAKER_ENTITIES_SKELETON_POINT_UTILS_H_
#define CARTOON_MAKER_ENTITIES_SKELETON_POINT_UTILS_H_

#include <QPointF>
#include <QRectF>

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
  static double DegreeToRadian(double degree){
    return (degree*std::numbers::pi)/180;

  }
  static QPointF FixPointPositionInsideRect(const QRectF &rect, QPointF point) {
    if (rect.contains(point)) {
      return point;
    }
    if (point.x() < 0) {
      point.setX(0);
    } else if (point.x() > rect.width()) {
      point.setX(rect.width());
    }
    if (point.y() < 0) {
      point.setY(0);
    }
    else if (point.y() > rect.height()) {
      point.setY(rect.height());
    }
    return point;
  }
};

#endif //CARTOON_MAKER_ENTITIES_SKELETON_POINT_UTILS_H_
