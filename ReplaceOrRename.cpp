#include "ReplaceOrRename.h"
#include <QGridLayout>
#include <QResizeEvent>

ReplaceOrRename::ReplaceOrRename(QWidget *parent)
    : QDialog(parent)
{
    setUpUi();
    this->setAttribute(Qt::WA_DeleteOnClose, true);
} // ReplaceOrRename

ReplaceOrRename::~ReplaceOrRename()
{
    delete text;
    delete renameBtn;
    delete replaceBtn;
} // ~ReplaceOrRename

/** Protected methods **/

void ReplaceOrRename::resizeEvent(QResizeEvent* e)
{
    int delta = static_cast<int>
                (e->size().width() / this->baseSize().width());

    QFont font{ "Monospace" };
    font.setStretch(QFont::Expanded);
    font.setPixelSize(15 * delta);	// "15" is a base font
    renameBtn->setFont(font);    	// for btn
    replaceBtn->setFont(font);

    font.setStretch(QFont::Unstretched);
    font.setPixelSize(15 * delta);
    text->setFont(font);

    QDialog::resizeEvent(e);
} // resizeEvent

/** Private methods **/

void ReplaceOrRename::setUpUi()
{
    Qt::WindowFlags flags = Qt::CustomizeWindowHint;
    this->setWindowFlags(flags);
    this->setBaseSize(200, 150);

    text = new QTextEdit();
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHeightForWidth(text->sizePolicy().hasHeightForWidth());
    text->setSizePolicy(sizePolicy);
    text->setFrameStyle(QFrame::NoFrame);
    text->setFrameShadow(QFrame::Plain);
    text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    text->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    text->setReadOnly(true);
    text->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    text->setText(tr("An exercise with this name already exists. "
                          "Do you want to replace it?"));

    renameBtn = new QPushButton(tr("rename"));
    sizePolicy.setHeightForWidth(renameBtn->sizePolicy().hasHeightForWidth());
    renameBtn->setSizePolicy(sizePolicy);
    renameBtn->setFlat(true);

    replaceBtn = new QPushButton(tr("replace"));
    sizePolicy.setHeightForWidth(replaceBtn->sizePolicy().hasHeightForWidth());
    replaceBtn->setSizePolicy(sizePolicy);
    replaceBtn->setFlat(true);
    replaceBtn->setDefault(true);

    QFont font{ "Monospace" };
    font.setStretch(QFont::Expanded);
    font.setPixelSize(15);
    renameBtn->setFont(font);
    replaceBtn->setFont(font);

    font.setStretch(QFont::Unstretched);
    font.setPixelSize(15);
    text->setFont(font);

    QGridLayout* layout = new QGridLayout();
    layout->addWidget(text, 1, 0, 2, 2);
    layout->addWidget(renameBtn, 3, 0, 1, 1);
    layout->addWidget(replaceBtn, 3, 1, 1, 1);
    layout->setContentsMargins(10, 10, 10, 5);

    setLayout(layout);

    QWidget::setTabOrder(replaceBtn, renameBtn);

    this->resize(200, 150);
} // setUpUi

/** Private slots **/
/*
void ReplaceOrRename::on_replaceBtn_clicked()
{
    emit replace();
} // on_replaceBtn_clicked

void ReplaceOrRename::on_renameBtn_clicked()
{
    emit rename();
} // on_renameBtn_clicked

*/
