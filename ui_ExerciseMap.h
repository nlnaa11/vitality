#ifndef UI_EXERCISEMAP_H
#define UI_EXERCISEMAP_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_ExerciseMap
{
public:
    void setupUi(QWidget* ExerciseMap);
    void retranslateUi(QWidget* ExerciseMap);

    QWidget* gridLayoutWidget;
    QGridLayout* centralLayout;
    QTableWidget* tableWidget;
    QLabel* periodLbl;
    QPushButton* backBtn;
    QPushButton* runBtn;
    QPushButton* editBtn;
};

namespace Ui
{
    class ExerciseMap : public Ui_ExerciseMap {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXERCISEMAP_H
