#include "ui_EditExercise.h"
#include "EditExercise.h"
#include <QDebug>
#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>

void Ui_EditExercise::setupUi(QDialog* EditExercise)
{
    Qt::WindowFlags flags = Qt::CustomizeWindowHint;
    EditExercise->setWindowFlags(flags);
    EditExercise->setBaseSize(230, 380);

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHeightForWidth(EditExercise->sizePolicy().hasHeightForWidth());
    EditExercise->setSizePolicy(sizePolicy);
    EditExercise->setAcceptDrops(true);
    EditExercise->setLocale(QLocale(QLocale::English, QLocale::World));
    EditExercise->setSizeGripEnabled(true);

    gridLayoutWidget = new QWidget(EditExercise);
    gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
    gridLayoutWidget->setGeometry(QRect(10, 10, 211, 361));

    centralLayout = new QGridLayout(gridLayoutWidget);
    centralLayout->setObjectName(QString::fromUtf8("centralLayout"));
    centralLayout->setSizeConstraint(QLayout::SetNoConstraint);
    centralLayout->setContentsMargins(10, 5, 10, 5);
    centralLayout->setVerticalSpacing(10);
    centralLayout->setAlignment(Qt::AlignCenter);

    EditExercise->setLayout(centralLayout);

    backBtn = new QPushButton();
    backBtn->setObjectName(QString::fromUtf8("backBtn"));
    QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    sizePolicy1.setHeightForWidth(backBtn->sizePolicy().hasHeightForWidth());
    backBtn->setSizePolicy(sizePolicy1);
    backBtn->setIcon(QIcon(":/images/back.png"));
    backBtn->setIconSize(QSize(48, 48));
    backBtn->setFlat(true);
    backBtn->setAutoDefault(false);

    centralLayout->addWidget(backBtn, 7, 0, 1, 1);

    okBtn = new QPushButton();
    okBtn->setObjectName(QString::fromUtf8("okBtn"));
    sizePolicy1.setHeightForWidth(okBtn->sizePolicy().hasHeightForWidth());
    okBtn->setSizePolicy(sizePolicy1);
    okBtn->setIcon(QIcon(":/images/ok.png"));
    okBtn->setIconSize(QSize(48, 48));
    okBtn->setFlat(true);
    okBtn->setDefault(true);

    centralLayout->addWidget(okBtn, 7, 1, 1, 1);

    exerciseLbl = new QLabel();
    exerciseLbl->setObjectName(QString::fromUtf8("exerciseLbl"));
    sizePolicy.setHeightForWidth(exerciseLbl->sizePolicy().hasHeightForWidth());
    exerciseLbl->setSizePolicy(sizePolicy);
    exerciseLbl->setScaledContents(true);
    exerciseLbl->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);

    centralLayout->addWidget(exerciseLbl, 1, 0, 1, 2);

    exerciseEdit = new QLineEdit();
    exerciseEdit->setObjectName(QString::fromUtf8("exerciseEdit"));
    sizePolicy1.setHeightForWidth(exerciseEdit->sizePolicy().hasHeightForWidth());
    exerciseEdit->setSizePolicy(sizePolicy1);
    exerciseEdit->setAlignment(Qt::AlignCenter);
    exerciseEdit->setDragEnabled(true);
    exerciseEdit->setForegroundRole(QPalette::Light);
    exerciseEdit->setPlaceholderText("A-Za-zА-Яа-я0-9 _");

    centralLayout->addWidget(exerciseEdit, 2, 0, 1, 2);

    minLbl = new QLabel();
    minLbl->setObjectName(QString::fromUtf8("minLbl"));
    sizePolicy.setHeightForWidth(minLbl->sizePolicy().hasHeightForWidth());
    minLbl->setSizePolicy(sizePolicy);
    minLbl->setScaledContents(true);
    minLbl->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);

    centralLayout->addWidget(minLbl, 3, 0, 1, 1);

    maxLbl = new QLabel();
    maxLbl->setObjectName(QString::fromUtf8("maxLbl"));
    sizePolicy.setHeightForWidth(maxLbl->sizePolicy().hasHeightForWidth());
    maxLbl->setSizePolicy(sizePolicy);
    maxLbl->setScaledContents(true);
    maxLbl->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);

    centralLayout->addWidget(maxLbl, 3, 1, 1, 1);

    minEdit = new QLineEdit();
    minEdit->setObjectName(QString::fromUtf8("minEdit"));
    sizePolicy1.setHeightForWidth(minEdit->sizePolicy().hasHeightForWidth());
    minEdit->setSizePolicy(sizePolicy1);
    minEdit->setAlignment(Qt::AlignCenter);
    minEdit->setFrame(true);
    minEdit->setForegroundRole(QPalette::Light);
    minEdit->setPlaceholderText("[0;999]");

    centralLayout->addWidget(minEdit, 4, 0, 1, 1);

    maxEdit = new QLineEdit();
    maxEdit->setObjectName(QString::fromUtf8("maxEdit"));
    sizePolicy1.setHeightForWidth(maxEdit->sizePolicy().hasHeightForWidth());
    maxEdit->setSizePolicy(sizePolicy1);
    maxEdit->setAlignment(Qt::AlignCenter);
    maxEdit->setFrame(true);
    maxEdit->setForegroundRole(QPalette::Light);
    maxEdit->setPlaceholderText("[0:999]");

    centralLayout->addWidget(maxEdit, 4, 1, 1, 1);

    seconds = new QCheckBox();
    seconds->setObjectName(QString::fromUtf8("seconds"));
    sizePolicy1.setHeightForWidth(seconds->sizePolicy().hasHeightForWidth());
    seconds->setSizePolicy(sizePolicy1);
    seconds->setLayoutDirection(Qt::RightToLeft);
    seconds->setAcceptDrops(true);
    seconds->setAutoExclusive(true);
    seconds->setStyleSheet("QCheckBox::indicator {"
                                      "width: 15px;"
                                      "height: 15px }");

    centralLayout->addWidget(seconds, 5, 0, 1, 1);

    repeats = new QCheckBox();
    repeats->setObjectName(QString::fromUtf8("repeats"));
    sizePolicy1.setHeightForWidth(repeats->sizePolicy().hasHeightForWidth());
    repeats->setSizePolicy(sizePolicy1);
    repeats->setAcceptDrops(true);
    repeats->setAutoExclusive(true);
    repeats->setChecked(true);

    centralLayout->addWidget(repeats, 5, 1, 1, 1);

    bottomFrame = new QFrame();
    bottomFrame->setObjectName(QString::fromUtf8("bottomFrame"));
    bottomFrame->setEnabled(false);
    sizePolicy.setHeightForWidth(bottomFrame->sizePolicy().hasHeightForWidth());
    bottomFrame->setSizePolicy(sizePolicy);
    bottomFrame->setFrameShape(QFrame::NoFrame);
    bottomFrame->setFrameShadow(QFrame::Raised);

    centralLayout->addWidget(bottomFrame, 6, 0, 1, 2);

    topFrame = new QFrame();
    topFrame->setObjectName(QString::fromUtf8("topFrame"));
    topFrame->setEnabled(false);
    sizePolicy.setHeightForWidth(topFrame->sizePolicy().hasHeightForWidth());
    topFrame->setSizePolicy(sizePolicy);
    topFrame->setFrameShape(QFrame::NoFrame);
    topFrame->setFrameShadow(QFrame::Raised);

    centralLayout->addWidget(topFrame, 0, 0, 1, 2);

    QFont font{ "Monospace" };
    font.setStretch(QFont::Expanded);
    font.setPixelSize(15);

    exerciseLbl->setFont(font);
    minLbl->setFont(font);
    maxLbl->setFont(font);
    seconds->setFont(font);
    repeats->setFont(font);

    font.setStretch(QFont::Unstretched);
    font.setPixelSize(14);

    exerciseEdit->setFont(font);
    minEdit->setFont(font);
    maxEdit->setFont(font);

    centralLayout->setRowStretch(0, 1);
    centralLayout->setRowStretch(1, 1);
    centralLayout->setRowStretch(2, 1);
    centralLayout->setRowStretch(3, 1);
    centralLayout->setRowStretch(4, 1);
    centralLayout->setRowStretch(5, 1);
    centralLayout->setRowStretch(6, 1);
    centralLayout->setRowStretch(7, 1);
    centralLayout->setColumnStretch(0, 1);
    centralLayout->setColumnStretch(1, 1);
    QWidget::setTabOrder(okBtn, backBtn);

    retranslateUi(EditExercise);

    QMetaObject::connectSlotsByName(EditExercise);

    EditExercise->resize(230, 380);
} // setupUi

void Ui_EditExercise::retranslateUi(QWidget* EditExercise)
{
    exerciseLbl->setText(QApplication::translate("EditExercise", "exercise", nullptr));
    minLbl->setText(QApplication::translate("EditExercise", "min", nullptr));
    maxLbl->setText(QApplication::translate("EditExercise", "max", nullptr));
    seconds->setText(QApplication::translate("EditExercise", "seconds", nullptr));
    repeats->setText(QApplication::translate("EditExercise", "repeats", nullptr));
    Q_UNUSED(EditExercise);
} // retranslateUi
