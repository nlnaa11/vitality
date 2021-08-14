#ifndef EXERCISEMAP_H
#define EXERCISEMAP_H

#include <QWidget>

class ModelForMap;
class PeriodMap;
class EditExerciseMap;

namespace Ui { class ExerciseMap; }

class ExerciseMap : public QWidget
{
    Q_OBJECT

public:
    ExerciseMap(QWidget* parent = nullptr);
    virtual ~ExerciseMap();

    void show_PeriodMap();  //for main

protected:
    void changeEvent(QEvent* e) override;
    void hideEvent(QHideEvent *e) override;
    void resizeEvent(QResizeEvent* e) override;

private slots:
    void periodRecieved(const QString& period);
    void updateUi();

    void on_runBtn_clicked();

private:
    void setupModel();
    void createUi();
    void setupStyle();

    Ui::ExerciseMap* ui;
    ModelForMap* model;

    PeriodMap* ui_PeriodMap;
    EditExerciseMap* ui_EditExMap;
};

#endif // EXERCISEMAP_H
