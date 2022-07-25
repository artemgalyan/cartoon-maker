#include "SidePoint.h"
#include "point_utils.h"
#include <QGraphicsSceneMouseEvent>

const QColor SidePoint::BorderColor = QColor("#79553D");

double SidePoint::GetRadius() const {
  return radius_;
}

double SidePoint::GetAngle() const {
  return angle_;
}

SidePoint::SidePoint(const double radius, double angle, Point *parent) : Point(radius * cos(angle),
                                                                                   radius * sin(angle),
                                                                                   parent),
                                                                             radius_(radius),
                                                                             angle_(angle) {
  lineToParent_ = new QGraphicsLineItem(QLineF(QPointF(0, 0), pos()), parentItem());
  connect(this, &QGraphicsObject::xChanged, this, &SidePoint::onPosChanged);
  connect(this, &QGraphicsObject::yChanged, this, &SidePoint::onPosChanged);
}

void SidePoint::AddMouseMoveEventListener(std::function<void(SidePoint *)> function) {
  listeners_.push_back(function);
  function(this);
}

void SidePoint::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  lineToParent_->setLine(QLineF(QPointF(0, 0), pos()));
  QPointF relativelyToParent = event->scenePos() - parentItem()->scenePos();
  angle_ = PointUtils::GetAngle(relativelyToParent);
  setPos(radius_ * cos(angle_), radius_ * sin(angle_));
}

void SidePoint::onPosChanged() {
  for (auto function : listeners_) {
    function(this);
  }
}

QPen SidePoint::GetStyle() const {
  QPen pen;
  pen.setBrush(QBrush(Point::PointColor, Qt::SolidPattern));
  pen.setColor(BorderColor);
  return pen;
}

Point *SidePoint::Clone(Point *parent) const {
  return new SidePoint(radius_, angle_, parent);
}

void SidePoint::SetAngle(double angle) {
  angle_ = angle;
}