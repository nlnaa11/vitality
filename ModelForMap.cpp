#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QVariant>
#include <QDebug>
#include "ModelForMap.h"

ModelForMap::ModelForMap(QObject* parent)
    : QObject(parent)
{
} // ModelForMap

ModelForMap::~ModelForMap()
{
} // ~ModelForMap

/** Public methods **/

void ModelForMap::setupModel(const QString& tableName)
{
    emit startUpdate();

    m_tableName = tableName;

    if(!exList.isEmpty())
        exList.clear();

    QSqlQuery q;
    QString input = QString("SELECT exercise FROM '%1'"
                            " WHERE hidden = ?");

    q.prepare(input.arg(m_tableName));
    qDebug() << "33 " << q.lastError().type();

    q.addBindValue(false);
    q.exec();
    qDebug() << "37 " << q.lastError().type();

    while(q.next())
    {
        exList.append(q.value(0).toString());
        qDebug() << q.value(0).toString();
    }

    m_firstHidden = exList.size();

    q.addBindValue(true);
    q.exec();
    qDebug() << "49 " << q.lastError().type();

    while(q.next())
    {
        exList.append(q.value(0).toString());
        qDebug() << "/" + q.value(0).toString();
    }

    emit finishMultiUpdate();
} // setUpModel

void ModelForMap::updateModel(ChangeType type, const QString& value, int row)
{
    emit startUpdate();
    qDebug() << "startUpdate ";

    int oldRow{ row };

    switch(type)
    {
        case NewInserted:
            insertItem(value);
            break;

        case Edited:
        {    
            oldRow = exList.indexOf(value);
            moveToBegin(oldRow);
            break;
        }

        case Deleted:
            removeItem(oldRow);
            break;

        case Hidden:
        {
            if(oldRow < m_firstHidden)
                moveToEnd(oldRow);
            else
                moveToBegin(oldRow);
            break;
        }
    }

    qDebug() << "finishOneUpdate ";
    emit finishOneUpdate(type, oldRow);
} // updateModel

void ModelForMap::updateModel(ChangeType type, const QVector<int>& rowList)
{
    emit startUpdate();
    qDebug() << "startMultiUpdate ";

    // Note: the items in the list are arranged in descending order

    switch(type)
    {
        case NewInserted:
            break;

        case Edited:
            break;

        case Deleted:
        {
            for(auto row : rowList)
                removeItem(row);
            break;
        }

        case Hidden:
        {
            // if the lowest row is less than the firstHidden,
            // we hide all the items
            if(rowList.last() < m_firstHidden)
            {
                // descending order
                for(auto row : rowList)
                {
                    if(row < m_firstHidden)
                        moveToEnd(row);
                }
            }
            // otherwise, we open all the items
            else
            {
                // ascending order
                int row = rowList.count() - 1;
                for(; row > -1; --row )
                {
                    if(row >= m_firstHidden)
                        moveToBegin(row);
                }
            }
            break;
        }
    }

    qDebug() << "finistMultiUpdate ";
    emit finishMultiUpdate();
} // updateModel(QList)

int ModelForMap::rowCount(bool full) const
{
    if(full)
        return exList.size();
    else
        return m_firstHidden;
} // rowCount

QString ModelForMap::data(int row)
{
    if(row < 0 || row >= exList.size())
        return QString();
    else
        return exList.at(row);
} // data

bool ModelForMap::isHidden(const QString& value) const
{
    int row = exList.indexOf(value);

    // [0, firstHidden)
    if(row > -1 && row < m_firstHidden)
        return false;
    else
        return true;
} // isHidden

int ModelForMap::firstHidden() const
{
    return m_firstHidden;
} // FirstHidden

const QString& ModelForMap::tableName() const
{
    return m_tableName;
} // tableName

/**
 * the order of the data in the database may not coincide
 * with the order of the data in the list that the views are oriented to
**/
const QVector<int> ModelForMap::dataForRandom() const
{
    QVector<int> data;
    data.reserve(m_firstHidden * 2);

    QSqlQuery q;
    QString input = QString("SELECT min, max FROM '%1'"
                            " WHERE exercise = ?");
    
    q.prepare(input.arg(m_tableName));
    qDebug() << "182 " << q.lastError().type();

    int row{0};
    while(row < m_firstHidden)
    {
        q.addBindValue(exList.at(row));

        if(!q.exec())
        {
            qDebug() << "191 " << q.lastError();
            return QVector<int>({0});
        }

        q.next();
        data << q.value("min").toInt()
             << q.value("max").toInt();

        ++row;
    }
    return data;
} // dataForRandom

/** Private methods
 *
 * A new item is _inserted_at_the_beginning of the list.
 *
 * Changing an existing item (not the name) and
 * opening a hidden item provokes _moving_to_the_beginning.
 *
 * Hiding an open item provokes _moving_to_the_end.
 *
 * Deleting an item from the list _removes
 * all related data from the database.
**/

void ModelForMap::insertItem(const QString& value)
{
    exList.prepend(value);

    ++m_firstHidden;
} // insertItem

void ModelForMap::removeItem(int row)
{
    QString value{ exList.at(row) };

    QSqlQuery q;
    QString input = QString("DELETE FROM '%1'"
                            " WHERE exercise = ?");

    q.prepare(input.arg(m_tableName));
    qDebug() << "230 " << q.lastError().type();
    q.addBindValue(value);

    q.exec();
    qDebug() << "234 " << q.lastError().type();

    exList.removeAt(row);

    if(row < m_firstHidden) --m_firstHidden;
} // removeItem

void ModelForMap::moveToBegin(int row)
{
    QString value{ exList.at(row) };

    QSqlQuery q;
    QString input = QString("UPDATE '%1'"
                            " SET hidden = false "
                            " WHERE exercise = ?");

    q.prepare(input.arg(m_tableName));
    qDebug() <<  "248 " << q.lastError().type();
    q.addBindValue(value);

    q.exec();
    qDebug() << "252 " << q.lastError().type();

    exList.removeAt(row);
    exList.prepend(value);

    if(row >= m_firstHidden) ++m_firstHidden;
} // moveToBegin

void ModelForMap::moveToEnd(int row)
{
    QString value{ exList.at(row) };

    QSqlQuery q;
    QString input = QString("UPDATE '%1'"
                            " SET hidden = true "
                            " WHERE exercise = ?");

    q.prepare(input.arg(m_tableName));
    qDebug() << "270 " << q.lastError().type();
    q.addBindValue(value);

    q.exec();
    qDebug() << "274 " << q.lastError().type();

    exList.removeAt(row);
    exList.append(value);

    --m_firstHidden;
} // moveToEnd
