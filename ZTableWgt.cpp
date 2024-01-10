#include <QHeaderView>
#include <QScrollBar>
#include <QPainter>
#include <QFileDialog>
#include <ActiveQt/QAxObject>
#include <QDesktopServices>
#include <QMessageBox>
#include <QDebug>
#include "ZTableWgt.h"

ZTableWgt::ZTableWgt(QWidget* parent, int nrow, int ncolumn, QString str)
	: QTableWidget(parent), m_nTabRow(nrow), m_nTabColumn(ncolumn) , m_strFirstRowContent(str)
{
	initFrame();
}

ZTableWgt::ZTableWgt(QWidget* parent /* = Q_NULLPTR */, stTableData stTabInfo /* = */)
	: QTableWidget(parent), m_stTableInfo(stTabInfo)
{
	m_strFirstRowContent = m_stTableInfo.strFirstRowContent;
	m_nTabColumn = m_stTableInfo.ncolumn;
	m_nTabRow = m_stTableInfo.nrow;

	m_strlstSecRowCon = m_stTableInfo.strlstSecondRowContent;
	m_strlstFirColCon = m_stTableInfo.strlstFirstColContent;

	m_nReportType = REPORT_DAY;

	initFrame();

	setFirstColumnContent(m_strlstFirColCon);
	setSecondRowContent(m_strlstSecRowCon);
	m_strReportFullPath = "";
	//show();

	m_pExcelExport = new ExcelExport();

	//��ʱˢ��
	m_pTimerUpadate = new QTimer(this);
	connect(m_pTimerUpadate, SIGNAL(timeout()), this, SLOT(slotTimeout()));
	m_pTimerUpadate->setInterval(6000);//����
}

ZTableWgt::~ZTableWgt()
{
	if (m_pTimerUpadate != NULL)
	{
		m_pTimerUpadate->stop();
		delete m_pTimerUpadate;
	}
}

void ZTableWgt::mousePressEvent(QMouseEvent* event) 
{
	/*if (event->button() == Qt::RightButton)
	{
		QPoint position = event->pos();
		int x = position.x();
		int y = position.y();

	}
	else
	{
		mousePressEvent(event);
	}*/
}

void ZTableWgt::startTimer()
{
	if (!m_pTimerUpadate->isActive())
	{
		m_pTimerUpadate->start();
	}
}

void ZTableWgt::setCurrentColumn(int ncolumn)
{
	setColumnCount(ncolumn);//������
	m_nTabColumn = ncolumn + INT_HEAD_COLUMN_COUNT;
}

void ZTableWgt::setCurrentRow(int nrow)
{
	setRowCount(nrow);//������
	m_nTabRow = nrow + INT_HEAD_ROW_COUNT;
}

void ZTableWgt::setFirstRowContent(QString str)
{
	setItem(0, 1, new QTableWidgetItem(QString::fromLocal8Bit("%1").arg(str)));
}

void ZTableWgt::setSecondRowContent(QStringList strlst)
{

	////ʾ����5�У���ȥ���У�ʣ4�У��ڶ��п�ʼ�����ӣ�1.1����ʼ
	//setItem(1, 1, new QTableWidgetItem(QString::fromLocal8Bit("1")));
	//setItem(1, 2, new QTableWidgetItem(QString::fromLocal8Bit("2")));
	//setItem(1, 3, new QTableWidgetItem(QString::fromLocal8Bit("3")));
	//setItem(1,4, new QTableWidgetItem(QString::fromLocal8Bit("4")));

	if (strlst.size() <= 0)
	{
		return;
	}
	//ע�����m_nColumnFrame��ֵ��ÿ���޸ı������ʱ�����£���������
	//��������Ϊm_nTabColumn - 1= strlst.size()
	if (m_nTabColumn != strlst.size() + INT_HEAD_COLUMN_COUNT)
	{
		return;
	}
	//��ͷ�ڶ��е����ݣ��Ǵ����ݱ�ĵ�1�п�ʼ��,��strlstҪ������0~strlst.size()
	for (int nIndex = 0; nIndex < strlst.size(); nIndex++)
	{
		setItem(1, nIndex + 1, new QTableWidgetItem(QString::fromLocal8Bit("%1").arg(strlst.at(nIndex))));
	}
}

