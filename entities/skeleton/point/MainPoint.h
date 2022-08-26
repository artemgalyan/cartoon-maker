#ifndef CARTOON_MAKER_LOGIC_SKELETON_POINT_MAINPOINT_H_
#define CARTOON_MAKER_LOGIC_SKELETON_POINT_MAINPOINT_H_

#include "point.h"

class MainPoint : public Point {
  Q_PROPERTY(double zvalue READ zValue WRITE setZValue);
 public:
  const static QColor BorderColor;
  const static int BorderWidth = 5;
  explicit MainPoint(double x, double y);
  [[nodiscard]] QRectF boundingRect() const override;
  Point* Clone(Point* parent) const override;
  [[nodiscard]] PointSnapshot CreateSnapshot() const override;
 protected:
  void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
 private:
  [[nodiscard]] QPen GetStyle() const override;
};

#endif //CARTOON_MAKER_LOGIC_SKELETON_POINT_MAINPOINT_H_
