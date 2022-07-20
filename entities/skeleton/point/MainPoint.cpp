#include "MainPoint.h"

#include <QPen>
#include <QColor>

MainPoint::MainPoint(double x, double y) : Point(x, y) {}

QPen MainPoint::GetStyle() const {
  QPen pen;
  pen.setBrush(QBrush(Point::PointColor, Qt::SolidPattern));
  pen.setColor(BorderColor);
  pen.setWidth(BorderWidth);
  return pen;
}
