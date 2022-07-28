#ifndef CARTOON_MAKER_UI_CONTEXT_MENU_WIDGETS_SCALESLIDER_H_
#define CARTOON_MAKER_UI_CONTEXT_MENU_WIDGETS_SCALESLIDER_H_

#include <QWidgetAction>
#include <QSlider>
#include <QLabel>

class ScaleSlider : public QWidgetAction {
  Q_OBJECT

 public:
  const static int Range = 100;
  const static int MinLabelWidth = 30;

  explicit ScaleSlider(double base_scale = 1, int scale_range = 10, QObject *parent = nullptr);
  [[nodiscard]] double GetValue() const;
 signals:
  void ValueChanged(double new_value);
 private slots:
  void SliderValueChanged();
 private:
  void SetValueFromScale(double scale);
  QLabel *value_label_;
  QSlider *slider_;
  double functional_constant_;
  int scale_range_;
  void SetupLayout();
};

#endif //CARTOON_MAKER_UI_CONTEXT_MENU_WIDGETS_SCALESLIDER_H_
