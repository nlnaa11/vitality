#include <QEvent>
#include <QDebug>
#include <QHeaderView>
#include <QResizeEvent>
#include <QTableWidgetItem>
#include "EditExerciseMap.h"
#include "ui_EditExerciseMap.h"
#include "EditExercise.h"

EditExerciseMap::EditExerciseMap(ModelForMap* model, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::EditExerciseMap)
//    , model(model)
{    
    ui->setupUi(this);

    // initModel
    setupModel(model);

    // initUi == initSortUi
    createSortUi();

} // EditExerciseMap

EditExerciseMap::~EditExerciseMap()
{
    delete ui;
} // ~EditExerciseMap

/** Public methods **/

/** Protected methods **/

void EditExerciseMap::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::LanguageChange)
        ui->retranslateUi(this);

    QDialog::changeEvent(e);
} // changeEvent

void EditExerciseMap::resizeEvent(QResizeEvent* e)
{
    int delta = static_cast<int>
                (e->size().width() / this->baseSize().width());
    qDebug() << "delta EM " << delta << " newSize " << e->size();

    QFont font{ "Monospace" };
    font.setStretch(QFont::Expanded);
    font.setPixelSize(15 * delta);
    ui->periodLbl->setFont(font);

    font.setStretch(QFont::Unstretched);
    font.setPixelSize(14 * delta);
    ui->tableWidget->setFont(font);

    ui->tableWidget->horizontalHeader()->
                    setDefaultSectionSize(40 * delta);
    ui->tableWidget->verticalHeader()->
                    setDefaultSectionSize(20 * delta);

    int width = 20 * delta;
    QString style{ "QCheckBox::indicator {"
                              "width: %1;"
                              "height: %2 }" };

    ui->tableWidget->setStyleSheet(style.arg(width).arg(width));

    QWidget::resizeEvent(e);
} // resizeEvent

/** Private methods **/

void EditExerciseMap::setupModel(ModelForMap* model)
{
    this->model = model;

    connect(model, &ModelForMap::finishMultiUpdate,
            this, &EditExerciseMap::updateUi);
    connect(model, &ModelForMap::finishOneUpdate,
            this, &EditExerciseMap::updateOne);
    connect(model, &ModelForMap::startUpdate,
            [=]
            {
                if(this->isVisible())
                    this->setEnabled(false);
            });
} // setupModel

void EditExerciseMap::createSortUi()
{
    this->setEnabled(false);

    // tableWidget
    ui->tableWidget->hideColumn(1);

    connect(ui->tableWidget, &MyTableWidget::itemClicked,
            [=](QTableWidgetItem* item)
            {
                if(!ignoreSignal)
                {
                    ui->tableWidget->setCurrentItem(item);
                    editExercise(item->data(Qt::DisplayRole).toString());
                }
            });
    connect(ui->tableWidget, &MyTableWidget::itemPressed,
            [=](QTableWidgetItem* item)
            {
                if(!ignoreSignal)
                {
                    int row = item->row();
                    createFilterUi(row);
                }
            });

    // periodLabel
    ui->periodLbl->setText(tr(model->tableName().toUtf8()));

    // backBtn & newBtn
    connect(ui->newBtn, &QPushButton::clicked,
            [=]
            {
                editExercise("");
            });
    connect(ui->backBtn, &QPushButton::clicked,
            [=]
            {
                emit backToMap();
            });

    this->setEnabled(true);
} // createSortUi

