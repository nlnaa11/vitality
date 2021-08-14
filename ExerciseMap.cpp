#include <QDebug>
#include <QResizeEvent>
#include <QHeaderView>
#include <QApplication>
#include <QRandomGenerator>
#include "ExerciseMap.h"
#include "ui_ExerciseMap.h"
#include "PeriodMap.h"
#include "EditExerciseMap.h"
#include "ModelForMap.h"

int random(int min, int max)
{
    static const double fraction = 1.0 / 32768.0;
    int rand = QRandomGenerator::global()->bounded(32767);
    int res = static_cast<int>(rand * fraction * (max - min + 1) + min);

    // require a multiplicity of 5 from the result
    return ((res + 4) /  5) * 5;
} // random

ExerciseMap::ExerciseMap(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ExerciseMap)
{
    ui->setupUi(this);

    // initAppStyle
    setupStyle();

    // initModel
    setupModel();

    // initUi
    createUi();

} // ExerciseMap

ExerciseMap::~ExerciseMap()
{
    delete ui;
    delete ui_PeriodMap;
    delete ui_EditExMap;
    delete model;
} // ~ExerciseMap

/** Public methods **/

void ExerciseMap::show_PeriodMap()
{
    //ui_PeriodMap->showMaximized();
    ui_PeriodMap->show();
} // show_PeriodMap

/** Protected methods**/

void ExerciseMap::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::LanguageChange)
        ui->retranslateUi(this);

    QWidget::changeEvent(e);
} // changeEvent

void ExerciseMap::hideEvent(QHideEvent *e)
{
    QTableWidgetItem* item = ui->tableWidget->item(0, 1);

    if(!item || item->text() == "")
        return QWidget::hideEvent(e);

    for(int row = 0; row < ui->tableWidget->rowCount(); ++row)
        ui->tableWidget->item(row, 1)->setText("");

    QWidget::hideEvent(e);
} // hideEvent

void ExerciseMap::resizeEvent(QResizeEvent* e)
{
    int delta = static_cast<int>
                (e->size().width() / this->baseSize().width());
    qDebug() << "delta EM " << delta << " newSize " << e->size();

    QFont font{ "Monospace" };
    font.setStretch(QFont::Expanded);
    font.setPixelSize(15 * delta);	// "15" is a base font
    ui->periodLbl->setFont(font);	// for lbl

    font.setStretch(QFont::Unstretched);
    font.setPixelSize(14 * delta);
    ui->tableWidget->setFont(font);

    ui->tableWidget->horizontalHeader()->
                    setDefaultSectionSize(40 * delta);
    ui->tableWidget->verticalHeader()->
                    setDefaultSectionSize(20 * delta);

    QWidget::resizeEvent(e);
} // resizeEvent

/** Private methods **/

void ExerciseMap::setupModel()
{
    model = new ModelForMap();

    connect(model, &ModelForMap::finishMultiUpdate,
            this, &ExerciseMap::updateUi);
    connect(model, &ModelForMap::finishOneUpdate,
            this, &ExerciseMap::updateUi);
    connect(model, &ModelForMap::startUpdate,
            [=]
            {
                if(this->isVisible())
                    this->setEnabled(false);
            });

} // setupModel

void ExerciseMap::createUi()
{
    ui_PeriodMap = new PeriodMap();
    ui_EditExMap = new EditExerciseMap(model);

    connect(ui->backBtn, &QPushButton::clicked,
            [=]
            {
                ui_PeriodMap->show();
                this->hide();
                //ui_PeriodMap->showMaximized();
            });
    connect(ui->editBtn, &QPushButton::clicked,
            [=]
            {
                ui_EditExMap->show();
                this->hide();
                //ui_EditExMap->showMaximized();
            });

    connect(ui_PeriodMap, &PeriodMap::periodSelected,
            this, &ExerciseMap::periodRecieved);
    connect(ui_EditExMap, &EditExerciseMap::backToMap,
            [=]
            {
                this->show();
                ui_EditExMap->close();
                //this->showMaximized();
            });
} // createUi

void ExerciseMap::setupStyle()
{
    qApp->setStyleSheet("* {"
                            "background-color: black;"
                            "selection-color: rgb(46, 52, 54);"
                            "color: rgb(255, 255, 255);"
                        "}");
} // setupStyle

/** Private slots **/

void ExerciseMap::periodRecieved(const QString& period)
{
    // updateModel
    if(model->tableName() != period)
        model->setupModel(period);

    ui_PeriodMap->close();

    if(model->rowCount(false))
        //this->showMaximized();
        this->show();
    else
        //ui_EditExMap->showMaximized();
        ui_EditExMap->show();
} // periodRecieved

/* connected to the model update signal */
void ExerciseMap::updateUi()
{
    ui->periodLbl->setText(model->tableName());

    int count{ ui->tableWidget->rowCount() };

    if(count)
        for(int row = --count; row > -1; --row)
            ui->tableWidget->removeRow(row);

    for(int row = 0; row < model->rowCount(false); ++row)
    {
        ui->tableWidget->insertRow(row);

        QTableWidgetItem* nameItem{ new QTableWidgetItem(model->data(row), Qt::DisplayRole) };
        QTableWidgetItem* resItem{ new QTableWidgetItem(Qt::DisplayRole) };
        Qt::ItemFlags flags{ ~Qt::ItemIsEnabled };

        nameItem->setFlags(flags);
        resItem->setFlags(flags);

        ui->tableWidget->setItem(row, 0, nameItem);
        ui->tableWidget->setItem(row, 1, resItem);

        ui->tableWidget->item(row, 1)->setTextAlignment(Qt::AlignCenter);
    }    
    this->setEnabled(true);
} // updateUi

void ExerciseMap::on_runBtn_clicked()
{
    this->setEnabled(false);

    QVector<int> data = model->dataForRandom();
    int row{0};

    for(int i = 0; i < data.size() - 1; i += 2)
    {
        int result = random(data[i], data[i + 1]);
        QString str = QString::number(result);

        ui->tableWidget->item(row, 1)->setText(str);

        ++row;
    }
    this->setEnabled(true);
} // on_runBtn_clicked
