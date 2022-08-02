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
#include <QParallelAnimationGroup>
CartoonEditor::CartoonEditor(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::CartoonEditor) {
  ui_->setupUi(this);
  SetupGraphicsView();
  SetupFrameWidget();
  SetupModelWidget();
  MakeConnects();
  SetupStyles();
  QTimer::singleShot(100, [this] { AddFrame(); });
}
/*parallel_animation_group = new QParallelAnimationGroup(cartoon_scene_);

  animationGroup->addPause(1000);
  animator_ = new Animator(cartoon_scene_, frames_);
  auto map_ = animator_->GetPropertiesMap();
  for (QMap<int, QVector<QPropertyAnimation *>>::iterator it = map_.begin(); it != map_.end(); ++it) {
    auto groupProperties = it.value();
    QSequentialAnimationGroup *currentAnimationGroup = new QSequentialAnimationGroup(cartoon_scene_);
    for (int i = 0; i < groupProperties.size(); i++) {
      currentAnimationGroup->addAnimation(groupProperties[i]);
    }
    parallel_animation_group->addAnimation(currentAnimationGroup);*/

void CartoonEditor::MakeConnects() {
  auto scene = dynamic_cast<CartoonScene *>(ui_->graphicsView->scene());
  if (scene == nullptr) {
    throw std::logic_error("Scene is not CartoonScene*");
  }

  connect(frame_widget_, SIGNAL(FrameSelected(int)), this, SLOT(SwitchToFrame(int)));
  connect(scene, SIGNAL(Changed()), this, SLOT(SceneChanged()));
  connect(ui_->PlayButton, SIGNAL(clicked(bool)), this, SLOT(Play()));
  connect(ui_->AddFrameButton, SIGNAL(clicked(bool)), this, SLOT(AddFrame()));
  connect(ui_->DeleteFrameButton, SIGNAL(clicked(bool)), this, SLOT(DeleteFrame()));
  connect(ui_->SaveCartoonButton, SIGNAL(clicked(bool)), this, SLOT(SaveCartoon()));
  connect(ui_->LoadCartoonButton, SIGNAL(clicked(bool)), this, SLOT(LoadCartoon()));
}