void ZTableWgt::setFirstColumnContent(QStringList strlst)
{
	/*//ʾ����6��
	setItem(2, 0, new QTableWidgetItem(QString("1:00")));
	setItem(3, 0, new QTableWidgetItem(QString("1:00")));
	setItem(4, 0, new QTableWidgetItem(QString("1:00")));
	setItem(5, 0, new QTableWidgetItem(QString("1:00")));*/
	
	//���е����ݣ��Ǵ����ݱ�ĵ�0�п�ʼ��
	if (strlst.size() <= 0)
	{
		return;
	}

	//��������Ϊm_nTabRow - 2= strlst.size()
	//if (rowCount() < m_nTabRow)
	if (m_nTabRow != strlst.size() + INT_HEAD_ROW_COUNT)
	{
		return;
	}		

	//�ӵ����п�ʼ
	for (int nrow = 0; nrow < strlst.size(); nrow++)
	{
		setItem((nrow + INT_HEAD_ROW_COUNT), 0, new QTableWidgetItem(QString("%1").arg(strlst.at(nrow))));
		item((nrow + INT_HEAD_ROW_COUNT), 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	}
}

void ZTableWgt::resetFirstColumnContent(QStringList strLst)
{
	deleteAllRows();

	if (m_strlstFirColCon.size() > 0)
	{
		m_strlstFirColCon.clear();
		for (int n = 0; n < strLst.size(); n++)
		{
			m_strlstFirColCon.append(strLst.at(n));
		}
	}

	addRows(strLst.size());
	m_nTabRow = strLst.size() + INT_HEAD_ROW_COUNT;

	setFirstColumnContent(strLst);
}

void ZTableWgt::setTabData(QMap<QString, QStringList> mapData)
{
	m_mapData.clear();

	if (mapData.size() < 0)
	{
		return;
	}

	//������
	QMapIterator<QString, QStringList> itr(mapData);
	while (itr.hasNext())
	{
		itr.next();
		//qDebug() << itr.key() << ":" << itr.value();
		m_mapData.insert(itr.key(), itr.value());
	}	
}

void ZTableWgt::updateData()
{
	//ˢ������,�ӵ����еڶ��п�ʼ������ݣ�����2��1����ʼ
	//QMap<QString, QStringList>,����QString��ң��㣬QStringList�Ƕ�Ӧ��ʱ��ֵ�������ձ�QStringList�洢1:00��2:00��...��24:00��Ķ�Ӧ��ֵ
	
	//���������ݣ��ӵ����еڶ��п�ʼ�����������
	if(m_nTabColumn < 0 || m_nTabRow <= 0)
	{
		return;
	}
	for (int nrow = 3; nrow < m_nTabRow; nrow++)
	{
		for (int ncol = 2; ncol < m_nTabColumn; ncol++)
		{
			this->removeCellWidget(nrow, ncol);
		}
	}
	
	
	//��ȡ����
	m_mapData.clear();	
	emit sigTableData(m_mapData,m_nReportType);

	if (m_mapData.size() <= 0 || m_nTabRow <= 0 || m_nTabColumn <= 0)
	{
		return;
	}

	QString strdata1_1 = this->model()->index(1, 1).data().toString();//��ͷ����ֵ����ң����
	if ((m_mapData[strdata1_1].size() != (m_nTabRow - 2)) || (m_mapData.size() != (m_nTabColumn - 1)))
	{
		qDebug() << "table'column or table's row   is not same whit map data!";
		return;
	}

	//�ӱ��ĵ����еڶ��У�2��1����ʼ���
	for (int ncol = 1; ncol < m_nTabColumn; ncol++)
	{
		QString strdata = this->model()->index(1, ncol).data().toString();//��ͷ����ֵ����ң����
		for (int nrow = 2; nrow < m_nTabRow; nrow++)
		{
			setItem(nrow, ncol, new QTableWidgetItem(QString("%1").arg(m_mapData[strdata].at(nrow-2))));
			item(nrow, ncol)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		}
	}		
}

void ZTableWgt::setReportFullPath(QString str)
{
	m_strReportFullPath = str;
}

void ZTableWgt::saveReport()
{
	if (m_strReportFullPath.isEmpty())
	{
		qDebug() << "file path is null!";
		return;
	}
	m_pExcelExport->setSavePath(m_strReportFullPath);

	
	QStringList strlstCol;
	for (int n = 1; n < this->model()->columnCount(); n++)
	{
		strlstCol.append(this->model()->index(1, n).data().toString());
	}
	m_pExcelExport->setHeadColumn(strlstCol);

	QStringList strlstRow;
	for (int n = 1; n < this->model()->rowCount(); n++)
	{
		strlstRow.append(this->model()->index(n + 1, 0).data().toString());
	}
	m_pExcelExport->setHeadRow(strlstRow);

	//�ļ������ڣ��½�excel
	m_pExcelExport->setRow(m_nTabRow);
	m_pExcelExport->setColumn(m_nTabColumn);
	m_pExcelExport->setName(m_strFirstRowContent);
	m_pExcelExport->setExcelData(m_mapData);
	m_pExcelExport->startExport();
}

void ZTableWgt::openReport()
{
	if (m_strReportFullPath == "")
	{
		return;
	}
	if (QFile::exists(m_strReportFullPath))
	{
		QDesktopServices::openUrl(QUrl::fromLocalFile(m_strReportFullPath));
	}
	/*//���·��������������
	QDir dir("../MonitorSys/export/reports");
	//dir.setFilter(QDir::Files | QDir::NoDotAndDotDot); // �����ļ����� 
	QStringList nameFilters;
	nameFilters << "*.xls";	
	QFileInfoList fileList = dir.entryInfoList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);// ��ȡ�ļ���Ϣ�б� 
	if (fileList.isEmpty())
		return;

	QFileInfo file(m_strReportFullPath);
	QString strFile = file.fileName();
	QString path;
	for (int nindex = 0; nindex < fileList.size(); nindex++)
	{
		QString str = fileList.at(nindex).fileName();
		if (str == strFile)
		{
			path = fileList.at(0).absoluteFilePath(); //filePath();
			break;
		}
	}	

	if (QFile::exists(path))
	{
		QDesktopServices::openUrl(QUrl::fromLocalFile(path));
	}*/
	
}

void ZTableWgt::InitTabHeader(QString str)
{
	switch (INT_HEAD_ROW_COUNT) 
	{
	case 1:
		//***
		break;
	case 2:
		//�ϲ���Ԫ��
		setSpan(0, 0, 2, 1);//���ƣ�ʱ��
		setSpan(0, 1, 1, m_nTabColumn - 1);//�豸����
		setItem(0, 0, new QTableWidgetItem(QString::fromLocal8Bit("ʱ��/����")));
		setItem(0, 1, new QTableWidgetItem(QString::fromLocal8Bit("%1").arg(str)));
		break;
	case 3:
		//***
		break;
	default:
		//***
		break;
	}
}

void ZTableWgt::deleteRow(int nindex)
{
}

void ZTableWgt::addRows(int nrows)
{
	int rowIndex = this->rowCount();//��ǰ��������
	//���˱�ͷ���У���ʼ���������
	for (int n = 0; n < nrows; n++)
	{		
		this->insertRow(rowIndex + n);//�����һ�еĺ������һ��
	}
}

void ZTableWgt::deleteAllRows()
{	
	int counter = this->rowCount();
	
	if (counter < INT_HEAD_ROW_COUNT)
	{
		return;
	}

	//���˱�ͷ���У�ɾ��������
	for (int index = INT_HEAD_ROW_COUNT; index <= counter; index++)
	{
		
		removeRow(INT_HEAD_ROW_COUNT);
		//QTableWidgetItem* item = this->takeVerticalHeaderItem(index);
		//delete item;		
	}
}

void ZTableWgt::addRow(int nIndex)
{
}

void ZTableWgt::initFrame()
{
	horizontalHeader()->setVisible(false);//��ͷ���ɼ�
	verticalHeader()->setVisible(false);//��ͷ���ɼ�
	//setShowGrid(false);//�����߲��ɼ�
	setEditTriggers(QAbstractItemView::NoEditTriggers);//���õ�Ԫ�񲻿ɱ༭
	setSelectionMode(QAbstractItemView::SingleSelection);//��ѡ
	setSelectionBehavior(QAbstractItemView::SelectRows);//ѡ��`
	setFocusPolicy(Qt::NoFocus);//���ѡ���������
	setFrameShape(QFrame::NoFrame);//ȥ���߿� ����

	setColumnCount(m_nTabColumn);//������
	setRowCount(m_nTabRow);//������
    
	//setItemDelegate(new ZItemDelegate(0));//���û滭������Ҫ�ڴ����л�����header��
	 
	//setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//setHorizontalScrollMode(ScrollPerPixel);
	//setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//���ع�����
	//setVerticalScrollMode(ScrollPerPixel);
	//ˮƽ���ã���ͷ���ܳ���������
	horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);// ����Ӧ���
	horizontalScrollBar()->setDisabled(true);//����ʾ������
	//horizontalHeader()->setStretchLastSection(true);// �����һ����������	
	
	horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);	// �����п�ģʽΪ�Զ��������޷��ֶ����죩
	horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);//�������й̶����
	setColumnWidth(0, INT_FIRST_COLUMN_WIDTH);                      //��һ�����ø߶�100px
    
	//��ֱ���ã������и�ģʽΪ�Զ��������Զ������п���䴰�ڣ��޷��ֶ�������
	verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);// ����Ӧ�߶�
	verticalScrollBar()->setDisabled(true);//����ʾ������
	verticalHeader()->setStretchLastSection(true);// �����һ����������

	verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);// �����и�ģʽΪ�Զ��������޷��ֶ����죩
	verticalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);//�������й̶��߶�
	setRowHeight(0, INT_HEAD_ROW_HEIGHT);//��һ�����ø߶�42px

	verticalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);//�������й̶��߶�
	setRowHeight(1, INT_HEAD_ROW_HEIGHT);//�ڶ������ø߶�42px

	InitTabHeader(m_strFirstRowContent);

	setItemDelegate(new ZItemDelegate(1));
	show();
}


