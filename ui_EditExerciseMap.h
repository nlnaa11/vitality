#ifndef UI_EDITEXERCISEMAP_H
#define UI_EDITEXERCISEMAP_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include "MyTableWidget.h"

QT_BEGIN_NAMESPACE

class Ui_EditExerciseMap
{
public:
    void setupUi(QDialog* EditExerciseMap);
    void retranslateUi(QWidget* EditExerciseMap);

    QWidget* gridLayoutWidget;
    QGridLayout* centralLayout;
    MyTableWidget* tableWidget;
    QPushButton* backBtn;
    QPushButton* newBtn;
    QLabel* periodLbl;

    QPushButton* deselectBtn;
    QPushButton* hideBtn;
    QPushButton* deleteBtn;
    QPushButton* allBtn;
    QLabel* selectedLbl;
};

namespace Ui
{
    class EditExerciseMap : public Ui_EditExerciseMap {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITEXERCISEMAP_H
