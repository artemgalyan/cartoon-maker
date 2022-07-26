

#include "modelview.h"

#include <utility>
#include "cartooneditor.h"
#include "ui_ModelView.h"
#include "../entities/body/factory/BodyFactory.h"

ModelView::~ModelView() {
  delete ui;
}
void ModelView::mousePressEvent(QMouseEvent *event) {
  BodyFactory *factory = BodyFactory::Instance();
  editor_->AddBody(factory->CreateByType(type_));
  QLabel::mousePressEvent(event);
}
ModelView::ModelView(QString type, QPixmap pixmap, CartoonEditor *editor, QWidget *parent)
    : QLabel(parent), ui(new Ui::ModelView), type_(std::move(type)), pixmap_(std::move(pixmap)), editor_(editor) {
  ui->setupUi(this);
  resize(pixmap_.size());
  SetWidth(width());
}

void ModelView::SetWidth(int width) {
  setFixedWidth(width);
  setPixmap(pixmap_.scaledToWidth(width, Qt::SmoothTransformation));
}
