#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

  private slots:
    void newProject();
    void openProject();
    void saveProject();
    void quit();
    void createTree();

  private:
    Ui::MainWindow* _ui;
    QTabWidget* _treeTabWidget;
};

#endif // MAINWINDOW_H
