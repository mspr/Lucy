#include "outputwindow.h"
#include "ui_outputwindow.h"
#include "messagehandler.h"
#include "outputscrollbar.h"

#include <QLabel>
#include <QFile>

using namespace Output;

OutputWindow::OutputWindow(QWidget* parent)
  : QDockWidget(parent)
  , _ui(new Ui::OutputWindow)
{
  _ui->setupUi(this);

  setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
  setTitleBarWidget(new QWidget());

  _ui->scrollArea->setVerticalScrollBar(new OutputScrollBar(_ui->scrollArea));
  _ui->scrollAreaWidgetContents->layout()->setSizeConstraint(QLayout::SetFixedSize);

  MessageHandler::registerOutputWindow(this);
}

OutputWindow::~OutputWindow()
{
  delete _ui;
}

void OutputWindow::showMessage(QtMsgType type, const QString& msg)
{
  QGridLayout* layout = qobject_cast<QGridLayout*>(_ui->scrollAreaWidgetContents->layout());
  Q_ASSERT_X(layout != nullptr, "showMessage()", "nullptr");
  const int rowIdx = layout->rowCount();

  QLabel* iconLabel = new QLabel();
  QLabel* msgLabel = new QLabel(msg);

  switch (type)
  {
    case QtDebugMsg:
      iconLabel->setPixmap(QPixmap(":/images/info.png"));
    break;
#if QT_VERSION >= 0x050500
    case QtInfoMsg:
      iconLabel->setPixmap(QPixmap(":/images/info.png"));
    break;
#endif
    case QtWarningMsg:
      iconLabel->setPixmap(QPixmap(":/images/warning.png"));
    break;
    case QtCriticalMsg:
    {
      iconLabel->setPixmap(QPixmap(":/images/error.png"));
      msgLabel->setText("<b>" + msgLabel->text() + "</b>");
    }
    break;
    case QtFatalMsg:
    break;
  }

  iconLabel->setMaximumSize(iconLabel->pixmap()->size());

  layout->addWidget(iconLabel, rowIdx, 0, 1, 1);
  layout->addWidget(msgLabel, rowIdx, 1, 1, 1);
}
