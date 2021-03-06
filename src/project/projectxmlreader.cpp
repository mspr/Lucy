#include "projectxmlreader.h"
#include "business/tree.h"

#include <QtXml/QDomDocument>
#include <QFile>
#include <QDebug>

using namespace Business;

/*static*/ QSharedPointer<Project> ProjectXmlReader::load(const QString& fileName)
{
  QSharedPointer<Project> project = nullptr;

  QDomDocument doc(fileName);
  QFile file(fileName);
  if (file.open(QIODevice::ReadOnly))
  {
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn))
    {
      qCritical() << "Error on project loading: " << errorStr
                  << "(line=" << errorLine
                  << ", column=" << errorColumn << ")";
      file.close();
    }
    else
    {
      QDomElement projectElem = doc.documentElement();

      const QString projectName = projectElem.attribute("name");
      project.reset(new Project(projectName));
      project->setFileInfo(QFileInfo(fileName));

      loadTrees(projectElem, *project);
      loadCurrentTree(projectElem, *project);

      file.close();
    }
  }

  return project;
}

void ProjectXmlReader::loadTrees(const QDomElement& projectNode, Project& project)
{
  const QDomNodeList treeNodes = projectNode.elementsByTagName("tree");
  for (int i=0; i<treeNodes.count(); ++i)
  {
    QDomElement treeNode = treeNodes.at(i).toElement();
    if (treeNode.hasAttribute("id"))
    {
      const int treeNodeId = treeNode.toElement().attribute("id").toInt();
      Tree* tree = new Tree(treeNodeId);
      project.add(tree);
    }
  }
}

void ProjectXmlReader::loadCurrentTree(const QDomElement& projectNode, Project& project)
{
  QDomElement currentTreeNode = projectNode.firstChildElement("current_tree");
  if (!currentTreeNode.isNull())
  {
    if (currentTreeNode.hasAttribute("id"))
    {
      Tree* tree = project.tree(currentTreeNode.attribute("id").toInt());
      project.setCurrentTree(tree);
    }
  }
}
