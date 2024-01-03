#pragma once
#include <QtWidgets/QWidget>
#include<QMouseEvent>
#include "ui_MonitorSys.h"
#include "ZTitleWgt.h"
#include "ZIntelligentReportWgt.h"
#include "HDataStruct.h"

#define INT_NORMAL_HEIGHT     800
#define INT_NORMAL_WIDTH     1500

class MonitorSys : public QWidget
{
    Q_OBJECT

public:
    MonitorSys(QWidget *parent = Q_NULLPTR);
    ~MonitorSys();

    void showEvent(QShowEvent* e);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    QSize getScreenSize();
    void  setDataInfo(stTableData stTabInfo);//从配置文件中获取信息
    

private:
    void initUI();

public slots:
    void slotMin();
    void slotMax(bool bMaxFlag);
    void slotClose();

private:
    Ui::MonitorSysClass ui;

    ZMonSysTitleWgt* m_pTitleWgt;
    ZIntelligentReportWgt* m_pIntelligentReportWgt;

    int m_nScreenWidth;
    int m_nSCreenHeight;
    bool m_bWndMaxFlag;

    stTableData m_stTabInfoFromFile;


    //鼠标拖动窗体移动
    bool        m_bDrag;
    QPoint      mouseStartPoint;
    QPoint      windowTopLeftPoint;
};
