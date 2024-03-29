#ifndef CARTOON_MAKER_LOGIC_SKELETON_POINT_POINT_H_
#define CARTOON_MAKER_LOGIC_SKELETON_POINT_POINT_H_

#include <QGraphicsObject>
#include <QPainter>
#include <QPen>
#include <QColor>

class PointSnapshot;

class Point : public QGraphicsObject {
 public:
  const static QColor PointColor;
  const static int PaintRadius = 5;
  Point(double x, double y, Point *parent = nullptr);
  [[nodiscard]] QRectF boundingRect() const override;
  virtual Point *Clone(Point *parent) const = 0;
  [[nodiscard]] virtual PointSnapshot CreateSnapshot() const = 0;
  void SetVisible(bool visible);
 protected:
  bool visible_ = true;
 private:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
  [[nodiscard]] virtual QPen GetStyle() const = 0;
};

#endif //CARTOON_MAKER_LOGIC_SKELETON_POINT_POINT_H_
