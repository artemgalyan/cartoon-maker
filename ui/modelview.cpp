

#include "modelview.h"
#include "ui_ModelView.h"

ModelView::ModelView(QWidget *parent) :
    QWidget(parent), ui(new Ui::ModelView) {
  ui->setupUi(this);
}

ModelView::~ModelView() {
  delete ui;
}
