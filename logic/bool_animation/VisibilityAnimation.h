#ifndef CARTOON_MAKER_LOGIC_BOOL_ANIMATION_VISIBILITYANIMATION_H_
#define CARTOON_MAKER_LOGIC_BOOL_ANIMATION_VISIBILITYANIMATION_H_

#include <QAbstractAnimation>
#include <QGraphicsItem>

class VisibilityAnimation : public QAbstractAnimation {
 public:
  VisibilityAnimation(bool value, QGraphicsItem* item);
  [[nodiscard]] int duration() const override;
  void updateCurrentTime(int currentTime) override;
 private:
  QGraphicsItem* item_;
  bool value_;
};

#endif //CARTOON_MAKER_LOGIC_BOOL_ANIMATION_VISIBILITYANIMATION_H_