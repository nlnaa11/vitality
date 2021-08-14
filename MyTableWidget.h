#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

class QTableWidget;
class QTime;
class set;

#include <QTableWidget>
#include <QTime>
#include <set>

class MyTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    MyTableWidget(QWidget* parent = nullptr);

    void setSelected(int row, bool select);
    bool isSelected(int row) const;
    QVector<int> selectedItems() const;
    void setAllSelected(int maxRow);
    void resetSelection();

    void mousePressEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;

signals:
    void itemClicked(QTableWidgetItem* item);
    void itemPressed(QTableWidgetItem* item);

private:
    QTime time;
    QPoint pos;
    std::set<int, std::greater<int>> selectedRows;
};

#endif // TABLEWIDGET_H
