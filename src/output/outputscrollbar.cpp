#include "outputscrollbar.h"

using namespace Output;

OutputScrollBar::OutputScrollBar(QWidget* parent)
  : QScrollBar(parent)
{
}

void OutputScrollBar::sliderChange(SliderChange sliderChange)
{
  QScrollBar::sliderChange(sliderChange);

  if (sliderChange == SliderRangeChange)
    setValue(maximum());
}
