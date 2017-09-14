#ifndef QUERYFIELD_H
#define QUERYFIELD_H

#include <QString>
#include <QMetaType>
#include <QUuid>

class QueryField
{
  public:
    QueryField(const QString& name, QMetaType::Type type);

    QUuid droid() const;
    QString name() const;
    QMetaType::Type type() const;

  private:
    QUuid _droid;
    QString _name;
    QMetaType::Type _type;
};

#endif // QUERYFIELD_H
