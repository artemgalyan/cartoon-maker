#include "point.h"

const QColor Point::PointColor("#F39C12");

Point::Point(double x, double y, Point *parent) : QGraphicsObject(parent) {
  setPos(x, y);
}

QRectF Point::boundingRect() const {
  return {-PaintRadius, -PaintRadius, 2 * PaintRadius, 2 * PaintRadius};
}

void Point::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  painter->save();
  QPen pen = this->GetStyle();
  painter->setPen(pen);
  painter->drawEllipse(boundingRect());
  painter->restore();
}
