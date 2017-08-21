#ifndef PROJECTXMLWRITER_H
#define PROJECTXMLWRITER_H

#include <QXmlStreamWriter>

#include "project.h"

class ProjectXmlWriter : QXmlStreamWriter
{
  public:
    ProjectXmlWriter() = delete;

    static void write(Project* project);
};

#endif // PROJECTXMLWRITER_H
