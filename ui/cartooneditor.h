#ifndef CARTOONEDITOR_H
#define CARTOONEDITOR_H

#include <QWidget>

#include "framewidget.h"
#include "../entities/Frame.h"

namespace Ui {
class CartoonEditor;
}

class CartoonEditor : public QWidget {
 Q_OBJECT

 public:
  explicit CartoonEditor(QWidget *parent = nullptr);
  ~CartoonEditor();
  void LoadFrame(const Frame &frame);
  [[nodiscard]] Frame MakeFrame() const;
 private slots:
  void AddFrame();
  void SwitchToFrame(int index);
  void UpdateFrame();
  void AddBody(Body *);
 private:
  [[nodiscard]] QPixmap GetScenePixmap() const;
  FrameWidget *frameWidget_;
  QVector<Body *> bodies_;
  QVector<Frame> frames_;
  int currentFrame_ = -1;
  Ui::CartoonEditor *ui;
 protected:
  void resizeEvent(QResizeEvent *event) override;
};

#endif // CARTOONEDITOR_H
