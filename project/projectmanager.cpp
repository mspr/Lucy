#include "projectmanager.h"
#include "project.h"

#include <QFile>

ProjectManager::ProjectManager()
{
}

void ProjectManager::openProject(const QString& projectFileName)
{
  Q_ASSERT(QFile::exists(projectFileName));

}
