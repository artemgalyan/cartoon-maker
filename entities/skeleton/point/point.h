#ifndef CARTOON_MAKER_LOGIC_SKELETON_POINT_POINT_H_
#define CARTOON_MAKER_LOGIC_SKELETON_POINT_POINT_H_

#include <QGraphicsObject>
#include <QPainter>
#include <QPen>
#include <QColor>

class Point : public QGraphicsObject {
 public:
  const static QColor PointColor;
  const static int PaintRadius = 20;
  Point(double x, double y, Point* parent = nullptr) : QGraphicsObject(parent) {
    setPos(x, y);
  };
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

const QColor Point::PointColor = QColor("#F39C12");

#endif //CARTOON_MAKER_LOGIC_SKELETON_POINT_POINT_H_
