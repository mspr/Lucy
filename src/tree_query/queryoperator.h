#ifndef QUERYOPERATOR_H
#define QUERYOPERATOR_H

#include <QObject>

class QueryOperator : public QObject
{
  public:
    QueryOperator(const QString& text, QObject* parent = nullptr);

    QString text() const;
    void setText(const QString& text);

  private:
    QString _text;
};

#endif // QUERYOPERATOR_H
