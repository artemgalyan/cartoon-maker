
#ifndef CARTOON_MAKER_UI_MODELWIDGET_H_
#define CARTOON_MAKER_UI_MODELWIDGET_H_

#include <QWidget>

class CartoonEditor;

QT_BEGIN_NAMESPACE
namespace Ui { class ModelWidget; }
QT_END_NAMESPACE

class ModelWidget : public QWidget {
 Q_OBJECT

 public:
  explicit ModelWidget(const QVector<QPair<QString, QPixmap>>&, CartoonEditor* editor, QWidget *parent = nullptr);
  ~ModelWidget() override;

 private:
  Ui::ModelWidget *ui;
};

#endif //CARTOON_MAKER_UI_MODELWIDGET_H_
