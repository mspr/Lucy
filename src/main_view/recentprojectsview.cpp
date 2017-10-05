#include "recentprojectsview.h"

#include <QHBoxLayout>
#include <QAction>
#include <QLabel>

RecentProjectsView::RecentProjectsView(const QList<QAction*>& openActions, QWidget* parent)
  : QDockWidget(parent)
{
  QWidget* widget = new QWidget(this);
  QVBoxLayout* vLayout = new QVBoxLayout(widget);
  widget->setLayout(vLayout);
  setWidget(widget);

  for (int i=0; i<openActions.count(); ++i)
  {
    RecentProjectView* recentProjectView = new RecentProjectView(openActions.at(i), widget);
    vLayout->addWidget(recentProjectView);
  }
}

RecentProjectsView::RecentProjectView::RecentProjectView(QAction* openAction, QWidget* parent)
  : QWidget(parent)
{
  Q_ASSERT(openAction != nullptr);

  QHBoxLayout* hLayout = new QHBoxLayout(this);
  setLayout(hLayout);
  QLabel* iconLabel = new QLabel(this);
  QPixmap pixmap = openAction->icon().pixmap(QSize(20, 20));
  iconLabel->setPixmap(pixmap);
  hLayout->addWidget(iconLabel);
  QVBoxLayout* vLayout = new QVBoxLayout();
  hLayout->addLayout(vLayout);
  QLabel* projectNameLabel = new QLabel(openAction->text(), this);
  vLayout->addWidget(projectNameLabel);
  QLabel* lastModifiedLabel = new QLabel(this);
  vLayout->addWidget(lastModifiedLabel);
}
