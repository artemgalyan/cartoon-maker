
#include "CartoonScene.h"

CartoonScene::CartoonScene(QObject *parent) : QGraphicsScene(parent) {}

void CartoonScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  emit Changed();
  QGraphicsScene::mouseReleaseEvent(event);
}
