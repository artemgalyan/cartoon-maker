

#include <QVBoxLayout>
#include "modelwidget.h"
#include "ui_ModelWidget.h"
#include "modelview.h"

ModelWidget::ModelWidget(const QVector<QPair<QString, QPixmap>>& data, CartoonEditor* editor, QWidget *parent) :
    QWidget(parent), ui(new Ui::ModelWidget) {
  ui->setupUi(this);
  if (parent != nullptr) {
    setFixedWidth(parent->width());
  }
  auto layout = new QVBoxLayout(this);
  setLayout(layout);
  for (const auto & [type, preview] : data) {
    auto widget = new ModelView(type, preview, editor, this);
    layout->addWidget(widget);
    modelViews_.push_back(widget);
  }
}

ModelWidget::~ModelWidget() {
  delete ui;
}

void ModelWidget::resizeEvent(QResizeEvent *event) {
  if (parentWidget() != nullptr) {
    setFixedWidth(parentWidget()->width());
  }
  for (auto view: modelViews_){
    view->SetWidth(width());
  }
  QWidget::resizeEvent(event);
}