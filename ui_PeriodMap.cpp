#include "ui_PeriodMap.h"
#include "PeriodMap.h"
#include <QDebug>
#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>

void Ui_PeriodMap::setupUi(QDialog* PeriodMap)
{
    Qt::WindowFlags flags = Qt::CustomizeWindowHint;
    PeriodMap->setWindowFlags(flags);
    PeriodMap->setBaseSize(230, 380);

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHeightForWidth(PeriodMap->sizePolicy().hasHeightForWidth());
    PeriodMap->setSizePolicy(sizePolicy);
    PeriodMap->setAcceptDrops(true);
    PeriodMap->setLocale(QLocale(QLocale::English, QLocale::World));
    PeriodMap->setSizeGripEnabled(true);

    gridLayoutWidget = new QWidget(PeriodMap);
    gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
    gridLayoutWidget->setGeometry(QRect(10, 10, 211, 361));

    gridLayout = new QGridLayout(gridLayoutWidget);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout->setSizeConstraint(QLayout::SetNoConstraint);
    gridLayout->setHorizontalSpacing(5);
    gridLayout->setVerticalSpacing(3);
    PeriodMap->setLayout(gridLayout);

    bottomFrame = new QFrame(gridLayoutWidget);
    bottomFrame->setObjectName(QString::fromUtf8("bottomFrame"));
    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy1.setHeightForWidth(bottomFrame->sizePolicy().hasHeightForWidth());
    bottomFrame->setSizePolicy(sizePolicy1);
    bottomFrame->setFrameShape(QFrame::NoFrame);
    bottomFrame->setFrameShadow(QFrame::Raised);

    gridLayout->addWidget(bottomFrame, 6, 0, 1, 3);

    leftFrame = new QFrame(gridLayoutWidget);
    leftFrame->setObjectName(QString::fromUtf8("leftFrame"));
    sizePolicy1.setHeightForWidth(leftFrame->sizePolicy().hasHeightForWidth());
    leftFrame->setSizePolicy(sizePolicy1);
    leftFrame->setFrameShape(QFrame::NoFrame);
    leftFrame->setFrameShadow(QFrame::Raised);

    gridLayout->addWidget(leftFrame, 2, 0, 1, 2);

    topFrame = new QFrame(gridLayoutWidget);
    topFrame->setObjectName(QString::fromUtf8("topFrame"));
    sizePolicy1.setHeightForWidth(topFrame->sizePolicy().hasHeightForWidth());
    topFrame->setSizePolicy(sizePolicy1);
    topFrame->setFrameShape(QFrame::NoFrame);
    topFrame->setFrameShadow(QFrame::Raised);

    gridLayout->addWidget(topFrame, 1, 0, 1, 3);

    eveningBtn = new QPushButton(gridLayoutWidget);
    eveningBtn->setObjectName(QString::fromUtf8("eveningBtn"));
    sizePolicy.setHeightForWidth(eveningBtn->sizePolicy().hasHeightForWidth());
    eveningBtn->setSizePolicy(sizePolicy);
    eveningBtn->setLocale(QLocale(QLocale::English, QLocale::World));
    eveningBtn->setFlat(false);

    QFont font{ "Monospace" };
    font.setStretch(QFont::Expanded);
    font.setLetterSpacing(QFont::AbsoluteSpacing, 5);
    font.setPixelSize(eveningBtn->size().height() / 2);
    qDebug() << eveningBtn->size().height() << font;
    eveningBtn->setFont(font);

    gridLayout->addWidget(eveningBtn, 5, 0, 1, 3);

    afternoonBtn = new QPushButton(gridLayoutWidget);
    afternoonBtn->setObjectName(QString::fromUtf8("afternoonBtn"));
    sizePolicy.setHeightForWidth(afternoonBtn->sizePolicy().hasHeightForWidth());
    afternoonBtn->setSizePolicy(sizePolicy);
    afternoonBtn->setLocale(QLocale(QLocale::English, QLocale::World));
    afternoonBtn->setFlat(false);

    font.setPixelSize(afternoonBtn->size().height() / 2);
    afternoonBtn->setFont(font);

    gridLayout->addWidget(afternoonBtn, 4, 0, 1, 3);

    morningBtn = new QPushButton(gridLayoutWidget);
    morningBtn->setObjectName(QString::fromUtf8("morningBtn"));
    sizePolicy.setHeightForWidth(morningBtn->sizePolicy().hasHeightForWidth());
    morningBtn->setSizePolicy(sizePolicy);
    morningBtn->setLocale(QLocale(QLocale::English, QLocale::World));
    morningBtn->setFlat(false);
    morningBtn->setDefault(false);

    font.setPixelSize(morningBtn->size().height() / 2);
    morningBtn->setFont(font);

    gridLayout->addWidget(morningBtn, 3, 0, 1, 3);

    languageBox = new QComboBox(gridLayoutWidget);
    languageBox->setObjectName(QString::fromUtf8("languageBox"));
    QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy2.setHeightForWidth(languageBox->sizePolicy().hasHeightForWidth());
    languageBox->setSizePolicy(sizePolicy2);
    languageBox->setMinimumSize(QSize(47, 27));
    languageBox->setLocale(QLocale(QLocale::English, QLocale::World));
    languageBox->setEditable(false);
    languageBox->setMaxVisibleItems(2);
    languageBox->setMaxCount(2);
    languageBox->setInsertPolicy(QComboBox::NoInsert);
    languageBox->setTabletTracking(false);

    font.setPixelSize(languageBox->size().height() / 2 - 1);
    font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
    qDebug() << font;
    languageBox->setFont(font);

    gridLayout->addWidget(languageBox, 2, 2, 1, 1);

    gridLayout->setRowStretch(1, 1);
    gridLayout->setRowStretch(2, 1);
    gridLayout->setRowStretch(3, 3);
    gridLayout->setRowStretch(4, 3);
    gridLayout->setRowStretch(5, 3);
    gridLayout->setRowStretch(6, 1);
    gridLayout->setColumnStretch(1, 5);
    gridLayout->setColumnStretch(2, 1);
    QWidget::setTabOrder(morningBtn, afternoonBtn);
    QWidget::setTabOrder(afternoonBtn, eveningBtn);
    QWidget::setTabOrder(eveningBtn, morningBtn);

    retranslateUi(PeriodMap);

    QMetaObject::connectSlotsByName(PeriodMap);

    PeriodMap->resize(230, 380);
} // setupUi

void Ui_PeriodMap::retranslateUi(QWidget* PeriodMap)
{
    eveningBtn->setText(QApplication::translate("PeriodMap", "evening", nullptr));
    afternoonBtn->setText(QApplication::translate("PeriodMap", "afternoon", nullptr));
    morningBtn->setText(QApplication::translate("PeriodMap", "morning", nullptr));
    languageBox->setCurrentText(QString());
    Q_UNUSED(PeriodMap);
} // retranslateUi