void EditExerciseMap::createFilterUi(int row)
{
    this->setEnabled(false);

    // tableWidget

    ignoreSignal = true;
    ui->tableWidget->showColumn(1);

    QTableWidgetItem* itemSelected = ui->tableWidget->takeItem(row, 1);
    itemSelected->setCheckState(Qt::Checked);
    ui->tableWidget->setSelected(row, true);
    ui->tableWidget->setItem(row, 1, itemSelected);
    qDebug() << ui->tableWidget->selectedItems().count();

    ui->tableWidget->setStyleSheet("QTableWidget::indicator {"
                                              "width: 20px;"
                                              "height: 20px }");


    connect(ui->tableWidget, &MyTableWidget::itemClicked,
            this, &EditExerciseMap::rowSelected);

    // deselectBtn & selectedLbl

    ui->periodLbl->hide();

    // click on deselectBtn -> return to sortUi
    ui->deselectBtn = new QPushButton();
    QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    sizePolicy1.setHeightForWidth(ui->deselectBtn->sizePolicy().hasHeightForWidth());
    ui->deselectBtn->setSizePolicy(sizePolicy1);
    ui->deselectBtn->setIcon(QIcon(":/images/deselect.png"));
    ui->deselectBtn->setIconSize(QSize(48, 48));
    ui->deselectBtn->setFlat(true);
    ui->centralLayout->addWidget(ui->deselectBtn, 0, 0, 1, 1);

    ui->selectedLbl = new QLabel();
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHeightForWidth(ui->selectedLbl->sizePolicy().hasHeightForWidth());
    ui->selectedLbl->setSizePolicy(sizePolicy);
    ui->selectedLbl->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    ui->selectedLbl->setText(tr("1 item selected"));
    ui->centralLayout->addWidget(ui->selectedLbl, 0, 1, 1, 2);

    QFont font{ "Monospace" };
    font.setStretch(QFont::Unstretched);
    font.setPixelSize(ui->tableWidget->font().pixelSize());
    ui->selectedLbl->setFont(font);

    connect(ui->deselectBtn, &QPushButton::clicked,
            this, &EditExerciseMap::deselectBtn_clicked);

    // hideBtn & deleteBtn & allBtn

    ui->backBtn->hide();
    ui->newBtn->hide();

    ui->hideBtn = new QPushButton();
    sizePolicy1.setHeightForWidth(ui->hideBtn->sizePolicy().hasHeightForWidth());
    ui->hideBtn->setSizePolicy(sizePolicy1);
    ui->hideBtn->setIcon(QIcon(":/images/hide.png"));
    ui->hideBtn->setIconSize(QSize(48, 48));
    ui->hideBtn->setFlat(true);
    ui->centralLayout->addWidget(ui->hideBtn, 7, 0, 1, 1);

    ui->deleteBtn = new QPushButton();
    sizePolicy1.setHeightForWidth(ui->deleteBtn->sizePolicy().hasHeightForWidth());
    ui->deleteBtn->setSizePolicy(sizePolicy1);
    ui->deleteBtn->setIcon(QIcon(":/images/delete.png"));
    ui->deleteBtn->setIconSize(QSize(48, 48));
    ui->deleteBtn->setFlat(true);
    ui->centralLayout->addWidget(ui->deleteBtn, 7, 1, 1, 1);

    ui->allBtn = new QPushButton();
    sizePolicy1.setHeightForWidth(ui->allBtn->sizePolicy().hasHeightForWidth());
    ui->allBtn->setSizePolicy(sizePolicy1);
    ui->allBtn->setIcon(QIcon(":/images/all.png"));
    ui->allBtn->setIconSize(QSize(48, 48));
    ui->allBtn->setFlat(true);
    ui->centralLayout->addWidget(ui->allBtn, 7, 2, 1, 1);

    connect(ui->hideBtn, &QPushButton::clicked,
            this, &EditExerciseMap::hideBtn_clicked);
    connect(ui->deleteBtn, &QPushButton::clicked,
            this, &EditExerciseMap::deleteBtn_clicked);
    connect(ui->allBtn, &QPushButton::clicked,
            this, &EditExerciseMap::allBtn_clicked);

    this->setEnabled(true);
} // createFilterUi

void EditExerciseMap::setNewRow(int row)
{
    ui->tableWidget->insertRow(row);

    QTableWidgetItem* nameItem{ new QTableWidgetItem(model->data(row), Qt::DisplayRole) };
    QTableWidgetItem* checkItem{ new QTableWidgetItem(Qt::CheckStateRole) };
    Qt::ItemFlags nameFlags{ Qt::ItemIsEnabled & ~Qt::ItemIsEditable };
    Qt::ItemFlags checkFlags{ Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable };

    nameItem->setFlags(nameFlags);
    checkItem->setFlags(checkFlags);

    checkItem->setCheckState(Qt::Unchecked);

    if(row >= model->firstHidden())
        nameItem->setBackground(QBrush(QColor(32, 32, 32)));

    ui->tableWidget->setItem(row, 0, nameItem);
    ui->tableWidget->setItem(row, 1, checkItem);
} // setNewRow

