#include "projectxmlwriter.h"
#include "domain_object/tree.h"

void ProjectXmlWriter::write(Project* project)
{
  Q_ASSERT(project != nullptr);

  const QString fileName = project->fileName();
  QFile file(fileName);
  if (file.open(QIODevice::WriteOnly))
  {
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);

    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("project");
    xmlWriter.writeAttribute("name", project->name());

    for (int i=0; i<project->trees().count(); ++i)
    {
      Tree* tree = project->trees().at(i);
      xmlWriter.writeStartElement("tree");
      xmlWriter.writeAttribute("id", QString::number(tree->id()));
      xmlWriter.writeEndElement();
    }

    xmlWriter.writeStartElement("current_tree");
    xmlWriter.writeAttribute("id", QString::number(project->currentTree()->id()));
    xmlWriter.writeEndElement();

    xmlWriter.writeEndDocument();

    file.close();
  }
}
