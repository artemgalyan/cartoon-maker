#include "CartoonScene.h"

#include <QGraphicsView>
#include <QPainter>

CartoonScene::CartoonScene(QGraphicsView *view, QObject *parent) : view_(view), QGraphicsScene(parent) {}

void CartoonScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  emit Changed();
  QGraphicsScene::mouseReleaseEvent(event);
}

QPixmap CartoonScene::GetScenePixmap() const {
  QImage image(view_->sceneRect().size().toSize(), QImage::Format_ARGB32);
  image.fill(Qt::white);
  QPainter painter(&image);
  painter.setRenderHint(QPainter::Antialiasing);
  view_->render(&painter);
  return QPixmap::fromImage(image);
}

Frame CartoonScene::MakeFrame() const {
  QVector<BodySnapshot> snaps;
  for (const auto &body : bodies_) {
    snaps.push_back(BodySnapshot(*body));
  }
  return Frame(snaps);
}

void CartoonScene::LoadFrame(const Frame &frame) {
  const auto &snapshots = frame.GetSnapshots();
  for (int i = 0; i < snapshots.count(); ++i) {
    bodies_[i]->LoadSnapshot(snapshots[i]);
  }
}

void CartoonScene::AddBody(Body *b) {
  bodies_.push_back(b);
}

void CartoonScene::Clear() {
  bodies_.clear();
  clear();
}

void CartoonScene::ForceUpdateSignal() {
  emit Changed();
}

const QVector<Body*>& CartoonScene::GetBodies() const {
  return bodies_;
}

void CartoonScene::LeaveNFirstBodiesOnTheScene(int n) {
  auto index = n;
  while (index != bodies_.count()) {
    bodies_[index]->SetVisible(false);
    delete bodies_[index];
    bodies_.remove(index);
  }
}

QVector<QString> CartoonScene::GetEntitiesNameList() const {
  QVector<QString> result;
  for (const auto& body: bodies_) {
    result.push_back(body->GetBodyType());
  }
  return result;
}