void CartoonEditor::SetupModelWidget() {
  auto factory = BodyFactory::Instance();
  model_widget_ = new ModelWidget(factory->GetPreviews(), this, ui_->modelsArea);
  ui_->modelsArea->setWidget(model_widget_);
  ui_->modelsArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

void CartoonEditor::SetupFrameWidget() {
  frame_widget_ = new FrameWidget(QVector<QPixmap>(), ui_->framesArea);
  ui_->framesArea->setWidget(frame_widget_);
  ui_->framesArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

void CartoonEditor::SetupGraphicsView() {
  cartoon_scene_ = new CartoonScene(ui_->graphicsView);
  ui_->graphicsView->setScene(cartoon_scene_);
  ui_->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui_->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

CartoonEditor::~CartoonEditor() {
  delete ui_;
}

void CartoonEditor::LoadFrame(const Frame &frame) {
  cartoon_scene_->LoadFrame(frame);
  UpdateFrame();
}

void CartoonEditor::AddFrame() {
  if (frames_.isEmpty()) {
    frames_.push_back(cartoon_scene_->MakeFrame());
    current_frame_ = 0;
    frame_widget_->AddFrame(cartoon_scene_->GetScenePixmap());
  } else {
    frames_.insert(current_frame_ + 1, frames_[current_frame_]);
    frame_widget_->InsertFrame(current_frame_, cartoon_scene_->GetScenePixmap());
    ++current_frame_;
  }
  UpdateFrame();
  PushCurrentState();
}

void CartoonEditor::UpdateFrame() {
  frames_[current_frame_] = cartoon_scene_->MakeFrame();
  frame_widget_->UpdateFrame(current_frame_, cartoon_scene_->GetScenePixmap());
}

void CartoonEditor::SwitchToFrame(int index) {
  UpdateFrame();
  current_frame_ = index;
  LoadFrame(frames_[current_frame_]);
}

void CartoonEditor::resizeEvent(QResizeEvent *event) {
  ui_->graphicsView->scene()->setSceneRect(0, 0, ui_->graphicsView->width(), ui_->graphicsView->height());
  QWidget::resizeEvent(event);
}

void CartoonEditor::AddBody(Body *b) {
  cartoon_scene_->AddBody(b);
  BodySnapshot added_body(*b);
  b->AddTo(ui_->graphicsView->scene());
  added_body.SetVisible(false);
  for (int i = 0; i < frames_.count(); ++i) {
    if (i != current_frame_) {
      frames_[i].AddBodySnapshot(added_body);
    }
  }
  UpdateFrame();
  PushCurrentState();
}

void CartoonEditor::Restore() {
  if (snapshots_.isEmpty() || snapshots_.count() == 1)
    return;

  snapshots_.pop();
  auto snapshot = snapshots_.top();
  frames_ = snapshot.frames;
  cartoon_scene_->LeaveNFirstBodiesOnTheScene(snapshot.number_of_bodies);
  frame_widget_->Clear();
  if (snapshot.frames.count() != snapshot.images.count()) {
    return;
  }
  for (const auto &image : snapshot.images) {
    frame_widget_->AddFrame(image);
  }
  current_frame_ = snapshot.current_frame;
  LoadFrame(frames_[current_frame_]);
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
  snapshots_.push(GetSnapshot());
}

void CartoonEditor::SetupStyles() {
  auto style_manager = StyleManager::Instance();
  setStyleSheet(style_manager->StyleByType("cartooneditor"));
  ui_->framesArea->setStyleSheet(style_manager->StyleByType("framewidget"));
  ui_->modelsArea->setLayoutDirection(Qt::RightToLeft);
  ui_->modelsArea->setStyleSheet(style_manager->StyleByType("framewidget"));
  ui_->graphicsView->setStyleSheet(style_manager->StyleByType("scene"));
  ui_->PlayButton->setIcon(QIcon(":/res/icons/playbutton.png"));
  ui_->AddFrameButton->setIcon(QIcon(":/res/icons/addbutton.png"));
  ui_->DeleteFrameButton->setIcon(QIcon(":/res/icons/deletebutton.png"));
  ui_->SaveCartoonButton->setIcon(QIcon(":/res/icons/savebutton.png"));
  ui_->LoadCartoonButton->setIcon(QIcon(":/res/icons/loadbutton.png"));
}

void CartoonEditor::Play() {
  SetAllEnabled(false);
  if (animator_ != nullptr)
    disconnect(animator_, &Animator::AnimationFinished, this, &CartoonEditor::AnimationFinished);
  delete animator_;
  animator_ = new Animator(cartoon_scene_, frames_);
  connect(animator_, &Animator::AnimationFinished, this, &CartoonEditor::AnimationFinished);
  animator_->Play();
}

void CartoonEditor::DeleteFrame() {
  frames_.remove(current_frame_);
  frame_widget_->DeleteFrameAt(current_frame_);
  --current_frame_;
  if (current_frame_ < 0) {
    current_frame_ = 0;
  }
  if (frames_.empty()) {
    cartoon_scene_->Clear();
    AddFrame();
  }
  LoadFrame(frames_[current_frame_]);
  PushCurrentState();
}

void CartoonEditor::SaveCartoon() {
  // TODO: Implement the method
}

void CartoonEditor::LoadCartoon() {
  // TODO: Implement the method
}

void CartoonEditor::Clear() {
  cartoon_scene_->Clear();
  frames_.clear();
  frame_widget_->Clear();
  snapshots_.clear();
}

CartoonEditorSnapshot CartoonEditor::GetSnapshot() const {
  int number_of_bodies = cartoon_scene_->GetBodies().count();
  const auto &images = frame_widget_->GetImages();
  return {current_frame_, number_of_bodies, frames_, images};
}

Cartoon CartoonEditor::ExportCartoon() const {
  return Cartoon(cartoon_scene_->GetEntitiesNameList(), frames_);
}

void CartoonEditor::LoadCartoon(const Cartoon &cartoon) {
  Clear();
  auto factory = BodyFactory::Instance();
  auto bodies_list = cartoon.GetEntities();
  for (const auto &body : bodies_list) {
    auto b = factory->CreateByType(body);
    cartoon_scene_->AddBody(b);
    b->AddTo(cartoon_scene_);
  }
  frames_ = cartoon.GetFrames();
  for (int i = 0; i < frames_.count(); ++i) {
    cartoon_scene_->LoadFrame(frames_[i]);
    frame_widget_->AddFrame(cartoon_scene_->GetScenePixmap());
  }
  SwitchToFrame(0);
}

void CartoonEditor::SetAllEnabled(bool value) {
  ui_->modelsArea->setEnabled(value);
  ui_->framesArea->setEnabled(value);
  ui_->AddFrameButton->setEnabled(value);
  ui_->DeleteFrameButton->setEnabled(value);
  ui_->SaveCartoonButton->setEnabled(value);
  ui_->PlayButton->setEnabled(value);
  ui_->LoadCartoonButton->setEnabled(value);

}

void CartoonEditor::AnimationFinished() {
  SetAllEnabled(true);
  current_frame_= frames_.count()-1;
  LoadFrame(frames_.last());
}
