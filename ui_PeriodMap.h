#ifndef UI_PERIODMAP_H
#define UI_PERIODMAP_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QDialog>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PeriodMap
{
public:
    void setupUi(QDialog* PeriodMap);
    void retranslateUi(QWidget* PeriodMap);

    QWidget* gridLayoutWidget;
    QGridLayout* gridLayout;
    QFrame* bottomFrame;
    QFrame* leftFrame;
    QFrame* topFrame;
    QPushButton* eveningBtn;
    QPushButton* afternoonBtn;
    QPushButton* morningBtn;
    QComboBox* languageBox;
};

namespace Ui
{
    class PeriodMap : public Ui_PeriodMap {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERIODMAP_H
