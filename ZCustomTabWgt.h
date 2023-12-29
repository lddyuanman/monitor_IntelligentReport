#pragma once
#include <QtWidgets/QWidget>
#include <QTableWidget>
#include <QStyledItemDelegate>
#include<QRect>


class ZCustomTabWgt : public QTableWidget
{
    Q_OBJECT

public:
    ZCustomTabWgt(QWidget* parent = Q_NULLPTR, QRect rect = QRect(0,0,0,0), int nRow = 0,int nColumn = 0);//报表参数过多，可考虑枚举
    ~ZCustomTabWgt();

    void initUI();



private:
    QTableWidget* m_pTableWgt;

    int  m_nRow;
    int  m_nColumn;
    QRect m_rectTab;
};
