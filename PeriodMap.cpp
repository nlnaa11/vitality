#include "PeriodMap.h"
#include "ui_PeriodMap.h"
#include <QApplication>
#include <QDebug>
#include <QResizeEvent>

PeriodMap::PeriodMap(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::PeriodMap)
{
    ui->setupUi(this);

    ui->languageBox->addItems(QStringList() << "en" << "ru");

    connect(ui->languageBox, &QComboBox::currentTextChanged,
           // static_cast<void (QComboBox::*)(const QString&)>(&QComboBox::currentIndexChanged),
            [=](const QString& currLang)
            {
                bool luck = translator.load(":/translations/Vitality_" + currLang);   // Загружаем перевод
                if(luck)
                    qApp->installTranslator(&translator);   // Устанавливаем перевод в приложение
            });

    // Первоначальная инициализация перевода для окна приложения
    bool luck = translator.load(QString(":/translations/Vitality_") + QString("en"));
    if(luck)
        qApp->installTranslator(&translator);
} // PeriodMap

PeriodMap::~PeriodMap()
{
    delete ui;
} // ~PeriodMap

void PeriodMap::changeEvent(QEvent* e)
{
    if(e->type() == QEvent::LanguageChange)
        ui->retranslateUi(this);

    QDialog::changeEvent(e);
} // changeEvent

void PeriodMap::resizeEvent(QResizeEvent* e)
{
    int delta = static_cast<int>
                (e->size().width() / this->baseSize().width());
    qDebug() << "delta " << delta << " newSize " << e->size();

    QFont font{ "Monospace" };
    font.setStretch(QFont::Expanded);
    font.setLetterSpacing(QFont::AbsoluteSpacing, 5);
    font.setPixelSize(15 * delta);	// "15" is a base font size
    qDebug() << font;				// for btn

    ui->eveningBtn->setFont(font);
    ui->afternoonBtn->setFont(font);
    ui->morningBtn->setFont(font);

    font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
    font.setPixelSize(14 * delta);	// "14" is a base font size
    qDebug() << font;				// for comboBox

    ui->languageBox->setFont(font);

    QDialog::resizeEvent(e);
} // resizeEvent

void PeriodMap::on_morningBtn_clicked()
{
    emit PeriodMap::periodSelected("morning");
} // on_morningBtn_clicke

void PeriodMap::on_afternoonBtn_clicked()
{
    emit PeriodMap::periodSelected("afternoon");
} // on_afternoonBtn_clicked

void PeriodMap::on_eveningBtn_clicked()
{
    emit PeriodMap::periodSelected("evening");
} // on_eveningBtn_clicked
