#ifndef CARTOONEDITOR_H
#define CARTOONEDITOR_H

#include <QWidget>
#include <stack>

#include "framewidget.h"
#include "../entities/Frame.h"
#include "modelwidget.h"

namespace Ui {
class CartoonEditor;
}

class CartoonEditor : public QWidget {
 Q_OBJECT

 public:
  explicit CartoonEditor(QWidget *parent = nullptr);
  ~CartoonEditor() override;
  void LoadFrame(const Frame &frame);
  [[nodiscard]] Frame MakeFrame() const;
  void AddBody(Body *);
 private slots:
  void AddFrame();
  void SwitchToFrame(int index);
  void UpdateFrame();
  void SceneChanged();
 private:
  void ClearPrevStates();
  void PushCurrentState();
  void LoadState(int selectedFrame, QVector<Frame> frames);
  void Restore();
  [[nodiscard]] QPixmap GetScenePixmap() const;
  FrameWidget *frameWidget_;
  ModelWidget *modelWidget_;
  QVector<Body *> bodies_;
  QVector<Frame> frames_;
  std::stack<QPair<int, QVector<Frame>>> previous_frames_;
  int currentFrame_ = -1;
  Ui::CartoonEditor *ui;
 protected:
  void keyPressEvent(QKeyEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;
};

#endif // CARTOONEDITOR_H
