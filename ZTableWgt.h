#pragma once
/*
* 处理表格部分
* 注意：行数 = 显示内容list + INT_HEAD_ROW_COUNT，INT_HEAD_ROW_COUNT为表头行数
*       列数 = 显示内容list + 1，1为首列
*/
#include <QTableWidget>
#include <QStyledItemDelegate>
#include "HDataStruct.h"

#define INT_FIRST_COLUMN_WIDTH 100//表头和表内容首列宽度
#define INT_HEAD_ROW_HEIGHT 40//表头首行和第二行高度
#define INT_HEAD_ROW_COUNT  2//表头行数

class ZTableWgt : public QTableWidget
{
	Q_OBJECT

public:
	ZTableWgt(QWidget* parent = Q_NULLPTR, int nrow = 0, int ncolumn = 0, QString str = "");
	ZTableWgt(QWidget* parent = Q_NULLPTR, stTableData stTabInfo = {});
	~ZTableWgt();


private:
	void initFrame();

	void setFirstColumnContent(QStringList strLst);//设置首列内容
	void setFirstRowContent(QString str);//设置表格首行内容，即设备名称
	void setSecondRowContent(QStringList strlst);//设置表格第二行显示内容
	void InitTabHeader(QString str);//设置表头


	void updateData();//存储值的格式如何定义？？，
	                  //如果换成月报，年报，存储格式会不会变map还是vector还是结构体

private:
	int m_nTabRow;
	int m_nTabColumn;
	QString m_strFirstRowContent;//首行内容，即设备名称
	QStringList m_strlstSecRowCon;//第二行内容
	QStringList m_strlstFirColCon;//首列内容

	stTableData m_stTableInfo;//表格信息
};


//完成报表样式重绘，在paint方法中，根据每个单元格的背景不同进行绘制背景
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
	int     m_type;//type=0: header    type=1：content
};