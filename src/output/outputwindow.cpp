#include "outputwindow.h"
#include "ui_outputwindow.h"
#include "messagehandler.h"
#include "outputscrollbar.h"

#include <QLabel>
#include <QFile>

using namespace Output;

OutputWindow::OutputWindow(QWidget* parent)
  : QDockWidget(parent)
  , m_ui(new Ui::OutputWindow)
{
  m_ui->setupUi(this);

  setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
  setTitleBarWidget(new QWidget());

  m_ui->scrollArea->setVerticalScrollBar(new OutputScrollBar(m_ui->scrollArea));
  m_ui->scrollAreaWidgetContents->layout()->setSizeConstraint(QLayout::SetFixedSize);

  MessageHandler::registerOutputWindow(this);
}

OutputWindow::~OutputWindow()
{
  delete m_ui;
}

void OutputWindow::showMessage(QtMsgType type, const QString& msg)
{
  QGridLayout* layout = qobject_cast<QGridLayout*>(m_ui->scrollAreaWidgetContents->layout());
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
