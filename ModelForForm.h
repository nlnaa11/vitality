#ifndef MODELFORFORM_H
#define MODELFORFORM_H

#include <QObject>
#include <QVariantList>

class ModelForForm : public QObject
{
    Q_OBJECT

public:
    ModelForForm(QObject* parent = nullptr);
    virtual ~ModelForForm();

    void setTable(const QString& name);
    QVariantList data() const;

    bool isDuplicate(const QString& exercise) const;
    void insertRow(const QString& exercise, int min, int max,
                   bool second) const;
    void removeRow(const QString& exercise) const;
    void selectRow(const QString& exercise);

private:
    QString tableName;
    QVariantList dataList;
};

#endif // MODELFORFORM_H
