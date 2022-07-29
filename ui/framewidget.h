#ifndef FRAMEWIDGET_H
#define FRAMEWIDGET_H

#include <QWidget>

#include "frameview.h"

namespace Ui {
class FrameWidget;
}

class FrameWidget : public QWidget {
 Q_OBJECT

 public:
  constexpr const static double ImageWidthMultiplyRatio = 0.8;
  explicit FrameWidget(QVector<QPixmap> images = QVector<QPixmap>(), QWidget *parent = nullptr);
  void AddFrame(const QPixmap &framePixmap);
  void InsertFrame(int index, const QPixmap &framePixmap);
  ~FrameWidget() override;
  void DeleteFrameAt(int index);
  void UpdateFrame(int index, const QPixmap &image);
  QVector<QPixmap> GetImages() const;
 signals:
  void FrameSelected(int index);
 private slots:
  void Clicked(int index);
 private:
  QVector<FrameView *> views_;
  QVector<QPixmap> images_;
  Ui::FrameWidget *ui;
};

#endif // FRAMEWIDGET_H
