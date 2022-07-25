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
  setLayout(layout);
  for (const auto &image : images_) {
    AddFrame(image);
  }
}

void FrameWidget::AddFrame(const QPixmap &framePixmap) {
  QPixmap pixmap = framePixmap.scaledToWidth(0.9 * width());
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
  if (index >= images_.count()) {
    return;
  }
  images_[index] = image.scaledToWidth(width());
  auto frameView = views_[index];
  if (frameView != nullptr)
    frameView->setPixmap(images_[index]);
  else
    throw std::logic_error("frameView is empty!");
}
