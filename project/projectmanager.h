#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QSharedPointer>

class Project;

class ProjectManager
{
  public:
    static ProjectManager* getInstance();
    static void kill();

    void openProject(const QString& projectFileName);

    QSharedPointer<Project> currentProject() const;

  private:
    ProjectManager();

  private:
    static ProjectManager* _projectManager;
    QSharedPointer<Project> _currentProject;
};

#endif // PROJECTMANAGER_H
