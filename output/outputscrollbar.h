#ifndef OUTPUTSCROLLBAR_H
#define OUTPUTSCROLLBAR_H

#include <QScrollBar>

namespace Output
{
  class OutputScrollBar : public QScrollBar
  {
    public:
      OutputScrollBar(QWidget* parent = nullptr);

    protected:
      virtual void sliderChange(SliderChange sliderChange) override;
  };

} // Output

#endif // OUTPUTSCROLLBAR_H
