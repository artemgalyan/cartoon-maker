#ifndef FRAMEWIDGET_H
#define FRAMEWIDGET_H

#include <QWidget>

#include "frameview.h"

namespace Ui {
  class FrameWidget;
}

class FrameWidget : public QWidget
{
  Q_OBJECT

public:
  explicit FrameWidget(QVector<QPixmap> images = QVector<QPixmap>(), QWidget *parent = nullptr);
  void AddFrame(const QPixmap& framePixmap);
  ~FrameWidget();
  void UpdateFrame(int index, const QPixmap& image);
signals:
  void FrameSelected(int index);
private slots:
  void Clicked(int index);
private:
  QVector<FrameView*> views_;
  QVector<QPixmap> images_;
  Ui::FrameWidget *ui;
};

#endif // FRAMEWIDGET_H
