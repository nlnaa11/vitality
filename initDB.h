#ifndef INITDB_H
#define INITDB_H

#include <QtSql/QSqlDatabase>
class QSqlDatabase;

class InitDB
{
public:
    ~InitDB();  // close the db

    void connectDB(bool& luck);

private:
    bool openDB();
    bool initDB();
    bool createTables();
    void showError(const QString& error, const QString& query);

private:
    QSqlDatabase db;
};

#endif // CONNECTDB_H
