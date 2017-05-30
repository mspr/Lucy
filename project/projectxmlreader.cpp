#include "projectxmlreader.h"
#include "domain_object/tree.h"

#include <QtXml/QDomDocument>
#include <QFile>
#include <QDebug>

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
      project.reset(new Project());

      QDomElement docElem = doc.documentElement();

      loadTrees(docElem, *project);
      loadCurrentTree(docElem, *project);

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
      project.AddTree(treeNodeId);
    }
  }
}

void ProjectXmlReader::loadCurrentTree(const QDomElement& projectNode, Project& project)
{
  QDomElement currentTreeNode = projectNode.firstChildElement("current_tree");
  if (!currentTreeNode.isNull())
  {
    if (currentTreeNode.hasAttribute("id"))
      project.setCurrentTree(currentTreeNode.attribute("id").toInt());
  }
}
