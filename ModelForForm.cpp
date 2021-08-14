#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "ModelForForm.h"

ModelForForm::ModelForForm(QObject* parent)
    : QObject(parent)
{
} // ModelForForm

ModelForForm::~ModelForForm()
{
} // ~ModelForForm

/** Public methods **/

void ModelForForm::setTable(const QString& name)
{
    tableName = name;
} // setTable

QVariantList ModelForForm::data() const
{
    if(dataList.isEmpty())
        return QVariantList();

    return dataList;
} // data

bool ModelForForm::isDuplicate(const QString& exercise) const
{
    QString EXISTS = QString("select exists "
                             "(select id from '%1' "
                             "where exercise = ?)");
    QSqlQuery q;
    q.prepare(EXISTS.arg(tableName));
    qDebug() << "36 " << q.lastError().type();
    q.addBindValue(exercise);

    q.exec();
    qDebug() << "40 " << q.lastError().type();
    q.next();

    if(q.value(0) != 0)
    {
        qDebug() << "a duplicate";
        return true;
    }
    else
    {
        qDebug() << "not a duplicate";
        return false;
    }
} // isDuplicate

void ModelForForm::insertRow(const QString& exercise, int min, int max,
                             bool second) const
{
    QString INSERT =  QString("insert into '%1' "
                              "(exercise, min, max, second, repeat, hidden) "
                              "values (?, ?, ?, ?, ?, false)");
    QSqlQuery q;
    q.prepare(INSERT.arg(tableName));
    qDebug() << "63 " << q.lastError().type();

    q.addBindValue(exercise);
    q.addBindValue(min);
    q.addBindValue(max);
    q.addBindValue(second);
    q.addBindValue(!second);

    q.exec();
    qDebug() << "72 " << q.lastError().type();
} // insertRow

void ModelForForm::removeRow(const QString& exercise) const
{
    QString DELETE =  QString("delete from '%1' "
                              "where exercise = ?");
    QSqlQuery q;
    q.prepare(DELETE.arg(tableName));
    qDebug() << "81 " << q.lastError().type();

    q.addBindValue(exercise);

    q.exec();
    qDebug() << "86 " << q.lastError().type();
} // removeRow

void ModelForForm::selectRow(const QString& exercise)
{
    QString SELECT =  QString("select exercise, min, max, second, repeat "
                      "from '%1' where exercise = ?");
    QSqlQuery q;
    q.prepare(SELECT.arg(tableName));
    qDebug() << "95 " << q.lastError().type();

    q.addBindValue(exercise);

    q.exec();
    qDebug() << "100 " << q.lastError().type();

    q.next();

    dataList << q.value(0).toString()
             << q.value(1).toInt()
             << q.value(2).toInt()
             << q.value(3).toBool()
             << q.value(4).toBool();
} // selectRow