void EditExerciseMap::setNewRowFromOld(int newRow, int oldRow)
{
    qDebug() << "setNewFromOld";
    // data and flags are saved
    QTableWidgetItem* nameItem{ ui->tableWidget->takeItem(oldRow, 0) };
    QTableWidgetItem* checkItem{ ui->tableWidget->takeItem(oldRow, 1) };

    qDebug() << nameItem->data(Qt::DisplayRole).toString();
    qDebug() << checkItem->data(Qt::CheckStateRole).toBool();

    if(newRow < model->firstHidden())
        nameItem->setBackground(QBrush("black"));
    else
        nameItem->setBackground(QBrush(QColor(32, 32, 32)));

    ui->tableWidget->removeRow(oldRow);
    ui->tableWidget->insertRow(newRow);

    ui->tableWidget->setItem(newRow, 0, nameItem);
    ui->tableWidget->setItem(newRow, 1, checkItem);
} // setNewRowFromOld

void EditExerciseMap::editExercise(const QString& exercise)
{
    if(!ui_editEx)
    {
        ui_editEx = new EditExercise(model->tableName(), exercise);

        connect(ui_editEx, &EditExercise::itemEdited,
            this, &EditExerciseMap::itemEdited);
        connect(ui_editEx, &EditExercise::newItemInserted,
            this, &EditExerciseMap::newItemInserted);
        connect(ui_editEx, &EditExercise::noChanges,
            this, &EditExerciseMap::closeEditExercise);
    }

    //ui_editEx->showMaximized();
    ui_editEx->show();
    this->hide();
} // editExercise

/** Private slots **/

void EditExerciseMap::updateUi()
{
    ui->periodLbl->setText(model->tableName());

    int count{ ui->tableWidget->rowCount() };

    if(count)
        for(int row = --count; row > -1; --row)
            ui->tableWidget->removeRow(row);

    for(int row = 0; row < model->rowCount(true); ++row)
        setNewRow(row);

    this->setEnabled(true);
} // updateUi

void EditExerciseMap::updateOne(ModelForMap::ChangeType type, int oldRow)
{
    switch(type)
    {
        case ModelForMap::NewInserted:
            setNewRow(0);
            break;
        case ModelForMap::Edited:
            setNewRowFromOld(0, oldRow);
            break;

        case ModelForMap::Deleted:
            ui->tableWidget->removeRow(oldRow);
            break;

        case ModelForMap::Hidden:
        {
            QString value =
                    ui->tableWidget->item(oldRow, 0)->data(Qt::DisplayRole).toString();

            // if it is hidden now, it means it was openned
            if(model->isHidden(value))
            {
                int newRow = model->rowCount(true);
                setNewRowFromOld(--newRow, oldRow);
            }
            else
                setNewRowFromOld(0, oldRow);

            break;
        }
    }
    this->setEnabled(true);
} // updateOne

void EditExerciseMap::itemEdited(const QString& exercise)
{
    closeEditExercise();

    model->updateModel(ModelForMap::Edited, exercise);
} // itemEdited

void EditExerciseMap::newItemInserted(const QString& exercise)
{
    closeEditExercise();

    model->updateModel(ModelForMap::NewInserted, exercise);
} // newItemInserted

void EditExerciseMap::closeEditExercise()
{
    this->show();
    ui_editEx->close();
    //this->showMaximized();

    delete ui_editEx;
    ui_editEx = nullptr;
} // closeEditExercise

void EditExerciseMap::rowSelected(QTableWidgetItem* it)
{
    this->setEnabled(false);

    int row = it->row();
    QTableWidgetItem* item = ui->tableWidget->takeItem(row, 1);

    // change the state of the checkBox &
    // change the list of selected items

    // in several lines to preserve the style of the marks
    bool state = !item->checkState();
    if(state)
        item->setCheckState(Qt::Checked);
    else
        item->setCheckState(Qt::Unchecked);
    ui->tableWidget->setSelected(row, state);

    ui->tableWidget->setItem(row, 1, item);

    // change the selectedLbl text

    QString str = ui->selectedLbl->text().split(' ').first();
    int num = str.toInt();

    if(state)
    {
        if(num == 0)
            ui->selectedLbl->setText(tr("1 item selected"));
        else
            ui->selectedLbl->setText(QString::number(++num) + tr(" items selected"));
    }
    else
    {
        if(num == 2)
            ui->selectedLbl->setText(tr("1 item selected"));
        else
            ui->selectedLbl->setText(QString::number(--num) + tr(" items selected"));
    }

    this->setEnabled(true);
} // rowSelected

