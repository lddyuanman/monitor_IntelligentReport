#pragma once
/*
* �����񲿷�,һ��QTableWidget���
* ע�⣺���� = ��ʾ����list + INT_HEAD_ROW_COUNT��INT_HEAD_ROW_COUNTΪ��ͷ����
*       ���� = ��ʾ����list + 1��1Ϊ����
*/
#include <QTableWidget>
#include <QStyledItemDelegate>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QMap>
#include "DataStruct.h"
#include "GlobalVariable.h"
#include "ExcelExport.h"

#define INT_FIRST_COLUMN_WIDTH 100//��ͷ�ͱ��������п��
#define INT_HEAD_ROW_HEIGHT 30//��ͷ���к͵ڶ��и߶�
#define INT_HEAD_ROW_COUNT  2//�Զ����ͷ����
#define INT_HEAD_COLUMN_COUNT  1//�Զ����ͷ����

#define INT_DAY_TIME  24//�ձ�ʱ��
#define INT_MONTH_TIME  31//�±�ʱ��
#define INT_YEAR_TIME  12//�걨ʱ��
#define INT_SEASON_TIME  4//�걨ʱ��

class ZTableWgt : public QTableWidget
{
	Q_OBJECT

public:
	ZTableWgt(QWidget* parent = Q_NULLPTR, int nrow = 0, int ncolumn = 0, QString str = "");
	ZTableWgt(QWidget* parent = Q_NULLPTR, stTableData stTabInfo = {});
	~ZTableWgt();

	void mousePressEvent(QMouseEvent* event);

	void setReportFullPath(QString str);//���ñ���ȫ·��
	void setTabData(QMap<QString, QStringList>  mapData);//��ֵ
	void updateData();//�洢ֵ�ĸ�ʽ��ζ��壿����
					  //��������±����걨���洢��ʽ�᲻���map����vector���ǽṹ��
private:
	void initFrame();

	void setCurrentColumn(int ncolumn);//������
	void setCurrentRow(int nrow);//������
	void setFirstColumnContent(QStringList strLst);//������������
	void resetFirstColumnContent(QStringList strLst);//��������
	void setFirstRowContent(QString str);//���ñ���������ݣ����豸����
	void setSecondRowContent(QStringList strlst);//���ñ��ڶ�����ʾ����
	void InitTabHeader(QString str);//���ñ�ͷ	

	void deleteRow(int nindex);//ɾ��ĳ��
	void deleteAllRows();
	void addRow(int nindex);//����ĳ��
	void addRows(int nrows);

	void saveReport();//���汨��
	void openReport();//�򿪱���

public slots:
	void slotDayTableShow();
	void slotMonthTableShow();
	void slotSeasonTableShow();
	void slotYearTableShow();

	void SlotMenuClicked(QAction* act);
	//void tableContexMenuRequested(QPoint& pos);
	//void on_tableViewCustomContextMenuRequested(const QPoint& pos);

	void sltOpenReport();
signals:
	void sigTableData(QMap<QString, QStringList> &mapData, ReportType type);
private:
	QMenu* m_pContextMenu;
	QAction* m_pActionDel;


	int m_nTabRow;
	int m_nTabColumn;
	QString m_strFirstRowContent;//�������ݣ����豸����
	QStringList m_strlstSecRowCon;//�ڶ�������
	QStringList m_strlstFirColCon;//��������
	QMap<QString, QStringList> m_mapData;//�洢������ݣ�keyΪң��㣬TΪ��Ӧ�ĸ���ʱ����ֵ,��һ��ң����Ӧһ��ֵ

	stTableData m_stTableInfo;//�����Ϣ
	ReportType m_nReportType; //��������
	QString m_strReportFullPath;//����ȫ·��

	ExcelExport* m_pExcelExport;//excel�ļ�����
};


//��ɱ�����ʽ�ػ棬��paint�����У�����ÿ����Ԫ��ı�����ͬ���л��Ʊ���
class ZItemDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	ZItemDelegate(int type, QObject* parent = 0);

	void paint(QPainter* painter,
		const QStyleOptionViewItem& option, const QModelIndex& index) const;
	void OldPaint(QPainter* painter,
		const QStyleOptionViewItem& option, const QModelIndex& index) const;
private:
	int     m_type;//type=0: header    type=1��content
};