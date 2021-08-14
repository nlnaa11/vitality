#ifndef PERIODMAP_H
#define PERIODMAP_H

#include <QDialog>
#include <QEvent>
#include <QTranslator>

namespace Ui { class PeriodMap; }

class PeriodMap : public QDialog
{
    Q_OBJECT
    
public:
    explicit PeriodMap(QWidget* parent = nullptr);
    virtual ~PeriodMap();

protected:
    void changeEvent(QEvent* e) override;
    void resizeEvent(QResizeEvent* e) override;

signals:
    void periodSelected(const QString& period);

private slots:
    void on_morningBtn_clicked();
    void on_afternoonBtn_clicked();
    void on_eveningBtn_clicked();

private:
    Ui::PeriodMap* ui;

    QTranslator translator;
};

#endif // PERIODMAP_H
