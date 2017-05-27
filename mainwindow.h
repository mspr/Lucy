#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui { class MainWindow; }

class FamilyTreeView;
class FamilyTreeScene;

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

  private:
    Ui::MainWindow* _ui;
    FamilyTreeView* _familyTreeView;
    QScopedPointer<FamilyTreeScene> _familyTreeScene;
};

#endif // MAINWINDOW_H
