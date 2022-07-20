#ifndef CARTOON_MAKER_LOGIC_SKELETON_POINT_SIDEPOINT_H_
#define CARTOON_MAKER_LOGIC_SKELETON_POINT_SIDEPOINT_H_

#include "point.h"
#include "MainPoint.h"
#include <QGraphicsLineItem>

class SidePoint : public Point {
 public:
  const static QColor BorderColor;
  SidePoint(const double radius, double angle, MainPoint* parent);
  [[nodiscard]] double GetRadius() const;
  [[nodiscard]] double GetAngle() const;
  void AddMouseMoveEventListener(std::function<void(SidePoint*)> function);
 protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
 private slots:
  void onPosChanged();
 private:
  [[nodiscard]] QPen GetStyle() const override;
  const double radius_;
  double angle_;
  QGraphicsLineItem *lineToParent_;
  QVector<std::function<void(SidePoint *)>> listeners_;
};


#endif //CARTOON_MAKER_LOGIC_SKELETON_POINT_SIDEPOINT_H_
