#pragma once
#include<QPoint>
//����ṹ��


typedef struct stTableData
{
	QPoint          begin;     //���ڿ�ʼλ��
	QPoint          end;
	int             nrow;     //������
	int             ncolumn;  //������
	QString         strFirstRowContent;    //���һ�����ݣ����豸����
	QStringList     strlstSecondRowContent;//��ڶ�������
	QStringList     strlstFirstColContent;//���һ������

	stTableData()
	{
		begin = QPoint(0, 0);
		end = QPoint(0, 0);
		nrow = 0;
		ncolumn = 0;
		strFirstRowContent = "";
		
	}
}TABLE_STRUCT;


