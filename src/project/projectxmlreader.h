#ifndef PROJECTXMLREADER_H
#define PROJECTXMLREADER_H

#include "project/project.h"

class QDomElement;

class ProjectXmlReader
{
  public:
    ProjectXmlReader() = delete;

    static QSharedPointer<Project> load(const QString& fileName);

  private:
    static void loadTrees(const QDomElement& projectNode, Project& project);
    static void loadCurrentTree(const QDomElement& projectNode, Project& project);
};

#endif // PROJECTXMLREADER_H
