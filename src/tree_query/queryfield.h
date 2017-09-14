#ifndef QUERYFIELD_H
#define QUERYFIELD_H

#include <QObject>
#include <QUuid>

class QueryField : public QObject
{
  public:
    QueryField(const QString& name, QMetaType::Type type, QObject* parent = nullptr);

    QUuid droid() const;
    QString name() const;
    QMetaType::Type type() const;

  private:
    QUuid _droid;
    QString _name;
    QMetaType::Type _type;
};

#endif // QUERYFIELD_H
