#include "treecreationdialog.h"
#include "ui_treecreationdialog.h"
#include "domain_object/person.h"
#include "domain_object/tree.h"
#include "project/projectmanager.h"
#include "project/project.h"

#include <QSqlQuery>
#include <QSqlRecord>

TreeCreationDialog::TreeCreationDialog(QWidget* parent)
  : QDialog(parent),
    _ui(new Ui::TreeCreationDialog)
{
  _ui->setupUi(this);
}

TreeCreationDialog::~TreeCreationDialog()
{
  delete _ui;
}

int TreeCreationDialog::exec()
{
  const int result = QDialog::exec();
  if (result)
  {
    const QString treeName = _ui->treeNameLineEdit->text();
    const QString firstName = _ui->firstNameLineEdit->text();
    const QString lastName = _ui->lastNameLideEdit->text();
    const QDate birthDate = _ui->birthDateEdit->date();

//    QString queryStr = "INSERT INTO public.\"Person\" (\"FirstName\", \"BirthDate\", \"LastName\") VALUES (:firstName, :birthDate, :lastName);";
//    QSqlQuery query;
//    query.prepare(queryStr);
//    query.bindValue(":firstName", QVariant::fromValue(firstName));
//    query.bindValue(":lastName", QVariant::fromValue(lastName));
//    query.bindValue(":birthDate", QVariant::fromValue(birthDate));

//    if (query.exec())
//    {
//      QVariant personId = query.lastInsertId();

//      QString queryStr = "INSERT INTO public.\"Tree\" (\"Name\", \"Reference\") VALUES (:treeName, :reference);";
//      QSqlQuery query;
//      query.prepare(queryStr);
//      query.bindValue(":treeName", QVariant::fromValue(treeName));
//      query.bindValue(":reference", personId);

//      query.exec();
//    }

    QSharedPointer<Project> currentProject = ProjectManager::getInstance()->currentProject();
    Q_ASSERT(!currentProject.isNull());

    Person* person = new Person(firstName, lastName, birthDate);
    currentProject->add(person);
    Tree* tree = new Tree(treeName, person);
    currentProject->add(tree);
  }

  return result;
}