void EditExerciseMap::deselectBtn_clicked()
{
    this->setEnabled(false);

    // disconnect btns

    disconnect(ui->deselectBtn, nullptr, nullptr, nullptr);
    disconnect(ui->hideBtn, nullptr, nullptr, nullptr);
    disconnect(ui->deleteBtn, nullptr, nullptr, nullptr);
    disconnect(ui->allBtn, nullptr, nullptr, nullptr);

    // remove btns & lbls for the filtering mode
    // make btns & lbl visible for the sorting mode

    delete ui->hideBtn;		ui->hideBtn = nullptr;
    delete ui->deleteBtn;	ui->deleteBtn = nullptr;
    delete ui->allBtn;		ui->allBtn = nullptr;

    ui->backBtn->setVisible(true);
    ui->newBtn->setVisible(true);

    delete ui->deselectBtn;	ui->deselectBtn = nullptr;
    delete ui->selectedLbl; ui->selectedLbl = nullptr;

    ui->periodLbl->setVisible(true);

    // reset the checkboxes and the list of selected items

    for(int row = 0; row < ui->tableWidget->rowCount(); ++row)
        ui->tableWidget->item(row, 1)->setCheckState(Qt::Unchecked);

    ui->tableWidget->resetSelection();

    // other resets

    ui->tableWidget->hideColumn(1);

    disconnect(ui->tableWidget, &MyTableWidget::itemClicked,
                this, &EditExerciseMap::rowSelected);

    ignoreSignal = false;

    this->setEnabled(true);
} // on_deselectBtn_clicked

void EditExerciseMap::hideBtn_clicked()
{
    this->setEnabled(false);

    int one = ui->tableWidget->selectedItems().count();
    qDebug() << one << "selected items";

    if(one == 0)
    {
        this->setEnabled(true);
        return; // continue to work in the filtering mode
    }

    else if(one == 1)
    {
        int row = ui->tableWidget->selectedItems().first();
        model->updateModel(ModelForMap::Hidden, "", row);
    }

    else
    {
        auto rowList = ui->tableWidget->selectedItems();
        model->updateModel(ModelForMap::Hidden, rowList);
    }

    // prepare the view to work in the sorting mode
    deselectBtn_clicked();
} // on_hideBtn_clicked

void EditExerciseMap::deleteBtn_clicked()
{
    this->setEnabled(false);

    int one = ui->tableWidget->selectedItems().count();
    qDebug() << one << "selected items";

    if(one == 0)
    {
        this->setEnabled(true);
        return; // continue to work in the filtering mode
    }

    else if(one == 1)
    {
        int row = ui->tableWidget->selectedItems().first();
        model->updateModel(ModelForMap::Deleted, "", row);
    }

    else
    {
        auto rowList = ui->tableWidget->selectedItems();
        model->updateModel(ModelForMap::Deleted, rowList);
    }

    // prepare the view to work in the sorting mode
    deselectBtn_clicked();
} // on_deleteBtn_clicked

void EditExerciseMap::allBtn_clicked()
{
    this->setEnabled(false);

    static bool select{ true };

    select = selectAll(select);

    this->setEnabled(true);
} // on_allBtn_clicked

bool EditExerciseMap::selectAll(bool select)
{
    QString str{ "%1" + tr(" item%2 selected") };
    int rowCount = ui->tableWidget->rowCount();

    if(select)
    {
        for(int row = 0; row < rowCount; ++row)
            ui->tableWidget->item(row, 1)->setCheckState(Qt::Checked);

        ui->tableWidget->setAllSelected(rowCount - 1);
        if(rowCount == 1)
            ui->selectedLbl->setText(str.arg(rowCount).arg(""));
        else
            ui->selectedLbl->setText(str.arg(rowCount).arg("s"));
    }
    else
    {
        for(int row = 0; row < rowCount; ++row)
            ui->tableWidget->item(row, 1)->setCheckState(Qt::Unchecked);

        ui->tableWidget->resetSelection();
        ui->selectedLbl->setText(str.arg(0).arg("s"));
    }

    return !select;
} // selectAll
