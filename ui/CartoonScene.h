#ifndef CARTOON_MAKER_UI_CARTOONSCENE_H_
#define CARTOON_MAKER_UI_CARTOONSCENE_H_

#include <QGraphicsScene>
#include "../entities/Frame.h"

class CartoonScene : public QGraphicsScene {
  Q_OBJECT
 public:
  explicit CartoonScene(QGraphicsView* view, QObject *parent = nullptr);
  [[nodiscard]] Frame MakeFrame() const;
  void LoadFrame(const Frame &frame);
  [[nodiscard]] QPixmap GetScenePixmap() const;
  void AddBody(Body *);
  void Clear();
  void ForceUpdateSignal();
  [[nodiscard]] const QVector<Body*>& GetBodies() const;
  void LeaveNFirstBodiesOnTheScene(int n);
  [[nodiscard]] QVector<QString> GetEntitiesNameList() const;
 signals:
  void Changed();
 protected:
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
 private:
  QVector<Body *> bodies_;
  QGraphicsView *view_;
};

#endif //CARTOON_MAKER_UI_CARTOONSCENE_H_
