#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QString>
#include <QScopedPointer>

class Project;

class ProjectManager
{
  public:
    ProjectManager();

    void openProject(const QString& projectFileName);

  private:
    QScopedPointer<Project> _currentProject;
};

#endif // PROJECTMANAGER_H
