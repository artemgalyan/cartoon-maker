#include "MainPoint.h"

#include <QPen>
#include <QColor>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

#include "point_utils.h"

const QColor MainPoint::BorderColor = QColor("#E74C3C");

MainPoint::MainPoint(double x, double y) : Point(x, y) {}

QPen MainPoint::GetStyle() const {
  QPen pen;
  pen.setBrush(QBrush(Point::PointColor, Qt::SolidPattern));
  pen.setColor(BorderColor);
  pen.setWidth(BorderWidth);
  return pen;
}
void MainPoint::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  if (scene() == nullptr)
    return;
  QRectF sceneRect = scene()->sceneRect();
  setPos(PointUtils::FixPointPositionInsideRect(sceneRect, event->scenePos()));
}

QRectF MainPoint::boundingRect() const {
  double r = Point::PaintRadius + BorderWidth;
  return {-r, -r, 2 * r, 2 * r};
}

Point *MainPoint::Clone(Point *parent) const {
  return new MainPoint(x(), y());
}

void MainPoint::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
  setZValue(zValue() - 1);
  auto* menu = new QMenu();
  menu->addAction("Delete");
  menu->addAction("Place behind");
  menu->exec(QCursor::pos());
  QGraphicsItem::contextMenuEvent(event);
}
