#pragma once
/*
* ����excel��񵼳����ܽӿ�
*/
#include<QObject>
#include<ActiveQt/QAxObject>

class ExcelExport
{
	Q_OBJECT

public:
	ExcelExport();
	~ExcelExport();

	bool addWorkbook();
	void startExport();
	void endExport();
private:
	QAxObject* m_pExcel;
	QAxObject*  m_pWorkbook;
	QString m_strSavePath;
signals:


public slots:

};
