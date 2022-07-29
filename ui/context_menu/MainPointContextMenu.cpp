#include "MainPointContextMenu.h"
#include "widgets/scaleslider/ScaleSlider.h"
#include "../CartoonScene.h"

MainPointContextMenu::MainPointContextMenu(MainPoint *point) : point_(point) {
  setAttribute(Qt::WA_NoSystemBackground);
  setAttribute(Qt::WA_TranslucentBackground);
  setFont(QFont("Arial"));
  setMinimumWidth(200);
  auto delete_action = new QAction("Delete");
  delete_action->setIcon(QIcon(":/res/icons/menudelete.png"));
  connect(delete_action, &QAction::triggered, this, &MainPointContextMenu::DeletePoint);
  addAction(delete_action);
  addSection("Scale");
  auto scale = new ScaleSlider(point_->scale());
  addAction(scale);
  connect(scale, &ScaleSlider::ValueChanged, this, &MainPointContextMenu::ScaleChanged);
  addSection("z-indexes");
  auto place_behind = new QAction("Place behind");
  place_behind->setIcon(QIcon(":/res/icons/placeback.png"));
  connect(place_behind, &QAction::triggered, this, &MainPointContextMenu::PlaceBehind);
  addAction(place_behind);
  auto place_in_front = new QAction("Place in front");
  place_in_front->setIcon(QIcon(":/res/icons/placefront.png"));
  connect(place_in_front, &QAction::triggered, this, &MainPointContextMenu::PlaceInFront);
  addAction(place_in_front);
}

void MainPointContextMenu::DeletePoint() {
  point_->hide();
  ForceSceneUpdate();
}

void MainPointContextMenu::ScaleChanged(double new_scale) {
  point_->setScale(new_scale);
  ForceSceneUpdate();
}

void MainPointContextMenu::PlaceBehind() {
  point_->setZValue(point_->zValue() - 1);
  ForceSceneUpdate();
}

void MainPointContextMenu::PlaceInFront() {
  point_->setZValue(point_->zValue() + 1);
  ForceSceneUpdate();
}

void MainPointContextMenu::ForceSceneUpdate() const {
  auto scene = dynamic_cast<CartoonScene*>(point_->scene());
  if (scene == nullptr)
    return;
  scene->ForceUpdateSignal();
}
