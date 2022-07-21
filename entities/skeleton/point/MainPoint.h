#ifndef CARTOON_MAKER_LOGIC_SKELETON_POINT_MAINPOINT_H_
#define CARTOON_MAKER_LOGIC_SKELETON_POINT_MAINPOINT_H_

#include "point.h"

class MainPoint : public Point {
 public:
  const static QColor BorderColor;
  const static int BorderWidth = 5;
  explicit MainPoint(double x, double y);
  [[nodiscard]] QRectF boundingRect() const override;
  Point* Clone(MainPoint* parent = nullptr) const override;
 protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
 private:
  [[nodiscard]] QPen GetStyle() const override;
};

#endif //CARTOON_MAKER_LOGIC_SKELETON_POINT_MAINPOINT_H_
