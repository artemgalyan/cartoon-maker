#include "cartooneditor.h"
#include "ui_cartooneditor.h"

#include <QGraphicsScene>
#include <QPainter>

CartoonEditor::CartoonEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CartoonEditor) {
  ui->setupUi(this);
  ui->graphicsView->setScene(new QGraphicsScene());
  auto scene = ui->graphicsView->scene();
  qDebug() << scene;
  scene->addEllipse(50, 50, 100, 100);

  frames_.push_back(MakeFrame());

  frameWidget_ = new FrameWidget(QVector<QPixmap>(), this);
  ui->framesArea->setAlignment(Qt::AlignVCenter);
  ui->framesArea->setWidget(frameWidget_);
  connect(frameWidget_, SIGNAL(FrameSelected(int)), this, SLOT(SwitchToFrame(int)));
  connect(ui->submitButton, SIGNAL(clicked(bool)), this, SLOT(AddFrame()));
}

CartoonEditor::~CartoonEditor() {
  delete ui;
}

void CartoonEditor::LoadFrame(const Frame &frame) {
  const auto &snapshots = frame.GetSnapshots();
  for (int i = 0; i < snapshots.count(); ++i) {
    bodies_[i].LoadSnapshot(snapshots[i]);
  }
}

void CartoonEditor::AddFrame() {
  frames_.insert(currentFrame_ + 1, frames_[currentFrame_]);
  ++currentFrame_;
  frameWidget_->AddFrame(GetScenePixmap());
}

Frame CartoonEditor::MakeFrame() const {
  QVector<BodySnapshot> snaps;
  for (const auto &body : bodies_) {
    snaps.push_back(BodySnapshot(body));
  }
  return Frame(snaps);
}

void CartoonEditor::UpdateFrame() {
  frames_[currentFrame_] = MakeFrame();
  frameWidget_->UpdateFrame(currentFrame_, GetScenePixmap());
}

QPixmap CartoonEditor::GetScenePixmap() const {
  auto scene = ui->graphicsView->scene();

  QImage image(ui->graphicsView->sceneRect().size().toSize(), QImage::Format_ARGB32);
  image.fill(Qt::white);

  QPainter painter(&image);
  painter.setRenderHint(QPainter::Antialiasing);
  ui->graphicsView->render(&painter);
  return QPixmap::fromImage(image);
}

void CartoonEditor::SwitchToFrame(int index) {
  currentFrame_ = index;
  LoadFrame(frames_[currentFrame_]);
}
