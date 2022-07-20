#include "testwidget.h"
#include "ui_TestWidget.h"

TestWidget::TestWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::TestWidget) {
  ui->setupUi(this);
  view_ = ui->graphicsView;
  scene_ = new QGraphicsScene();
  view_->setScene(scene_);
}

TestWidget::~TestWidget() {
  delete ui;
}

void TestWidget::resizeEvent(QResizeEvent *event) {
  scene_->setSceneRect(0, 0, view_->width(), view_->height());
  QWidget::resizeEvent(event);
}
