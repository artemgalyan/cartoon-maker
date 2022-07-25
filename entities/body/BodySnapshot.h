#ifndef CARTOON_MAKER_ENTITIES_BODY_BODYSNAPSHOT_H_
#define CARTOON_MAKER_ENTITIES_BODY_BODYSNAPSHOT_H_

#include "Body.h"
#include "../skeleton/SkeletonSnapshot.h"

class BodySnapshot {
 public:
  BodySnapshot(const Body&);
  BodySnapshot(SkeletonSnapshot  skeleton, bool isVisible);
  [[nodiscard]] SkeletonSnapshot GetSkeleton() const;
  [[nodiscard]] bool IsVisible() const;
 private:
  SkeletonSnapshot skeleton_;
  bool isVisible_ = true;
};

#endif //CARTOON_MAKER_ENTITIES_BODY_BODYSNAPSHOT_H_
