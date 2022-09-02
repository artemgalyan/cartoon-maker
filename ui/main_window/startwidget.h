
#ifndef CARTOON_MAKER_UI_MAIN_WINDOW_STARTWIDGET_H_
#define CARTOON_MAKER_UI_MAIN_WINDOW_STARTWIDGET_H_

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class StartWidget; }
QT_END_NAMESPACE

class StartWidget : public QWidget {
 Q_OBJECT

 public:
  explicit StartWidget(QWidget* parent = nullptr);
  ~StartWidget() override;
 private slots:
  void OnPlayButtonClicked();
  void OnExitButtonClicked();
 signals:
  void OnPlayClicked();
 private:
 protected:
  void paintEvent(QPaintEvent* event) override;
 private:
  Ui::StartWidget* ui;
  QPixmap background_;
};

#endif //CARTOON_MAKER_UI_MAIN_WINDOW_STARTWIDGET_H_
