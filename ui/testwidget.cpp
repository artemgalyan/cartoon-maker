#include "testwidget.h"
#include "ui_testwidget.h"

#include "../entities/body/factory/BodyFactory.h"

TestWidget::TestWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::TestWidget) {
  ui->setupUi(this);
  view_ = ui->graphicsView;
  view_->setRenderHint(QPainter::Antialiasing, true);
  scene_ = new QGraphicsScene();
  view_->setScene(scene_);
  auto factory = BodyFactory::Instance();
  auto snake = factory->CreateByType("Snake");
  snake->AddTo(scene_);
  auto pig = factory->CreateByType("Pig");
  pig->AddTo(scene_);
}

TestWidget::~TestWidget() {
  delete ui;
}

void TestWidget::resizeEvent(QResizeEvent *event) {
  scene_->setSceneRect(0, 0, view_->width(), view_->height());
  QWidget::resizeEvent(event);
}
