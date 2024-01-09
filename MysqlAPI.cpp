//#include<QSqlDatabase>
#include <QMessageBox>
#include <QMap>
#include "MysqlAPI.h"
#include "DataStruct.h"

MysqlAPI::MysqlAPI()
{

}

MysqlAPI::~MysqlAPI()
{
	//处理关闭数据库连接
}

bool MysqlAPI::isConnect()
{

	//QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	//db.setHostName("127.0.0.1");  //连接本地主机
	//db.setPort(3306);
	//db.setDatabaseName("数据库名");
	//db.setUserName("用户名");
	//db.setPassword("密码");
	//bool ok = db.open();
	//if (ok) {
	//	QMessageBox::information(this, "infor", "link success");
	//}
	//else {
	//	QMessageBox::information(this, "infor", "link failed");
	//	qDebug() << "error open database because" << db.lastError().text();
	//}
	return true;
}

void MysqlAPI::getDayData(QMap<QString, QStringList>& mapvalue)
{
	for (int n = 0; n < 21; n++)
	{
		QString strKey = QString::fromLocal8Bit("遥测%1").arg(n);
		QStringList strlst;
		for (int  i = 0; i < 24; i++)
		{
			strlst.append(QString("%10:00").arg(i));			
		}
		mapvalue.insert(strKey, strlst);
	}
}

void MysqlAPI::getMonthData(QMap<QString, QStringList>& mapvalue)
{
	for (int n = 0; n < 21; n++)
	{
		QString strKey = QString::fromLocal8Bit("遥测%1").arg(n);
		QStringList strlst;
		for (int i = 0; i < 31; i++)
		{
			strlst.append(QString("%10:00").arg(i));
		}
		mapvalue.insert(strKey, strlst);
	}
}

void MysqlAPI::getSecsonData(QMap<QString, QStringList>& mapvalue)
{
	for (int n = 0; n < 21; n++)
	{
		QString strKey = QString::fromLocal8Bit("遥测%1").arg(n);
		QStringList strlst;
		for (int i = 0; i < 4; i++)
		{
			strlst.append(QString("%10:00").arg(i));
		}
		mapvalue.insert(strKey, strlst);
	}
}

void MysqlAPI::getYearData(QMap<QString, QStringList>& mapvalue)
{
	for (int n = 0; n < 21; n++)
	{
		QString strKey = QString::fromLocal8Bit("遥测%1").arg(n);
		QStringList strlst;
		for (int i = 0; i < 12; i++)
		{
			strlst.append(QString("%10:00").arg(i));
		}
		mapvalue.insert(strKey, strlst);
	}
}

void MysqlAPI::getData(QMap<QString, QStringList>& mapvalue, QString startTime, QString endTime)
{
}

void MysqlAPI::getData(QMap<QString, QStringList>& mapvalue, ReportType type)
{
	switch (type)
	{
	case REPORT_DAY:
		getDayData(mapvalue);
		break;
	case REPORT_MONTH:
		getMonthData(mapvalue);
		break;
	case REPORT_SECSON:
		getSecsonData(mapvalue);
		break;
	case REPORT_YEAR:
		getYearData(mapvalue);
		break;
	default:
		break;
	}

}


void MysqlAPI::slotGetData(QMap<QString, QStringList>& mapvalue,ReportType type)
{
	getData(mapvalue,type);
}