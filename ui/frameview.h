#ifndef FRAME_H
#define FRAME_H

#include <QLabel>

class FrameView : public QLabel
{
  Q_OBJECT
public:
  FrameView(int index, QPixmap image, QWidget* parent = nullptr);
signals:
  void Clicked(int index);
protected:
  void mousePressEvent(QMouseEvent*) override;
private:
  int index_;
  QPixmap image_;
};

#endif // FRAME_H
