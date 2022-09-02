
#ifndef CARTOON_MAKER_UI_MAIN_WINDOW_MAINWINDOW_H_
#define CARTOON_MAKER_UI_MAIN_WINDOW_MAINWINDOW_H_

#include <QStackedWidget>
#include <QMainWindow>
#include "startwidget.h"
#include "../cartooneditor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() override;
 private slots:
  void OnPlayButtonClicked();
  void OnReturnButtonClicked();
 private:
  Ui::MainWindow* ui;
  CartoonEditor* cartoon_editor_;
  StartWidget* start_widget_;
  QStackedWidget* stacked_widget_;
};

#endif //CARTOON_MAKER_UI_MAIN_WINDOW_MAINWINDOW_H_
