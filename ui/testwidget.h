
#ifndef CARTOON_MAKER_UI_TESTWIDGET_H_
#define CARTOON_MAKER_UI_TESTWIDGET_H_

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "../entities/skeleton/point/point.h"
#include "../entities/skeleton/point/MainPoint.h"
#include "../entities/skeleton/point/SidePoint.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TestWidget; }
QT_END_NAMESPACE

class TestWidget : public QWidget {
 Q_OBJECT

 public:
  explicit TestWidget(QWidget *parent = nullptr);
  ~TestWidget() override;
 protected:
  void resizeEvent(QResizeEvent *event) override;
 private:
  Ui::TestWidget *ui;
  QGraphicsScene *scene_;
  QGraphicsView *view_;
};

#endif //CARTOON_MAKER_UI_TESTWIDGET_H_
