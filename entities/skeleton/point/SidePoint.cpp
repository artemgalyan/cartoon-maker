#include "SidePoint.h"
#include "point_utils.h"
#include "PointSnapshot.h"

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
  line_to_parent_ = new QGraphicsLineItem(QLineF(QPointF(0, 0), pos()), parentItem());
  connect(this, &QGraphicsObject::xChanged, this, &SidePoint::onPosChanged);
  connect(this, &QGraphicsObject::yChanged, this, &SidePoint::onPosChanged);
}

void SidePoint::AddMouseMoveEventListener(const std::function<void(SidePoint *)>& function) {
  listeners_.push_back(function);
  function(this);
}

void SidePoint::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  QPointF relativelyToParent = event->scenePos() - parentItem()->scenePos();
  angle_ = PointUtils::GetAngle(relativelyToParent);
  UpdatePos();
}

void SidePoint::onPosChanged() {
  UpdateLineToParent();
  for (const auto& function : listeners_) {
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
  auto result = new SidePoint(radius_, angle_, parent);
  result->setFlag(QGraphicsItem::ItemIsMovable, flags().testFlag(QGraphicsItem::ItemIsMovable));
  for (const auto& listener: listeners_) {
    result->AddMouseMoveEventListener(listener);
  }
  return result;
}

void SidePoint::SetAngle(double angle) {
  angle_ = angle;
  UpdatePos();
}

void SidePoint::UpdatePos() {
  setPos(radius_ * cos(angle_), radius_ * sin(angle_));
}

void SidePoint::UpdateLineToParent() {
  line_to_parent_->setVisible(visible_);
  line_to_parent_->setLine(QLineF(QPointF(0, 0), pos()));
}

PointSnapshot SidePoint::CreateSnapshot() const {
  return {radius_, angle_};
}
