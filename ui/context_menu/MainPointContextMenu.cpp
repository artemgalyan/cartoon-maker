#include "MainPointContextMenu.h"
#include "widgets/scaleslider/ScaleSlider.h"

MainPointContextMenu::MainPointContextMenu(MainPoint *point) : point_(point) {
  setMinimumWidth(200);
  auto delete_action = new QAction("Delete");
  connect(delete_action, &QAction::triggered, this, &MainPointContextMenu::DeletePoint);
  addAction(delete_action);
  addSection("Scale");
  auto scale = new ScaleSlider(point_->scale());
  addAction(scale);
  connect(scale, &ScaleSlider::ValueChanged, this, &MainPointContextMenu::ScaleChanged);
  addSeparator();
  auto place_behind = new QAction("Place behind");
  connect(place_behind, &QAction::triggered, this, &MainPointContextMenu::PlaceBehind);
  addAction(place_behind);
  auto place_in_front = new QAction("Place in front");
  connect(place_in_front, &QAction::triggered, this, &MainPointContextMenu::PlaceInFront);
  addAction(place_in_front);
}

void MainPointContextMenu::DeletePoint() {
  point_->hide();
}

void MainPointContextMenu::ScaleChanged(double new_scale) {
  point_->setScale(new_scale);
}

void MainPointContextMenu::PlaceBehind() {
  point_->setZValue(point_->zValue() - 1);
}

void MainPointContextMenu::PlaceInFront() {
  point_->setZValue(point_->zValue() + 1);
}
