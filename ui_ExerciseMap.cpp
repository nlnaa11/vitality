#include "ui_ExerciseMap.h"
#include "ExerciseMap.h"
#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QHeaderView>
#include <QDebug>

void Ui_ExerciseMap::setupUi(QWidget* ExerciseMap)
{
    Qt::WindowFlags flags = Qt::CustomizeWindowHint;
    ExerciseMap->setWindowFlags(flags);
    ExerciseMap->setBaseSize(230, 380);

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHeightForWidth(ExerciseMap->sizePolicy().hasHeightForWidth());
    ExerciseMap->setSizePolicy(sizePolicy);
    ExerciseMap->setAcceptDrops(true);
    ExerciseMap->setLocale(QLocale(QLocale::English, QLocale::World));

    gridLayoutWidget = new QWidget(ExerciseMap);
    gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
    gridLayoutWidget->setGeometry(QRect(10, 10, 211, 361));

    centralLayout = new QGridLayout(gridLayoutWidget);
    centralLayout->setObjectName(QString::fromUtf8("centralLayout"));
    centralLayout->setSizeConstraint(QLayout::SetNoConstraint);
    centralLayout->setContentsMargins(10, 5, 10, 5);
    centralLayout->setVerticalSpacing(10);
    centralLayout->setAlignment(Qt::AlignCenter);

    ExerciseMap->setLayout(centralLayout);

    tableWidget = new QTableWidget(gridLayoutWidget);
    tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
    QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
    sizePolicy2.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
    tableWidget->setSizePolicy(sizePolicy);
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

    periodLbl = new QLabel(gridLayoutWidget);
    periodLbl->setObjectName(QString::fromUtf8("periodLbl"));
    sizePolicy.setHeightForWidth(periodLbl->sizePolicy().hasHeightForWidth());
    periodLbl->setSizePolicy(sizePolicy);
    periodLbl->setAcceptDrops(true);
    periodLbl->setScaledContents(false);
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

    backBtn = new QPushButton(gridLayoutWidget);
    backBtn->setObjectName(QString::fromUtf8("backBtn"));
    QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    sizePolicy1.setHeightForWidth(backBtn->sizePolicy().hasHeightForWidth());
    backBtn->setSizePolicy(sizePolicy1);
    backBtn->setIcon(QIcon(":/images/back.png"));
    backBtn->setIconSize(QSize(48, 48));
    backBtn->setFlat(true);
    backBtn->setDefault(false);

    centralLayout->addWidget(backBtn, 7, 0, 1, 1);

    runBtn = new QPushButton(gridLayoutWidget);
    runBtn->setObjectName(QString::fromUtf8("runBtn"));
    sizePolicy1.setHeightForWidth(runBtn->sizePolicy().hasHeightForWidth());
    runBtn->setSizePolicy(sizePolicy1);
    runBtn->setIcon(QIcon(":/images/run.png"));
    runBtn->setIconSize(QSize(48, 48));
    runBtn->setFlat(true);
    runBtn->setDefault(true);

    centralLayout->addWidget(runBtn, 7, 1, 1, 1);

    editBtn = new QPushButton(gridLayoutWidget);
    editBtn->setObjectName(QString::fromUtf8("backBtn"));
    sizePolicy1.setHeightForWidth(editBtn->sizePolicy().hasHeightForWidth());
    editBtn->setSizePolicy(sizePolicy1);
    editBtn->setIcon(QIcon(":/images/edit.png"));
    editBtn->setIconSize(QSize(48, 48));
    editBtn->setFlat(true);
    editBtn->setDefault(false);

    centralLayout->addWidget(editBtn, 7, 2, 1, 1);

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
    QWidget::setTabOrder(backBtn, runBtn);
    QWidget::setTabOrder(runBtn, editBtn);

    retranslateUi(ExerciseMap);

    QMetaObject::connectSlotsByName(ExerciseMap);

    ExerciseMap->resize(230, 380);
} // setupUi

void Ui_ExerciseMap::retranslateUi(QWidget* ExerciseMap)
{
    Q_UNUSED(ExerciseMap);
} // retranslateUi
