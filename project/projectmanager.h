#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QSharedPointer>

class Project;

class ProjectManager : public QObject
{
  Q_OBJECT

  public:
    static ProjectManager* getInstance();
    static void kill();

    void openProject(const QString& projectFileName);
    QSharedPointer<Project> createNewProject(const QString& projectName);
    void closeProject();

    QSharedPointer<Project> currentProject() const;

  signals:
    void projectOpen();

  private:
    ProjectManager();

  private:
    static ProjectManager* _projectManager;
    QSharedPointer<Project> _currentProject;
};

#endif // PROJECTMANAGER_H
