#include "cartooneditor.h"
#include "ui_cartooneditor.h"
#include "../entities/body/factory/BodyFactory.h"
#include "CartoonScene.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QPainter>
#include <QKeyEvent>
#include <QKeyCombination>
#include <QAbstractButton>

CartoonEditor::CartoonEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CartoonEditor) {
  ui->setupUi(this);
  SetupGraphicsView();
  SetupFrameWidget();
  SetupModelWidget();
  MakeConnects();

  QTimer::singleShot(100, [this] { AddFrame(); });
}

void CartoonEditor::MakeConnects() {
  auto scene = dynamic_cast<CartoonScene *>(ui->graphicsView->scene());
  if (scene == nullptr) {
    throw std::logic_error("Scene is not CartoonScene*");
  }

  connect(frameWidget_, SIGNAL(FrameSelected(int)), this, SLOT(SwitchToFrame(int)));
  connect(ui->submitButton, SIGNAL(clicked(bool)), this, SLOT(AddFrame()));
  connect(scene, SIGNAL(Changed()), this, SLOT(SceneChanged()));
}

void CartoonEditor::SetupModelWidget() {
  auto factory = BodyFactory::Instance();
  modelWidget_ = new ModelWidget(factory->GetPreviews(), this, ui->modelsArea);
  ui->modelsArea->setWidget(modelWidget_);
}

void CartoonEditor::SetupFrameWidget() {
  frameWidget_ = new FrameWidget(QVector<QPixmap>(), ui->framesArea);
  ui->framesArea->setWidget(frameWidget_);
}

void CartoonEditor::SetupGraphicsView() {
  auto cartoonScene = new CartoonScene();
  ui->graphicsView->setScene(cartoonScene);
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

CartoonEditor::~CartoonEditor() {
  delete ui;
}

void CartoonEditor::LoadFrame(const Frame &frame) {
  const auto &snapshots = frame.GetSnapshots();
  for (int i = 0; i < snapshots.count(); ++i) {
    bodies_[i]->LoadSnapshot(snapshots[i]);
  }
  UpdateFrame();
}

void CartoonEditor::AddFrame() {
  ClearPrevStates();
  if (frames_.isEmpty()) {
    frames_.push_back(MakeFrame());
    currentFrame_ = 0;
    frameWidget_->AddFrame(GetScenePixmap());
  } else {
    frames_.insert(currentFrame_ + 1, frames_[currentFrame_]);
    frameWidget_->InsertFrame(currentFrame_, GetScenePixmap());
    ++currentFrame_;
  }
  UpdateFrame();
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
  UpdateFrame();
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

  BodySnapshot addedBody(*b);
  addedBody.SetVisible(false);

  for (int i = 0; i < frames_.count(); ++i) {
    if (i != currentFrame_) {
      frames_[i].AddBodySnapshot(addedBody);
    }
  }
  ClearPrevStates();
  PushCurrentState();
  UpdateFrame();
}

void CartoonEditor::Restore() {
  if (previous_frames_.empty())
    return;
  frames_ = previous_frames_.top().second;
  currentFrame_ = previous_frames_.top().first;
  previous_frames_.pop();
  LoadFrame(frames_[currentFrame_]);
}

void CartoonEditor::keyPressEvent(QKeyEvent *event) {
  if (event->matches(QKeySequence::Undo)) {
    Restore();
  }
  QWidget::keyPressEvent(event);
}

void CartoonEditor::SceneChanged() {
  UpdateFrame();
  PushCurrentState();
}

void CartoonEditor::PushCurrentState() {
  previous_frames_.push({currentFrame_, frames_});
}

void CartoonEditor::ClearPrevStates() {
  while (!previous_frames_.empty())
    previous_frames_.pop();
}
