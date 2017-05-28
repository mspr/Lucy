#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QString>
#include <QScopedPointer>

class Project;

class ProjectManager
{
  public:
    static ProjectManager* getInstance();
    static void kill();

    void openProject(const QString& projectFileName);

  private:
    ProjectManager();

  private:
    static ProjectManager* _projectManager;
    QScopedPointer<Project> _currentProject;
};

#endif // PROJECTMANAGER_H
