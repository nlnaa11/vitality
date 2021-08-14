#ifndef UI_EDITEXERCISE_H
#define UI_EDITEXERCISE_H

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_EditExercise
{
public:
    void setupUi(QDialog* EditExercise);
    void retranslateUi(QWidget* EditExercise);

    QWidget* gridLayoutWidget;
    QGridLayout* centralLayout;
    QPushButton* backBtn;
    QPushButton* okBtn;
    QLabel* exerciseLbl;
    QLineEdit* exerciseEdit;
    QLabel* minLbl;
    QLabel* maxLbl;
    QLineEdit* minEdit;
    QLineEdit* maxEdit;
    QCheckBox* seconds;
    QCheckBox* repeats;
    QFrame* topFrame;
    QFrame* bottomFrame;
};

namespace Ui
{
    class EditExercise : public Ui_EditExercise {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITEXERCISE_H
