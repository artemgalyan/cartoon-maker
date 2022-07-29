#ifndef CARTOONEDITOR_H
#define CARTOONEDITOR_H

#include <QWidget>
#include <stack>

#include "framewidget.h"
#include "../entities/Frame.h"
#include "modelwidget.h"
#include "CartoonScene.h"

namespace Ui {
class CartoonEditor;
}

class CartoonEditor : public QWidget {
 Q_OBJECT
 public:
  explicit CartoonEditor(QWidget *parent = nullptr);
  ~CartoonEditor() override;
  void LoadFrame(const Frame &frame);
  void AddBody(Body *);
 protected:
  void keyPressEvent(QKeyEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;
 private slots:
  void AddFrame();
  void DeleteFrame();
  void SaveCartoon();
  void LoadCartoon();
  void SwitchToFrame(int index);
  void UpdateFrame();
  void SceneChanged();
  void Play();
 private:
  void SetupGraphicsView();
  void SetupFrameWidget();
  void SetupModelWidget();
  void MakeConnects();
  void SetupStyles();
  void ClearPrevStates();
  void PushCurrentState();
  void LoadState(int selectedFrame, QVector<Frame> frames);
  void Restore();
  CartoonScene *cartoonScene_;
  FrameWidget *frameWidget_;
  ModelWidget *modelWidget_;
  QVector<Frame> frames_;
  std::stack<QPair<int, QVector<Frame>>> previous_frames_;
  int currentFrame_ = -1;
  Ui::CartoonEditor *ui;
};

#endif // CARTOONEDITOR_H
