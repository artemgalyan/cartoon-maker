#ifndef CARTOON_MAKER_UI_MODELVIEW_H_
#define CARTOON_MAKER_UI_MODELVIEW_H_

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ModelView; }
QT_END_NAMESPACE

class ModelView : public QWidget {
 Q_OBJECT

 public:
  explicit ModelView(QWidget *parent = nullptr);
  ~ModelView() override;

 private:
  Ui::ModelView *ui;
};

#endif //CARTOON_MAKER_UI_MODELVIEW_H_
