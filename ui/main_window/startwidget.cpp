#include <QPalette>
#include <QPainter>

#include "startwidget.h"
#include "ui_startwidget.h"
#include "../../logic/factory/StyleManager.h"

StartWidget::StartWidget(QWidget* parent) :
    QWidget(parent), ui(new Ui::StartWidget) {
  ui->setupUi(this);
  connect(ui->playButton, SIGNAL(clicked(bool)), this, SLOT(OnPlayButtonClicked()));
  connect(ui->exitButton, SIGNAL(clicked(bool)), this, SLOT(OnExitButtonClicked()));

  auto style_manager = StyleManager::Instance();
  auto style_sheet = style_manager->StyleByType("start_menu_button");
  ui->playButton->setStyleSheet(style_sheet);
  ui->exitButton->setStyleSheet(style_sheet);

  this->setStyleSheet(style_manager->StyleByType("start_widget"));
  background_ = QPixmap(":/res/background.png");
}

StartWidget::~StartWidget() {
  delete ui;
}

void StartWidget::OnPlayButtonClicked() {
  emit OnPlayClicked();
}

void StartWidget::OnExitButtonClicked() {
  QApplication::exit(0);
}

void StartWidget::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  QPixmap image = background_.scaledToHeight(height(), Qt::SmoothTransformation);
  painter.drawPixmap(0, 0, image);
  QWidget::paintEvent(event);
}
