#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <functional>
#include <QMainWindow>
#include <QUuid>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

  private:
    void setupRecentProjectsActions();
    void updateRecentProjectsActions();
    void setupSignalSlotConnections();
    void askUserToSaveAndContinue(std::function<void()> action);

  private slots:
    void newProject();
    void openProject();
    void openRecentProject();
    void saveProject();
    void saveProjectAs();
    void quit();
    void createTree();

    void onProjectOpen();
    void onProjectClosed();
    void onTreeAdded(QUuid droid);
    void onProjectDirty();
    void onProjectUpToDate();
    void onProjectSaved();

  private:
    Ui::MainWindow* _ui;
    QTabWidget* _treeTabWidget;
    int _recentProjectsNumber;
    QList<QAction*> _recentProjectsActions;
};

#endif // MAINWINDOW_H
