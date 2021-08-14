#ifndef REPLACEORRENAME_H
#define REPLACEORRENAME_H

#include <QDialog>
#include <QPushButton>
#include <QTextEdit>

class ReplaceOrRename : public QDialog
{
    Q_OBJECT

public:
    ReplaceOrRename(QWidget* parent = nullptr);
    ~ReplaceOrRename();

    QPushButton* replaceBtn;
    QPushButton* renameBtn;

protected:
    void resizeEvent(QResizeEvent* e) override;

private:
    void setUpUi();

    QTextEdit* text;
};

#endif // REPLACEORRENAME_H
