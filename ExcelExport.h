#pragma once
/*
* 处理excel表格导出功能接口
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
	QString getRangeLetter(int nsize);//返回对应excel中对应的列字母


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
	QStringList m_strlstRow;//表头行信息,即纵表头信息
	QStringList m_strlstCol;//表头列信息，即横表头信息
	QMap<QString, QStringList> m_mapExcelData;

	QAxObject* m_pExcel;
	QAxObject* m_pWorkbook;
	//QAxObject* m_pExcel;
	//QAxObject*  m_pWorkbook;
	//QString m_strSavePath;

signals:


public slots:

};