//void ZTableWgt::SlotMenuClicked(QAction* act)
//{
//	/*if (act == m_pActionDel)
//	{
//		int nRow = m_pSelectItem->row();
//		QTableWidgetItem* item =this->item(nRow, 1);
//
//		removeRow(nRow);
//	}*/
//}

void ZTableWgt::slotDayTableShow()
{
	m_nReportType = REPORT_DAY;

	QStringList strlstTime;
	for (int n = 0; n < INT_DAY_TIME; n++)
	{
		strlstTime.append(QString("%1:00").arg(n));
	}

	resetFirstColumnContent(strlstTime);
	updateData();
}

void ZTableWgt::slotMonthTableShow()
{
	m_nReportType = REPORT_MONTH;

	QStringList strlstTime;
	for (int n = 1; n <= INT_MONTH_TIME; n++)
	{
		strlstTime.append(QString::fromLocal8Bit("%1��").arg(n));
	}

	resetFirstColumnContent(strlstTime);
	updateData();
}


void ZTableWgt::slotSeasonTableShow()
{
	m_nReportType = REPORT_SECSON;

	QStringList strlstTime;
	for (int n = 1; n <= INT_SEASON_TIME; n++)
	{
		strlstTime.append(QString::fromLocal8Bit("��%1����").arg(n));
	}

	resetFirstColumnContent(strlstTime);
	updateData();
}

