#pragma once
/*
* 智能报表窗口: 顶部窗口和报表窗口
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
#include "ZTableWgt.h"
#include "HDataStruct.h"
//#ifdef _DEBUG
//#include "ZCustomTabWgt.h"
//#endif // _DEBUG

#define INI_TOP_HEIGHT 50
#define INT_BUTTON_WIDTH 50
#define INT_BUTTON_HEIGHT 30

class HIntelligentReportWgt : public QWidget
{
    Q_OBJECT

public:
    HIntelligentReportWgt(QWidget* parent = Q_NULLPTR, stTableData stTable = {});
    HIntelligentReportWgt(QWidget* parent = Q_NULLPTR, QRect rect = QRect(0,0,0,0),int nrow = 0, int ncolumn = 0);
    ~HIntelligentReportWgt();

    //void mousePressEvent(QMouseEvent* event);
    //void mouseMoveEvent(QMouseEvent* event);
    //void mouseReleaseEvent(QMouseEvent* event);
    //void wheelEvent(QWheelEvent* event);        // 用鼠标滚轮事件实现图像放大缩小
private:
    void initUI();
    void initTopWgt();
    void initReportWgt();

signals:
    void sigDayTableShow();
    void sigMonthTableShow();
	void sigSeasonTableShow();
    void sigYearTableShow();
    

public slots:
    void slotDayBtnClicked();
    void slotMonthBtnClicked();
    void slotSeasonBtnClicked();
    void slotYearBtnClicked();
    void slotMoreBtnClicked();


private:
    QWidget* m_pTopWgt;//顶部窗口
    QLabel* m_plbTitle;
    QLabel* m_plbSysTime;
    QPushButton* m_pbtnDay;
    QPushButton* m_pbtnMonth;
    QPushButton* m_pbtnYear;
    QPushButton* m_pbtnSeason;

    QPushButton* m_pbtnMore;
    QWidget* m_pReportWgt;//报表窗口
   

   // QTableWidget* m_pTabWgt;

    HCustomTabWgt* m_pCustomTabWgt;//用户自定义报表
    ZTableWgt* m_pTabWgt;//报表窗口


    int  m_nRowTab;
    int  m_nColumnTab;
    QRect    m_rectReport;//窗口初始位置、大小
    stTableData m_stTableDataInfo;//表数据

    //鼠标拖动窗体移动
    bool        m_bDrag;
    QPoint      mouseStartPoint;
    QPoint      windowTopLeftPoint;
};