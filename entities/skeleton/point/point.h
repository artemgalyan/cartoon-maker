#ifndef CARTOON_MAKER_LOGIC_SKELETON_POINT_POINT_H_
#define CARTOON_MAKER_LOGIC_SKELETON_POINT_POINT_H_

#include <QGraphicsObject>
#include <QPainter>
#include <QPen>

class Point : public QGraphicsObject {
 public:
  Point(int x, int y, Point* parent) : QGraphicsObject(parent) {
    setPos(x, y);
  };
  const static int PaintRadius = 20;
  [[nodiscard]] QRectF boundingRect() const override {
    return {-PaintRadius, -PaintRadius, 2 * PaintRadius, 2 * PaintRadius};
  }
 private:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
    painter->save();
    QPen pen = this->GetStyle();
    painter->setPen(pen);
    painter->drawEllipse(boundingRect());
    painter->restore();
  }
  [[nodiscard]] virtual QPen GetStyle() const = 0;
};

#endif //CARTOON_MAKER_LOGIC_SKELETON_POINT_POINT_H_
