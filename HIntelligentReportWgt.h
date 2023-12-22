#pragma once
/*
* ���ܱ�������: �������ںͱ�������
* 
*/

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QTableWidget>
#include <QRect>

#include "HCustomTabWgt.h"

#define INI_TOP_HEIGHT 50
#define INT_BUTTON_WIDTH 50
#define INT_BUTTON_HEIGHT 30

class HIntelligentReportWgt : public QWidget
{
    Q_OBJECT

public:
    HIntelligentReportWgt(QWidget* parent = Q_NULLPTR, QRect rect = QRect(0,0,0,0),int nrow = 0, int ncolumn = 0);
    ~HIntelligentReportWgt();

    //void mousePressEvent(QMouseEvent* event);
    //void mouseMoveEvent(QMouseEvent* event);
    //void mouseReleaseEvent(QMouseEvent* event);
    //void wheelEvent(QWheelEvent* event);        // ���������¼�ʵ��ͼ��Ŵ���С
private:
    void initUI();
    void initTopWgt();
    void initReportWgt();

signals:


public slots:

private:
    QWidget* m_pTopWgt;//��������
    QLabel* m_plbTitle;
    QLabel* m_plbSysTime;
    QPushButton* m_pbtnDay;
    QPushButton* m_pbtnMonth;
    QPushButton* m_pbtnYear;
    QPushButton* m_pbtnMore;

    QWidget* m_pReportWgt;//��������
   

    QTableWidget* m_pTabWgt;

    HCustomTabWgt* m_pCustomTabWgt;//�û��Զ��屨��


    int  m_nRowTab;
    int  m_nColumnTab;
    QRect    m_rectReport;//���ڳ�ʼλ�á���С

    //����϶������ƶ�
    bool        m_bDrag;
    QPoint      mouseStartPoint;
    QPoint      windowTopLeftPoint;
};