#ifndef CARTOON_MAKER_LOGIC_SKELETON_POINT_POINT_H_
#define CARTOON_MAKER_LOGIC_SKELETON_POINT_POINT_H_

#include <QGraphicsObject>
#include <QPainter>
#include <QPen>
#include <QColor>

class MainPoint;

class Point : public QGraphicsObject {
 public:
  const static QColor PointColor;
  const static int PaintRadius = 20;
  Point(double x, double y, Point* parent = nullptr);
  [[nodiscard]] QRectF boundingRect() const override;
  virtual Point* Clone(MainPoint* parent) const = 0;
 private:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
  [[nodiscard]] virtual QPen GetStyle() const = 0;
};

#endif //CARTOON_MAKER_LOGIC_SKELETON_POINT_POINT_H_
