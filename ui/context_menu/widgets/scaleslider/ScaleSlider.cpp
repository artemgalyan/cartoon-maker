#include <QHBoxLayout>
#include "ScaleSlider.h"

ScaleSlider::ScaleSlider(double base_scale, int scale_range, QObject *parent)
    : QWidgetAction(parent), scale_range_(scale_range) {
  SetupLayout();
  functional_constant_ = pow(scale_range, 1.0 / Range);
  connect(slider_, &QAbstractSlider::valueChanged, this, &ScaleSlider::SliderValueChanged);
  SetValueFromScale(base_scale);
}

void ScaleSlider::SetupLayout() {
  auto widget = new QWidget();
  auto layout = new QHBoxLayout();
  slider_ = new QSlider(Qt::Horizontal);
  slider_->setMinimum(-Range);
  slider_->setMaximum(Range);
  value_label_ = new QLabel();
  value_label_->setIndent(5);
  value_label_->setNum(GetValue());
  value_label_->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
  value_label_->setMinimumWidth(MinLabelWidth);
  layout->addWidget(slider_, 0,Qt::AlignVCenter);
  layout->addWidget(value_label_,  0, Qt::AlignVCenter | Qt::AlignRight);
  widget->setLayout(layout);
  setDefaultWidget(widget);
}

void ScaleSlider::SliderValueChanged() {
  double value = GetValue();
  double val = round(value * 10) / 10;
  value_label_->setText(QString::number(val));
  emit ValueChanged(value);
}

double ScaleSlider::GetValue() const {
  double result = pow(functional_constant_, slider_->value());
  return result > scale_range_ ? scale_range_ : result;
}

void ScaleSlider::SetValueFromScale(double scale) {
  int value = round(log(scale) / log(functional_constant_));
  slider_->setValue(value);
  SliderValueChanged();
}
