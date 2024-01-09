#pragma once
/*
*mysql数据库处理接口，
* 注意：不要跟业务挂钩
*/
#include <QObject>
#include "GlobalVariable.h"

class MysqlAPI :public QObject
{
	Q_OBJECT

public:
	MysqlAPI();
	~MysqlAPI();

	bool isConnect();

	void getDayData(QMap<QString, QStringList>& mapvalue);
	void getMonthData(QMap<QString, QStringList>& mapvalue);
	void getSecsonData(QMap<QString, QStringList>& mapvalue);
	void getYearData(QMap<QString, QStringList>& mapvalue);
	void getData(QMap<QString, QStringList>& mapvalue, QString startTime, QString endTime);
	void getData(QMap<QString, QStringList>& mapvalue, ReportType type);
signals:


public slots:
	void slotGetData(QMap<QString, QStringList>& mapvalue, ReportType type);
};
