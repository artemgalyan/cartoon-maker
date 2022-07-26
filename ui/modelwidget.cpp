

#include <QVBoxLayout>
#include "modelwidget.h"
#include "ui_ModelWidget.h"
#include "modelview.h"

ModelWidget::ModelWidget(const QVector<QPair<QString, QPixmap>>& data, CartoonEditor* editor, QWidget *parent) :
    QWidget(parent), ui(new Ui::ModelWidget) {
  ui->setupUi(this);
  auto layout = new QVBoxLayout(this);
  setLayout(layout);
  for (const auto & [type, preview] : data) {
    layout->addWidget(new ModelView(type, preview.scaledToWidth(width()), editor, this));
  }
}

ModelWidget::~ModelWidget() {
  delete ui;
}
