#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QString>

class ProjectManager
{
  public:
    ProjectManager();

    void openProject(const QString& projectFileName);
};

#endif // PROJECTMANAGER_H
