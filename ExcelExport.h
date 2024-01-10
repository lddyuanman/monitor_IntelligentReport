#pragma once
/*
* ����excel��񵼳����ܽӿ�
*/
#include <QObject>
#include <ActiveQt/QAxObject>
#include <QMap>

class ExcelExport :public QObject
{
	Q_OBJECT

public:
	ExcelExport();
	~ExcelExport();
	
	int changeStringToAscii(QString str);
	int changeStringToInt(QString str);
	QString changeAsciiToString(int n);
	QString getRangeLetter(int nsize);//���ض�Ӧexcel�ж�Ӧ������ĸ


	void setSavePath(QString strpath);	
	bool isFileExist(QString strfile);
	bool isFileOpen(QString strfile);
	bool isDeleteOldExcel();

	void setRow(int nrow);
	void setColumn(int ncol);
	void setName(QString str);
	void setHeadRow(QStringList strlst);
	void setHeadColumn(QStringList strlst);
	void setExcelData(QMap<QString, QStringList> mapdata);

	bool addWorkbook();
	void startExport();
	void endExport();
	void example();
private:
	QString m_strExcelPath;
	int m_nTabRow;
	int m_nTabColumn;
	QString m_strName;
	QStringList m_strlstRow;//��ͷ����Ϣ,���ݱ�ͷ��Ϣ
	QStringList m_strlstCol;//��ͷ����Ϣ�������ͷ��Ϣ
	QMap<QString, QStringList> m_mapExcelData;

	QAxObject* m_pExcel;
	QAxObject* m_pWorkbook;
	//QAxObject* m_pExcel;
	//QAxObject*  m_pWorkbook;
	//QString m_strSavePath;

signals:


public slots:

};
