#pragma once
/*
* 智能报表窗口: 顶部窗口和报表窗口
* 只处理窗口之间的交互，不处理数据
*/
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QTableWidget>
#include <QRect>
#include <QMenu>
#include <QMap>
#include "HCustomTabWgt.h"
#include "ZTableWgt.h"
#include "DataStruct.h"
#include "ZSetDateWgt.h"
#include "ZExportReportWgt.h"
#include "GlobalVariable.h"
//#ifdef _DEBUG
//#include "ZCustomTabWgt.h"
//#endif // _DEBUG

#define INI_TOP_HEIGHT 50
#define INT_BUTTON_WIDTH 50
#define INT_BUTTON_HEIGHT 30

class ZIntelligentReportWgt : public QWidget
{
    Q_OBJECT

public:
    ZIntelligentReportWgt(QWidget* parent = Q_NULLPTR, stTableData stTable = {});
    ZIntelligentReportWgt(QWidget* parent = Q_NULLPTR, QRect rect = QRect(0,0,0,0),int nrow = 0, int ncolumn = 0);
    ~ZIntelligentReportWgt();

    //void mousePressEvent(QMouseEvent* event);
    //void mouseMoveEvent(QMouseEvent* event);
    //void mouseReleaseEvent(QMouseEvent* event);
    //void wheelEvent(QWheelEvent* event);        // 用鼠标滚轮事件实现图像放大缩小
    void getReportPath(QString &strpath);
    void setData(QMap<QString, QStringList> mapdata);
    void setTableData();
private:
    void initUI();
    void initTopWgt();
    void initReportWgt();
    void initMenuWgt();

signals:
    void sigDayTableShow();
    void sigMonthTableShow();
	void sigSeasonTableShow();
    void sigYearTableShow();    

    void sigGetReportData(QMap<QString, QStringList> &mapdata, ReportType type);

public slots:
    void slotShowMenu(QPoint pos);

    void slotDayBtnClicked();
    void slotMonthBtnClicked();
    void slotSeasonBtnClicked();
    void slotYearBtnClicked();
    void slotMoreBtnClicked();

    void slotOpenDirectory();

    void slotGetReportData(QMap<QString, QStringList>& mapdata, ReportType type);
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

    HCustomTabWgt* m_pCustomTabWgt;//用户自定义报表
    ZTableWgt* m_pTabWgt;//报表窗口

    QMenu* m_pMenu;//右键菜单
    ZSetDateWgt* m_pSetDateWgt;//设置日期窗口
    ZExportReportWgt* m_pExportWgt;//导出报表窗口

    int  m_nRowTab;
    int  m_nColumnTab;
    QRect    m_rectReport;//窗口初始位置、大小
    stTableData m_stTableDataInfo;//表数据
    ReportType m_nTabType;//报表类型

    //鼠标拖动窗体移动
    bool        m_bDrag;
    QPoint      mouseStartPoint;
    QPoint      windowTopLeftPoint;
};