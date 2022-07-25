#include "cartooneditor.h"
#include "ui_cartooneditor.h"
#include "../entities/body/factory/BodyFactory.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QPainter>

CartoonEditor::CartoonEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CartoonEditor) {
  ui->setupUi(this);
  ui->graphicsView->setScene(new QGraphicsScene());
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  frames_.push_back(MakeFrame());

  frameWidget_ = new FrameWidget(QVector<QPixmap>(), this);
  ui->framesArea->setAlignment(Qt::AlignVCenter);
  ui->framesArea->setWidget(frameWidget_);
  connect(frameWidget_, SIGNAL(FrameSelected(int)), this, SLOT(SwitchToFrame(int)));
  connect(ui->submitButton, SIGNAL(clicked(bool)), this, SLOT(AddFrame()));

  auto factory = BodyFactory::Instance();
  AddBody(factory->CreateByType("Pig"));
  AddBody(factory->CreateByType("Snake"));
  QTimer::singleShot(100, [this] { AddFrame(); });
}

CartoonEditor::~CartoonEditor() {
  delete ui;
}

void CartoonEditor::LoadFrame(const Frame &frame) {
  const auto &snapshots = frame.GetSnapshots();
  for (int i = 0; i < snapshots.count(); ++i) {
    bodies_[i]->LoadSnapshot(snapshots[i]);
  }
}

void CartoonEditor::AddFrame() {
  if (currentFrame_ == -1) {
    frames_.push_back(MakeFrame());
  } else {
    UpdateFrame();
    frames_.push_back(frames_.last());
  }
  ++currentFrame_;
  frameWidget_->AddFrame(GetScenePixmap());
}

Frame CartoonEditor::MakeFrame() const {
  QVector<BodySnapshot> snaps;
  for (const auto &body : bodies_) {
    snaps.push_back(BodySnapshot(*body));
  }
  return Frame(snaps);
}

void CartoonEditor::UpdateFrame() {
  frames_[currentFrame_] = MakeFrame();
  frameWidget_->UpdateFrame(currentFrame_, GetScenePixmap());
}

QPixmap CartoonEditor::GetScenePixmap() const {
  QImage image(ui->graphicsView->sceneRect().size().toSize(), QImage::Format_ARGB32);
  image.fill(Qt::white);

  QPainter painter(&image);
  painter.setRenderHint(QPainter::Antialiasing);
  ui->graphicsView->render(&painter);
  return QPixmap::fromImage(image);
}

void CartoonEditor::SwitchToFrame(int index) {
  frames_[currentFrame_] = MakeFrame();
  currentFrame_ = index;
  LoadFrame(frames_[currentFrame_]);
}

void CartoonEditor::resizeEvent(QResizeEvent *event) {
  ui->graphicsView->scene()->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
  QWidget::resizeEvent(event);
}

void CartoonEditor::AddBody(Body *b) {
  bodies_.push_back(b);
  b->AddTo(ui->graphicsView->scene());
}
