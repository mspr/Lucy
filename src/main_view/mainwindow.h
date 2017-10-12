#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <functional>
#include <QMainWindow>
#include <QUuid>

namespace Ui { class MainWindow; }
class RecentProjectsView;

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

  private:
    void setupRecentProjectsMenu();
    void updateRecentProjectsMenu();
    void setupSignalSlotConnections();
    void askUserToSaveAndContinue(std::function<void()> action);
    void setDirty(bool dirty);

  private slots:
    void newProject();
    void openProject();
    void openRecentProject();
    void saveProject();
    void saveProjectAs();
    void quit();
    void createTree();

    void onTreeTabCurrentChanged(int index);

    void onProjectOpen();
    void onProjectClosed();
    void onTreeAdded(QUuid droid);
    void onCurrentTreeChanged();
    void onProjectDirty();
    void onProjectSaved();

  protected:
    virtual void keyPressEvent(QKeyEvent*) override;

  private:
    Ui::MainWindow* _ui;
    QTabWidget* _treeTabWidget;
    RecentProjectsView* _recentProjectsView;
    int _recentProjectsNumber;
    QMenu* _recentProjectsMenu;
};

#endif // MAINWINDOW_H
