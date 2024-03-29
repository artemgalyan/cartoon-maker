#ifndef CARTOON_MAKER_ENTITIES_BODY_BODYSNAPSHOT_H_
#define CARTOON_MAKER_ENTITIES_BODY_BODYSNAPSHOT_H_

#include "Body.h"
#include "../skeleton/SkeletonSnapshot.h"

class BodySnapshot {
 public:
  explicit BodySnapshot() = default;
  explicit BodySnapshot(const Body&);
  BodySnapshot(SkeletonSnapshot  skeleton, bool is_visible);
  [[nodiscard]] SkeletonSnapshot GetSkeleton() const;
  [[nodiscard]] bool IsVisible() const;
  void SetVisible(bool visible);
  [[nodiscard]] double GetZIndex() const;
  void SetZIndex(double z);
  [[nodiscard]] double GetScale() const;
  void SetScale(double scale);
  friend QDataStream& operator>>(QDataStream&, BodySnapshot&);
  friend QDataStream& operator<<(QDataStream&, const BodySnapshot&);
 private:
  SkeletonSnapshot skeleton_;
  bool is_visible_ = true;
};

#endif //CARTOON_MAKER_ENTITIES_BODY_BODYSNAPSHOT_H_