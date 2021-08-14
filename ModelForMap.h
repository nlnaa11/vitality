#ifndef MODELFORMAP_H
#define MODELFORMAP_H

#include <QStringList>
#include <QObject>

class ModelForMap : public QObject
{
    Q_OBJECT

public:
    ModelForMap(QObject* parent = nullptr);
    virtual ~ModelForMap();

    enum ChangeType { NewInserted, Edited, Deleted, Hidden, };

    void setupModel(const QString& tableName);
    void updateModel(ChangeType type, const QString& value = "", int row = -1);
    void updateModel(ChangeType type, const QVector<int>& rowInt);

    int rowCount(bool full) const;
    QString data(int row);  

    bool isHidden(const QString& value) const;
    int firstHidden() const;
    const QString& tableName() const;
    const QVector<int> dataForRandom() const;

signals:
    void startUpdate();
    void finishMultiUpdate();
    void finishOneUpdate(ChangeType type, int oldRow);

private:
    void insertItem(const QString& value);
    void removeItem(int row);
    void moveToBegin(int row);
    void moveToEnd(int row);

    QString m_tableName{""};
    QStringList exList;

    int m_firstHidden{-1};
};

#endif // MODELFORMAP_H
