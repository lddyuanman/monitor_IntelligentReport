#pragma once
/*
* �����񲿷�
* ע�⣺���� = ��ʾ����list + INT_HEAD_ROW_COUNT��INT_HEAD_ROW_COUNTΪ��ͷ����
*       ���� = ��ʾ����list + 1��1Ϊ����
*/
#include <QTableWidget>
#include <QStyledItemDelegate>
#include "HDataStruct.h"

#define INT_FIRST_COLUMN_WIDTH 100//��ͷ�ͱ��������п��
#define INT_HEAD_ROW_HEIGHT 40//��ͷ���к͵ڶ��и߶�
#define INT_HEAD_ROW_COUNT  2//��ͷ����

class ZTableWgt : public QTableWidget
{
	Q_OBJECT

public:
	ZTableWgt(QWidget* parent = Q_NULLPTR, int nrow = 0, int ncolumn = 0, QString str = "");
	ZTableWgt(QWidget* parent = Q_NULLPTR, stTableData stTabInfo = {});
	~ZTableWgt();


private:
	void initFrame();

	void setFirstColumnContent(QStringList strLst);//������������
	void setFirstRowContent(QString str);//���ñ���������ݣ����豸����
	void setSecondRowContent(QStringList strlst);//���ñ��ڶ�����ʾ����
	void InitTabHeader(QString str);//���ñ�ͷ


	void updateData();//�洢ֵ�ĸ�ʽ��ζ��壿����
	                  //��������±����걨���洢��ʽ�᲻���map����vector���ǽṹ��

private:
	int m_nTabRow;
	int m_nTabColumn;
	QString m_strFirstRowContent;//�������ݣ����豸����
	QStringList m_strlstSecRowCon;//�ڶ�������
	QStringList m_strlstFirColCon;//��������

	stTableData m_stTableInfo;//�����Ϣ
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