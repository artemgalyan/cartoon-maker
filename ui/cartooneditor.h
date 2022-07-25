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
 private:
  QPixmap GetScenePixmap() const;
  FrameWidget *frameWidget_;
  QVector<Body> bodies_;
  QVector<Frame> frames_;
  int currentFrame_ = 0;
  Ui::CartoonEditor *ui;
};

#endif // CARTOONEDITOR_H
