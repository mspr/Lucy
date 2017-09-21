#ifndef RECENTPROJECTSVIEW_H
#define RECENTPROJECTSVIEW_H

#include <QDockWidget>

class RecentProjectsView : public QDockWidget
{
  public:
    RecentProjectsView(const QList<QAction*>& openActions, QWidget* parent = nullptr);

  private:
    class RecentProjectView : public QWidget
    {
      public:
        RecentProjectView(QAction* openAction, QWidget* parent = nullptr);
    };
};

#endif // RECENTPROJECTSVIEW_H
