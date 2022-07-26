#ifndef CARTOON_MAKER_UI_CARTOONSCENE_H_
#define CARTOON_MAKER_UI_CARTOONSCENE_H_

#include <QGraphicsScene>

class CartoonScene : public QGraphicsScene {
  Q_OBJECT
 public:
  CartoonScene(QObject *parent = nullptr);
 signals:
  void Changed();
 protected:
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif //CARTOON_MAKER_UI_CARTOONSCENE_H_
