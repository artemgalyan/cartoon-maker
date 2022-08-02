#ifndef CARTOON_MAKER_ENTITIES_SKELETON_SKELETON_H_
#define CARTOON_MAKER_ENTITIES_SKELETON_SKELETON_H_

#include <QVector>

#include "point/point.h"
#include "point/MainPoint.h"
#include "SkeletonSnapshot.h"

class Skeleton {
 public:
  explicit Skeleton(QVector<Point*> points);
  Skeleton(const Skeleton&) noexcept;
  [[nodiscard]] const QVector<Point*>& GetPoints() const;
  [[nodiscard]] MainPoint* GetMainPoint() const;
  [[nodiscard]] Skeleton Clone() const;
  void SetVisible(bool visible) const;
  void LoadSnapshot(const SkeletonSnapshot&);
  [[nodiscard]] bool IsVisible() const;
  [[nodiscard]] double GetScale() const;
  void SetPointsVisibility(bool value);
 private:
  QVector<Point*> points_;
};

#endif //CARTOON_MAKER_ENTITIES_SKELETON_SKELETON_H_
