#include "framewidget.h"
#include "ui_framewidget.h"

#include <QVBoxLayout>

#include "frameview.h"

FrameWidget::FrameWidget(QVector<QPixmap> images, QWidget *parent) :
    images_(std::move(images)),
    QWidget(parent),
    ui(new Ui::FrameWidget) {
  ui->setupUi(this);
  auto layout = new QVBoxLayout(this);
  layout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
  setLayout(layout);
  for (const auto &image : images_) {
    AddFrame(image);
  }
}

void FrameWidget::AddFrame(const QPixmap &framePixmap) {
  QPixmap pixmap = framePixmap.scaledToWidth(ImageWidthMultiplyRatio * width(), Qt::SmoothTransformation);
  images_.push_back(pixmap);
  auto frame = new FrameView(images_.count() - 1, pixmap, this);
  connect(frame, &FrameView::Clicked, this, &FrameWidget::Clicked);
  views_.push_back(frame);
  layout()->addWidget(frame);
}

FrameWidget::~FrameWidget() {
  delete ui;
}

void FrameWidget::Clicked(int index) {
  emit FrameSelected(index);
}

void FrameWidget::UpdateFrame(int index, const QPixmap &image) {
  if (parentWidget() != nullptr) {
    setFixedWidth(parentWidget()->width());
  }
  if (index >= images_.count()) {
    return;
  }
  images_[index] = image.scaledToWidth(ImageWidthMultiplyRatio * width(), Qt::SmoothTransformation);
  auto frameView = views_[index];
  if (frameView != nullptr)
    frameView->setPixmap(images_[index]);
  else
    throw std::logic_error("frameView is empty!");
}

void FrameWidget::InsertFrame(int index, const QPixmap &framePixmap) {
  QPixmap pixmap = framePixmap.scaledToWidth(ImageWidthMultiplyRatio * width(), Qt::SmoothTransformation);
  if (index == images_.count() - 1){
    AddFrame(framePixmap);
    return;
  }
  images_.insert(index + 1, framePixmap);
  auto frame = new FrameView(index, pixmap, this);

  connect(frame, &FrameView::Clicked, this, &FrameWidget::Clicked);

  views_.insert(index + 1,frame);
  auto l = dynamic_cast<QVBoxLayout*>(layout());
  l->insertWidget(index, frame);
  for (int i = index + 1; i < views_.count(); ++i) {
    views_[i]->SetIndex(views_[i]->GetIndex() + 1);
  }
}

void FrameWidget::DeleteFrameAt(int index) {
  layout()->removeWidget(views_[index]);
  views_[index]->hide();
  delete views_[index];
  views_.removeAt(index);
  images_.removeAt(index);
  for (int i = index; i < views_.count(); ++i) {
    views_[i]->SetIndex(views_[i]->GetIndex() - 1);
  }
}

QVector<QPixmap> FrameWidget::GetImages() const {
  return images_;
}

void FrameWidget::Clear() {
  for (auto widget: views_) {
    layout()->removeWidget(widget);
    widget->hide();
    delete widget;
  }
  views_.clear();
  images_.clear();
}
