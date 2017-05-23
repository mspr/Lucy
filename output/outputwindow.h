#ifndef OUTPUTWINDOW_H
#define OUTPUTWINDOW_H

#include <QDockWidget>

namespace Ui { class OutputWindow; }

namespace Output
{
  class OutputWindow : public QDockWidget
  {
    Q_OBJECT

    public:
      explicit OutputWindow(QWidget* parent = 0);
      ~OutputWindow();

      void showMessage(QtMsgType type, const QString& msg);

    private:
      Ui::OutputWindow* m_ui;
  };

} // Output

#endif // OUTPUTWINDOW_H
