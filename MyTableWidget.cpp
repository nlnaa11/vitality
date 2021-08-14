class MyTableWidget;

#include <QDebug>
#include <QWidget>
#include <QMouseEvent>
#include "MyTableWidget.h"

MyTableWidget::MyTableWidget(QWidget* parent)
    : QTableWidget(parent)
{
}

void MyTableWidget::mousePressEvent(QMouseEvent* event)
{
    time = QTime().currentTime();
    pos = event->pos();
}

void MyTableWidget::mouseReleaseEvent(QMouseEvent* event)
{
    QTime t = QTime().currentTime();
    int interval = t.msecsTo(time);

    if (pos == event->pos())
    {
        QTableWidgetItem* item = itemAt(pos);

        if(item)
        {
            if(abs(interval) < 700)
                emit itemClicked(item);
            else
                emit itemPressed(item);
        }
    }
}

void MyTableWidget::setSelected(int row, bool select)
{
    if(select)
        selectedRows.insert(row);
    else
    {
        auto pos = selectedRows.find(row);
        if(pos != selectedRows.end())
            selectedRows.erase(pos);
    }
    qDebug() << selectedRows.size() << "selectedRows size";

} // setSelected

bool MyTableWidget::isSelected(int row) const
{
    auto pos = selectedRows.find(row);

    return (pos == selectedRows.end()) ? false : true;
} // isSelected

QVector<int> MyTableWidget::selectedItems() const
{
    if(selectedRows.empty())
        return QVector<int>();

    std::vector<int> items{ selectedRows.begin(), selectedRows.end() };
    return QVector<int>::fromStdVector(items);
} // selectedItems

void MyTableWidget::setAllSelected(int maxRow)
{
    for(int row = maxRow; row > -1; --row)
        selectedRows.insert(row);
} // setAllSelected

void MyTableWidget::resetSelection()
{
    selectedRows.clear();
} // resetSelection

