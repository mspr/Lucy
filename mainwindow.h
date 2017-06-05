#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

  private slots:
    void newProject();
    void openProject();
    void saveProject();
    void quit();
    void createTree();
    void onProjectOpen();
    void onTreeAdded(QUuid droid);

  private:
    Ui::MainWindow* _ui;
    QTabWidget* _treeTabWidget;
};

#endif // MAINWINDOW_H
