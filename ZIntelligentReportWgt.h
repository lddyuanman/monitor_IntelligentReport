#pragma once
/*
* ���ܱ�����: �������ںͱ�����
* ֻ������֮��Ľ���������������
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
    //void wheelEvent(QWheelEvent* event);        // ���������¼�ʵ��ͼ��Ŵ���С
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
    QWidget* m_pTopWgt;//��������
    QLabel* m_plbTitle;
    QLabel* m_plbSysTime;
    QPushButton* m_pbtnDay;
    QPushButton* m_pbtnMonth;
    QPushButton* m_pbtnYear;
    QPushButton* m_pbtnSeason;

    QPushButton* m_pbtnMore;
    QWidget* m_pReportWgt;//������   

    HCustomTabWgt* m_pCustomTabWgt;//�û��Զ��屨��
    ZTableWgt* m_pTabWgt;//������

    QMenu* m_pMenu;//�Ҽ��˵�
    ZSetDateWgt* m_pSetDateWgt;//�������ڴ���
    ZExportReportWgt* m_pExportWgt;//����������

    int  m_nRowTab;
    int  m_nColumnTab;
    QRect    m_rectReport;//���ڳ�ʼλ�á���С
    stTableData m_stTableDataInfo;//������
    ReportType m_nTabType;//��������

    //����϶������ƶ�
    bool        m_bDrag;
    QPoint      mouseStartPoint;
    QPoint      windowTopLeftPoint;
};