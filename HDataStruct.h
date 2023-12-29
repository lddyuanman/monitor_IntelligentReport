#pragma once
#include<QPoint>
//定义结构体


typedef struct stTableData
{
	QPoint          begin;     //窗口开始位置
	QPoint          end;
	int             nrow;     //表行数
	int             ncolumn;  //表列数
	QString         strFirstRowContent;    //表第一行内容，即设备名称
	QStringList     strlstSecondRowContent;//表第二行内容
	QStringList     strlstFirstColContent;//表第一列内容

	stTableData()
	{
		begin = QPoint(0, 0);
		end = QPoint(0, 0);
		nrow = 0;
		ncolumn = 0;
		strFirstRowContent = "";
		
	}
}TABLE_STRUCT;