void ZTableWgt::slotYearTableShow()
{
	m_nReportType = REPORT_YEAR;

	QStringList strlstTime;
	for (int n = 1; n <= INT_YEAR_TIME; n++)
	{
		strlstTime.append(QString::fromLocal8Bit("%1��").arg(n));
	}
	resetFirstColumnContent(strlstTime);
	updateData();
}

void ZTableWgt::sltOpenReport()
{
	m_pExcelExport->setSavePath(m_strReportFullPath);
	//�ļ����ڲ��Ҳ�ɾ���ɵ��ļ�
	if (m_pExcelExport->isFileExist(m_strReportFullPath))
	{
		if (m_pExcelExport->isFileOpen(m_strReportFullPath))
		{
			QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�ļ��Ѵ򿪣�"));
			qDebug() << "flie isn't delete. Be using!";
			return;
		}
		else
		{
			if (!m_pExcelExport->isDeleteOldExcel())
			{
				openReport();
				return;
			}
		}
	}
	
	saveReport();
	openReport();
}

void ZTableWgt::slotTimeout()
{
	updateData();
}

//����m_frozenTableWgtde ����ʽ�����塢������ɫ��
ZItemDelegate::ZItemDelegate(int type, QObject* parent)
	: QStyledItemDelegate(parent),m_type(type)
{
}

void ZItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (0 == m_type) //header tablewidget
	{
		int rowIndex = index.row();//�к�
		int colIndex = index.column();//�к�
		if (rowIndex == 0 || rowIndex == 1)//ǰ������Ϊheader
		{
			//����
			QColor color;
			color.setRgb(231, 238, 251);

			//���Ʊ���
			painter->setPen(color);
			painter->setBrush(QBrush(color));
			painter->drawRect(option.rect);

			//����
			painter->setPen(QColor(51, 51, 51));
			QTextOption op;
			op.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

			QFont font;
			font.setFamily("Microsoft YaHei");
			//font.setPixelSize(14);
			font.setBold(true);
			painter->setFont(font);

			QRect rect;
			rect = option.rect;
			painter->drawText(rect, index.data(Qt::DisplayRole).toString(), op);
		}
	}
	else {  //content table widget
		//����
		//painter->setPen(QColor(102, 102, 102));
		painter->setPen(QColor(239, 244, 255));
		QTextOption op;
		op.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

		QFont font;
		font.setFamily("Microsoft YaHei");
		font.setPixelSize(12);
		painter->setFont(font);

		if (option.state & QStyle::State_Selected) {
			//painter->fillRect(option.rect, QBrush(QColor(239, 244, 255)));
			painter->fillRect(option.rect, QBrush(QColor(102, 102, 102)));
		}

		painter->drawText(option.rect, index.data(Qt::DisplayRole).toString(), op);

		//�ױ߿�
		painter->setPen(QColor(248, 251, 255));
		painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());

	}

}
