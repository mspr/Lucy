#include "projectxmlreader.h"
#include "domain_object/tree.h"

#include <QtXml/QDomDocument>
#include <QDebug>

/*static*/ Project ProjectXmlReader::load(const QString& fileName)
{
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
      return Project();
    }

    Project project;

    QDomElement docElem = doc.documentElement();

    loadTrees(docElem, project);

    file.close();
  }

  return Project();
}

void ProjectXmlReader::loadTrees(const QDomElement& projectNode, Project& project)
{
  QList<Tree> trees;

  const QDomNodeList treeNodes = projectNode.elementsByTagName("tree");
  for (int i=0; i<treeNodes.count(); ++i)
  {
    QDomNode treeNode = treeNodes.at(i);
//    const QString nodeName = treeNode.nodeName();
    const int treeNodeId = treeNode.toElement().attribute("id").toInt();
    trees.append(Tree(treeNodeId));
  }
}
