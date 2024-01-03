#pragma once
/*
* 基于QWidget的类声明
*/
#include <QtWidgets/QWidget>
#include <QPushButton>
#include <QDateTimeEdit>
#include <QCalendarWidget>
#include <QMouseEvent>

#define INI_SETDATEWGT_HEIGHT 400
#define INI_SETDATEWGT_WIDTH 400
#define INI_SETDATEWGT_TITLE_HEIGHT 40
#define INI_SETDATEWGT_DATE_HEIGHT 195
#define INI_SETDATEWGT_INFO_HEIGHT 150
#define INI_SETDATEWGT_LINEEDIT_HEIGHT 40
#define INI_SETDATEWGT_BTN_HEIGHT 30
#define INI_SETDATEWGT_BTN_WIDTH 100

class ZSetDateWgt : public QWidget
{
	Q_OBJECT

public:
	ZSetDateWgt(QWidget* parent = Q_NULLPTR);
	~ZSetDateWgt();
	void mousePressEvent(QMouseEvent* event);

	void  initUI();	
	void initCalendarWgt();

private:
	QPushButton* m_pBtnClose;
	QDateTimeEdit* m_pDateTimeEdit;
	QPushButton* m_pBtnDateTime;
	QCalendarWidget* m_pCalendarWgt;
signals:


public slots:
	void slotShowSetDateWgt();

	void sloCloseBtnClicked();
	void slotDateBtnClicked();

	void slotLastYearBtnClicked();
	void slotNextYearBtnClicked();
	void slotHalfYearBtnClicked();

	void slotLastMonthBtnClicked();
	void slotNextMonthBtnClicked();
	void slotHalfMonthBtnClicked();

	void slotLastDayBtnClicked();
	void slotNextDayBtnClicked();
	void slotTodayBtnClicked();

	void slotCancelBtnClicked();
	void slotUseBtnClicked();
	void slotSureBtnClicked();
};
