#ifndef EDITEXERCISE_H
#define EDITEXERCISE_H

#include <QDialog>

class ModelForForm;
class ReplaceOrRename;

namespace Ui { class EditExercise; }

class EditExercise : public QDialog
{
    Q_OBJECT

public:
    explicit EditExercise(const QString& period, const QString& exercise = "",
                          QWidget* parent = nullptr);
    virtual ~EditExercise();

protected:
    void resizeEvent(QResizeEvent* e) override;

signals:
    void itemEdited(const QString& exercise);
    void newItemInserted(const QString& exercise);
    void noChanges();

private slots:
    void on_okBtn_clicked();

private:
    void setupModel(const QString& period, const QString& exercise);
    void createUi();
    void createMapper();
    void createValidator();
    void processDuplicate();
    void replace();

private:
    Ui::EditExercise* ui;
    ModelForForm* model = nullptr;

    ReplaceOrRename* dialog = nullptr;
};
#endif // EDITEXERCISE_H
