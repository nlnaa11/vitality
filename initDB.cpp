#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
//#include <QApplication>
#include <QFile>
#include <QStandardPaths>
#include <QDebug>
#include "initDB.h"

InitDB::~InitDB()
{
    db.close();
} // ~InitDB

/** Public methods **/

void InitDB::connectDB(bool& luck)
{
//    QString path = qApp->applicationDirPath() + "/exercise";
    QString path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)
                    + "/Vitality/exercise";

    qDebug() << path;
    if(!QFile(path).exists())
        luck = this->initDB();
    else
        luck = this->openDB();
} // connectDB

/** Private methods **/

bool InitDB::openDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("main");
//    db.setDatabaseName("exercise");
    db.setDatabaseName(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)
                        + "/Vitality/exercise");

    qDebug() << db.databaseName();

    if(!db.open())
    {
        showError(db.lastError().text(), "db.open()");
        return false;
    }

    return true;
} // openDB

bool InitDB::initDB()
{
    if(this->openDB())
        if(this->createTables())
            return true;

    return false;
} // initDB

bool InitDB::createTables()
{
    QString input = "CREATE TABLE %1 (id INTEGER PRIMARY KEY,"
                                  " exercise VARCHAR(40) UNIQUE,"
                                  " min INTEGER,"
                                  " max INTEGER,"
                                  " repeat BOOLEAN true,"
                                  " second BOOLEAN false,"
                                  " hidden BOOLEAN false)";
    QSqlQuery query;

    if(!query.exec(input.arg("morning")))
    {
        showError(query.lastError().text(), query.lastQuery());
        return false;
    }

    if(!query.exec(input.arg("afternoon")))
    {
        showError(query.lastError().text(), query.lastQuery());
        return false;
    }

    if(!query.exec(input.arg("evening")))
    {
        showError(query.lastError().text(), query.lastQuery());
        return false;
    }

    return true;
} // createTables

void InitDB::showError(const QString& error, const QString& query = "")
{
    qDebug() << "Unable to initialize Database.\n"
             << "Error: " + error
             << "Query: " + query;
} // showError
