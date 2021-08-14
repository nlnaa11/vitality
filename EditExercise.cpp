#include <QResizeEvent>
#include <QVariant>
#include <QRegularExpression>
#include <QIntValidator>
#include <QRegularExpressionValidator>
#include "EditExercise.h"
#include "ui_EditExercise.h"
#include "ReplaceOrRename.h"
#include "ModelForForm.h"

EditExercise::EditExercise(const QString& period, const QString& exercise,
                           QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::EditExercise)
{
    ui->setupUi(this);
//    this->setAttribute(Qt::WA_DeleteOnClose, true);

    // initModel
    setupModel(period, exercise);

    // initMapper
    createMapper();

    // initValidator
    createValidator();

    // initUi
    connect(ui->backBtn, &QPushButton::clicked,
            [=]
            {
                emit noChanges();
            });

    ui->exerciseEdit->setFocus();
} // EditExercise

EditExercise::~EditExercise()
{
    delete ui;
    delete model;
    // dialog is deleted when it is closed
} // ~EditExercise

void EditExercise::resizeEvent(QResizeEvent* e)
{
    int delta = static_cast<int>
                (e->size().width() / this->baseSize().width());

    QFont font{ "Monospace" };
    font.setStretch(QFont::Expanded);
    font.setPixelSize(15 * delta);

    ui->exerciseLbl->setFont(font);
    ui->minLbl->setFont(font);
    ui->maxLbl->setFont(font);
    ui->seconds->setFont(font);
    ui->repeats->setFont(font);

    font.setStretch(QFont::Unstretched);
    font.setPixelSize(14 * delta);

    ui->exerciseEdit->setFont(font);
    ui->minEdit->setFont(font);
    ui->maxEdit->setFont(font);

    int width = 15 * delta;
    QString style{ "QCheckBox::indicator {"
                              "width: %1;"
                              "height: %2 }" };

    ui->seconds->setStyleSheet(style.arg(width).arg(width));
    ui->repeats->setStyleSheet(ui->seconds->styleSheet());


    QDialog::resizeEvent(e);
} // resizeEvent

void EditExercise::setupModel(const QString& period, const QString& exercise)
{
    model = new ModelForForm(this);
    model->setTable(period);

    if(exercise != "")
        model->selectRow(exercise);
} // setupModel

void EditExercise::createMapper()
{
    QVariantList data = model->data();

    if(!data.isEmpty())
    {
        ui->exerciseEdit->setText(data[0].toString());
        ui->minEdit->setText(data[1].toString());
        ui->maxEdit->setText(data[2].toString());
        if(data[3].toBool())
            ui->seconds->setCheckState(Qt::Checked);
        else
            ui->seconds->setCheckState(Qt::Unchecked);
    }
} // createMapper

void EditExercise::createValidator()
{
    QString exerRange = "[\\w ]{1,40}|[А-Яа-я0-9_ ]{1,40}";
    QRegularExpression exerRegExp ("^" + exerRange + "$");

    QRegularExpressionValidator* exerValidator = new QRegularExpressionValidator(exerRegExp, this);
    ui->exerciseEdit->setValidator(exerValidator);

    QIntValidator* minMaxValidator = new QIntValidator(0, 999, this);
    ui->minEdit->setValidator(minMaxValidator);
    ui->maxEdit->setValidator(minMaxValidator);
} // createValidator

void EditExercise::processDuplicate()
{
    if(!dialog)
    {
        dialog = new ReplaceOrRename();

        connect(dialog->replaceBtn, &QPushButton::clicked,
            [=]
            {
                // this->showMaximized();
                this->setStyleSheet("background: black;"
                                    "color: white");
                this->show();
                dialog->close(); // Qt::WA_DeleteOnClose = true
                dialog = nullptr;

                replace();
            });
        connect(dialog->renameBtn, &QPushButton::clicked,
            [=]
            {
                // this->showMaximized();
                this->setStyleSheet("background: black;"
                                    "color: white");
                this->show();
                dialog->close();
                dialog = nullptr;

                this->setEnabled(true);
                ui->exerciseEdit->setFocus();
            });
    }

//    this->hide();
    this->setStyleSheet("background: rgb(32, 32, 32);"
                        "color: rgb(45, 45, 45)");
    dialog->show();
} // processDuplicate

void EditExercise::on_okBtn_clicked()
{
    this->setEnabled(false);

    QString exercise = ui->exerciseEdit->text();
    int min = ui->minEdit->text().toInt();
    int max = ui->maxEdit->text().toInt();
    bool second = ui->seconds->isChecked();

    bool duplicate = model->isDuplicate(exercise);

    if(!duplicate)
    {
        model->insertRow(exercise, min, max, second);
        emit newItemInserted(exercise);
        return;
    }
    else
        processDuplicate();
} // on_okBtn_clicked

void EditExercise::replace()
{
    QString exercise = ui->exerciseEdit->text();
    int min = ui->minEdit->text().toInt();
    int max = ui->maxEdit->text().toInt();
    bool second = ui->seconds->isChecked();

    model->removeRow(exercise);
    model->insertRow(exercise, min, max, second);
    emit itemEdited(exercise);
} // replace
