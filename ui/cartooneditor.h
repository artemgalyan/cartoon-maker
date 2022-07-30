#ifndef CARTOONEDITOR_H
#define CARTOONEDITOR_H

#include <QWidget>
#include <QStack>

#include "framewidget.h"
#include "../entities/Frame.h"
#include "modelwidget.h"
#include "CartoonScene.h"
#include "../entities/Cartoon.h"
#include "../logic/CartoonEditorSnaphot.h"

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
  void Clear();
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
  [[nodiscard]] CartoonEditorSnapshot GetSnapshot() const;
  void SetupGraphicsView();
  void SetupFrameWidget();
  void SetupModelWidget();
  void MakeConnects();
  void SetupStyles();
  void PushCurrentState();
  void Restore();
  QStack<CartoonEditorSnapshot> snapshots_;
  CartoonScene *cartoon_scene_;
  FrameWidget *frame_widget_;
  ModelWidget *model_widget_;
  QVector<Frame> frames_;
  int current_frame_ = -1;
  Ui::CartoonEditor *ui_;
};

#endif // CARTOONEDITOR_H
