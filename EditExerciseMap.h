#ifndef EDITEXERCISEMAP_H
#define EDITEXERCISEMAP_H

#include <QDialog>
#include "ModelForMap.h"

class EditExercise;
class QTableWidgetItem;

namespace Ui { class EditExerciseMap; }

class EditExerciseMap : public QDialog
{
    Q_OBJECT

public:
    EditExerciseMap(ModelForMap* model, QWidget* parent = nullptr);
    virtual ~EditExerciseMap();

protected:
    void changeEvent(QEvent* e) override;
    void resizeEvent(QResizeEvent* e) override;

signals:
    void backToMap();

private slots:
    void updateUi();
    void updateOne(ModelForMap::ChangeType type, int oldRow);

    // a reaction to the work of the ui_editEx
    void itemEdited(const QString& exercise);
    void newItemInserted(const QString& exercise);
    void closeEditExercise();

    // a reaction to its own work in the filter mode
    void rowSelected(QTableWidgetItem* item);
    void deselectBtn_clicked();
    void hideBtn_clicked();
    void deleteBtn_clicked();
    void allBtn_clicked();
    bool selectAll(bool select);

private:
    void setupModel(ModelForMap* model);
    void createSortUi();
    void createFilterUi(int row);

    void setNewRow(int row);
    void setNewRowFromOld(int newRow, int oldRow);

    void editExercise(const QString& exercise);

    Ui::EditExerciseMap* ui;
    ModelForMap* model = nullptr;

    EditExercise* ui_editEx = nullptr;

    bool ignoreSignal{false};
};

#endif // EDITEXERCISEMAP_H
