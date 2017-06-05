#include "projectmanager.h"
#include "project.h"
#include "projectxmlreader.h"

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

  _currentProject = ProjectXmlReader::load(projectFileName);
  if (!_currentProject.isNull())
    emit projectOpen();
}

QSharedPointer<Project> ProjectManager::currentProject() const
{
  return _currentProject;
}
