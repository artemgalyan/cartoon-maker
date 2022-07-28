#include "cartooneditor.h"
#include "ui_cartooneditor.h"
#include "../entities/body/factory/BodyFactory.h"
#include "CartoonScene.h"
#include "../logic/factory/StyleManager.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QKeyCombination>
#include <QAbstractButton>
#include <QScrollBar>

CartoonEditor::CartoonEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CartoonEditor) {
  ui->setupUi(this);
  SetupGraphicsView();
  SetupFrameWidget();
  SetupModelWidget();
  MakeConnects();

  SetupStyles();
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
  ui->modelsArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

void CartoonEditor::SetupFrameWidget() {
  frameWidget_ = new FrameWidget(QVector<QPixmap>(), ui->framesArea);
  ui->framesArea->setWidget(frameWidget_);
  ui->framesArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

void CartoonEditor::SetupGraphicsView() {
  cartoonScene_ = new CartoonScene(ui->graphicsView);
  ui->graphicsView->setScene(cartoonScene_);
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

CartoonEditor::~CartoonEditor() {
  delete ui;
}

void CartoonEditor::LoadFrame(const Frame &frame) {
  cartoonScene_->LoadFrame(frame);
  UpdateFrame();
}

void CartoonEditor::AddFrame() {
  ClearPrevStates();
  if (frames_.isEmpty()) {
    frames_.push_back(cartoonScene_->MakeFrame());
    currentFrame_ = 0;
    frameWidget_->AddFrame(cartoonScene_->GetScenePixmap());
  } else {
    frames_.insert(currentFrame_ + 1, frames_[currentFrame_]);
    frameWidget_->InsertFrame(currentFrame_, cartoonScene_->GetScenePixmap());
    ++currentFrame_;
  }
  UpdateFrame();
}

void CartoonEditor::UpdateFrame() {
  frames_[currentFrame_] = cartoonScene_->MakeFrame();
  frameWidget_->UpdateFrame(currentFrame_, cartoonScene_->GetScenePixmap());
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
  cartoonScene_->AddBody(b);
  BodySnapshot addedBody(*b);
  b->AddTo(ui->graphicsView->scene());
  addedBody.SetVisible(false);
  for (int i = 0; i < frames_.count(); ++i) {
    if (i != currentFrame_) {
      frames_[i].AddBodySnapshot(addedBody);
    }
  }
  ClearPrevStates();
  UpdateFrame();
  PushCurrentState();
}

void CartoonEditor::Restore() {
  if (previous_frames_.size() <= 1)
    return;

  previous_frames_.pop();
  frames_ = previous_frames_.top().second;
  currentFrame_ = previous_frames_.top().first;
  if (previous_frames_.size() > 1) {
    previous_frames_.pop();
    previous_frames_.push(previous_frames_.top());
  }
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

void CartoonEditor::SetupStyles() {
  auto styleManager = StyleManager::Instance();
  ui->submitButton->setStyleSheet(styleManager->StyleByType("button"));
  setStyleSheet(styleManager->StyleByType("cartooneditor"));
  ui->framesArea->setStyleSheet(styleManager->StyleByType("framewidget"));
  ui->modelsArea->setLayoutDirection(Qt::RightToLeft);
  ui->modelsArea->setStyleSheet(styleManager->StyleByType("framewidget"));
  ui->graphicsView->setStyleSheet(styleManager->StyleByType("scene"));
}
