#ifndef CARTOONEDITOR_H
#define CARTOONEDITOR_H

#include <QWidget>
#include <QStack>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>

#include "framewidget.h"
#include "../entities/Frame.h"
#include "modelwidget.h"
#include "CartoonScene.h"
#include "../entities/Cartoon.h"
#include "../logic/CartoonEditorSnaphot.h"
#include "../logic/Animator.h"

namespace Ui {
class CartoonEditor;
}

class CartoonEditor : public QWidget {
 Q_OBJECT
 public:
  const static QString FileExtensionName;
  explicit CartoonEditor(QWidget* parent = nullptr);
  ~CartoonEditor() override;
  void LoadFrame(const Frame& frame);
  void AddBody(Body*);
  void Clear();
  [[nodiscard]] Cartoon ExportCartoon() const;
  void LoadCartoon(const Cartoon&);
  void AddFirstFrameIfNeeded();
 protected:
  void keyPressEvent(QKeyEvent* event) override;
  void resizeEvent(QResizeEvent* event) override;
 private slots:
  void AddFrame();
  void DeleteFrame();
  void SaveCartoon();
  void LoadCartoon();
  void SwitchToFrame(int index);
  void UpdateFrame();
  void SceneChanged();
  void Play();
  void AnimationFinished();
 signals:
  void ToMainMenu();
 private:
  void SetAllEnabled(bool value);
  [[nodiscard]] CartoonEditorSnapshot GetSnapshot() const;
  void SetupGraphicsView();
  void SetupFrameWidget();
  void SetupModelWidget();
  void MakeConnects();
  void SetupStyles();
  void PushCurrentState();
  void Restore();
  QStack<CartoonEditorSnapshot> snapshots_;
  CartoonScene* cartoon_scene_;
  FrameWidget* frame_widget_;
  ModelWidget* model_widget_;
  Animator* animator_ = nullptr;
  QVector<Frame> frames_;
  int current_frame_ = -1;
  Ui::CartoonEditor* ui_;
};

#endif // CARTOONEDITOR_H
