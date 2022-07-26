#ifndef CARTOON_MAKER_UI_MODELVIEW_H_
#define CARTOON_MAKER_UI_MODELVIEW_H_

#include <QLabel>

class CartoonEditor;

QT_BEGIN_NAMESPACE
namespace Ui { class ModelView; }
QT_END_NAMESPACE

class ModelView : public QLabel {
 Q_OBJECT

 public:
  explicit ModelView(QString type, QPixmap pixmap, CartoonEditor * editor, QWidget *parent = nullptr);
  ~ModelView() override;
 protected:
  void mousePressEvent(QMouseEvent *event) override;
 private:
  QString type_;
  QPixmap pixmap_;
  CartoonEditor * editor_;
  Ui::ModelView *ui;
};

#endif //CARTOON_MAKER_UI_MODELVIEW_H_
