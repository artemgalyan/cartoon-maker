#ifndef CARTOON_MAKER_LOGIC_SKELETON_POINT_SIDEPOINT_H_
#define CARTOON_MAKER_LOGIC_SKELETON_POINT_SIDEPOINT_H_

#include "point.h"
#include "MainPoint.h"
#include <QGraphicsLineItem>

class SidePoint : public Point {
  Q_OBJECT
  Q_PROPERTY(double angle READ GetAngle WRITE SetAngle)
 public:
  const static QColor BorderColor;
  SidePoint(double radius, double angle, Point* parent);
  [[nodiscard]] double GetRadius() const;
  [[nodiscard]] double GetAngle() const;
  void AddMouseMoveEventListener(const std::function<void(SidePoint*)>& function);
  Point* Clone(Point* parent) const override;
  void SetAngle(double angle);
  void UpdatePos();
  void UpdateLineToParent();
  [[nodiscard]] PointSnapshot CreateSnapshot() const override;
 protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
 private slots:
  void onPosChanged();
 private:
  [[nodiscard]] QPen GetStyle() const override;
  const double radius_;
  double angle_;
  QGraphicsLineItem* line_to_parent_;
  QVector<std::function<void(SidePoint*)>> listeners_;
};

#endif //CARTOON_MAKER_LOGIC_SKELETON_POINT_SIDEPOINT_H_
