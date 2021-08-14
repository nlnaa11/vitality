#include "ui_EditExerciseMap.h"
#include "EditExerciseMap.h"
#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QHeaderView>

void Ui_EditExerciseMap::setupUi(QDialog* EditExerciseMap)
{
    Qt::WindowFlags flags = Qt::CustomizeWindowHint;
    EditExerciseMap->setWindowFlags(flags);
    EditExerciseMap->setBaseSize(230, 380);

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHeightForWidth(EditExerciseMap->sizePolicy().hasHeightForWidth());
    EditExerciseMap->setSizePolicy(sizePolicy);
    EditExerciseMap->setAcceptDrops(true);
    EditExerciseMap->setLocale(QLocale(QLocale::English, QLocale::World));
    EditExerciseMap->setSizeGripEnabled(true);

    gridLayoutWidget = new QWidget(EditExerciseMap);
    gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
    gridLayoutWidget->setGeometry(QRect(10, 10, 211, 361));

    centralLayout = new QGridLayout(gridLayoutWidget);
    centralLayout->setObjectName(QString::fromUtf8("centralLayout"));
    centralLayout->setSizeConstraint(QLayout::SetNoConstraint);
    centralLayout->setContentsMargins(10, 5, 10, 5);
    centralLayout->setVerticalSpacing(10);
    centralLayout->setAlignment(Qt::AlignCenter);

    EditExerciseMap->setLayout(centralLayout);

    tableWidget = new MyTableWidget();
    tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
    sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
    tableWidget->setSizePolicy(sizePolicy);
    tableWidget->setMouseTracking(true);
    tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    tableWidget->setColumnCount(2);
    tableWidget->horizontalHeader()->setDefaultSectionSize(30);
    tableWidget->verticalHeader()->setDefaultSectionSize(30);
    tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    tableWidget->horizontalHeader()->hide();
    tableWidget->verticalHeader()->hide();

    centralLayout->addWidget(tableWidget, 1, 0, 6, 3);

    periodLbl = new QLabel();
    periodLbl->setObjectName(QString::fromUtf8("periodLbl"));
    sizePolicy.setHeightForWidth(periodLbl->sizePolicy().hasHeightForWidth());
    periodLbl->setSizePolicy(sizePolicy);
    periodLbl->setAlignment(Qt::AlignBottom | Qt::AlignLeading | Qt::AlignLeft);
    periodLbl->setLocale(QLocale(QLocale::English, QLocale::World));

    centralLayout->addWidget(periodLbl, 0, 0, 1, 2);

    QFont font{ "Monospace" };
    font.setStretch(QFont::Expanded);
    font.setPixelSize(15);
    periodLbl->setFont(font);

    font.setStretch(QFont::Unstretched);
    font.setPixelSize(14);
    tableWidget->setFont(font);

    backBtn = new QPushButton();
    backBtn->setObjectName(QString::fromUtf8("backBtn"));
    QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    sizePolicy2.setHeightForWidth(backBtn->sizePolicy().hasHeightForWidth());
    backBtn->setSizePolicy(sizePolicy2);
    backBtn->setIcon(QIcon(":/images/back.png"));
    backBtn->setIconSize(QSize(48, 48));
    backBtn->setFlat(true);

    centralLayout->addWidget(backBtn, 7, 0, 1, 1);

    newBtn = new QPushButton();
    newBtn->setObjectName(QString::fromUtf8("newBtn"));
    sizePolicy2.setHeightForWidth(newBtn->sizePolicy().hasHeightForWidth());
    newBtn->setSizePolicy(sizePolicy2);
    newBtn->setIcon(QIcon(":/images/new.png"));
    newBtn->setIconSize(QSize(48, 48));
    newBtn->setFlat(true);

    centralLayout->addWidget(newBtn, 7, 1, 1, 1);

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
    centralLayout->setColumnStretch(2, 1);

    retranslateUi(EditExerciseMap);

    QMetaObject::connectSlotsByName(EditExerciseMap);

    EditExerciseMap->resize(230, 380);
} // setupUi

void Ui_EditExerciseMap::retranslateUi(QWidget* EditExerciseMap)
{
    Q_UNUSED(EditExerciseMap);
} // retranslateUi
