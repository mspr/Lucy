#include "projectmanager.h"
#include "project.h"
#include "projectxmlreader.h"

#include <QSharedPointer>
#include <QFile>

ProjectManager* ProjectManager::_projectManager = nullptr;

/*static*/ ProjectManager* ProjectManager::getInstance()
{
  if (_projectManager == nullptr)
    _projectManager = new ProjectManager();

  return _projectManager;
}

/*static*/ void ProjectManager::kill()
{
  if (_projectManager != nullptr)
  {
    delete _projectManager;
    _projectManager = nullptr;
  }
}

ProjectManager::ProjectManager()
{
  _currentProject.reset();
}

void ProjectManager::openProject(const QString& projectFileName)
{
  Q_ASSERT(QFile::exists(projectFileName));

  QSharedPointer<Project> project = ProjectXmlReader::load(projectFileName);
  _currentProject.reset();
}
