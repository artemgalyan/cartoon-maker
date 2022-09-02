#include "mainwindow.h"
#include "ui_MainWindow.h"
#include "../../logic/factory/StyleManager.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  auto style_manager = StyleManager::Instance();
  stacked_widget_ = new QStackedWidget();
  cartoon_editor_ = new CartoonEditor();
  start_widget_ = new StartWidget();
  stacked_widget_->addWidget(cartoon_editor_);
  stacked_widget_->addWidget(start_widget_);
  stacked_widget_->setCurrentWidget(start_widget_);
  setCentralWidget(stacked_widget_);
  stacked_widget_->setStyleSheet(style_manager->StyleByType("mainwindow"));
  connect(start_widget_, SIGNAL(OnPlayClicked()), this, SLOT(OnPlayButtonClicked()));
  connect(cartoon_editor_, SIGNAL(ToMainMenu()), this, SLOT(OnReturnButtonClicked()));
}

MainWindow::~MainWindow() {
  delete ui;
}
void MainWindow::OnPlayButtonClicked() {
  stacked_widget_->setCurrentWidget(cartoon_editor_);
  cartoon_editor_->AddFirstFrameIfNeeded();
}

void MainWindow::OnReturnButtonClicked() {
  stacked_widget_->setCurrentWidget(start_widget_);
}
