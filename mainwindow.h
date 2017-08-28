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
    void setupSignalSlotConnections();
    void askUserToSaveAndContinue(std::function<void()> action);

  private slots:
    void newProject();
    void openProject();
    void saveProject();
    void saveProjectAs();
    void quit();
    void createTree();
    void onProjectOpen();
    void onTreeAdded(QUuid droid);
    void onProjectUpdated();
    void onProjectUpToDate();

  private:
    Ui::MainWindow* _ui;
    QTabWidget* _treeTabWidget;
};

#endif // MAINWINDOW_H
