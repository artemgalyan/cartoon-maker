#ifndef CARTOON_MAKER_ENTITIES_BODY_BODYSNAPSHOT_H_
#define CARTOON_MAKER_ENTITIES_BODY_BODYSNAPSHOT_H_

#include "Body.h"
#include "../skeleton/SkeletonSnapshot.h"

class BodySnapshot {
 public:
  // TODO: Add scale field
  BodySnapshot(const Body&);
  BodySnapshot(SkeletonSnapshot  skeleton, bool isVisible);
  [[nodiscard]] SkeletonSnapshot GetSkeleton() const;
  [[nodiscard]] bool IsVisible() const;
  void SetVisible(bool visible);
  [[nodiscard]] double GetZIndex() const;
  void SetZIndex(double z);
 private:
  SkeletonSnapshot skeleton_;
  bool isVisible_ = true;
  double zIndex_;
};

#endif //CARTOON_MAKER_ENTITIES_BODY_BODYSNAPSHOT_H_
