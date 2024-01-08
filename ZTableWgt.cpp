#include<QHeaderView>
#include<QScrollBar>
#include<QPainter>
#include <QFileDialog>
#include<ActiveQt/QAxObject>
#include<QDesktopServices>
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
}

ZTableWgt::~ZTableWgt()
{

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

void ZTableWgt::updateData()
{
	//ˢ������,�ӵ����еڶ��п�ʼ������ݣ�����2��1����ʼ
    //��������QMap����QVector
	//QMap<QString, QList<QString>>,����QString��ң��㣬QList<QString>�Ƕ�Ӧ��ʱ��ֵ�������ձ�QList�洢1:00��2:00��3:00��......24:00��Ķ�Ӧ��ֵ
    //QVector<QVector<int>> array(rows,QVector<int>(cols))
}

void ZTableWgt::setReportFullPath(QString str)
{
	m_strReportFullPath = str;
}

void ZTableWgt::saveReport()
{
	//���������˶�ԭ���ļ�����д���ˢ�µ����⣬�ͽ�ԭ���ļ�ɾ��������д�ļ�
	//��ȡ����·��
	//QString filepath = QFileDialog::getSaveFileName(this, tr("Save"), ".", tr(" (*.xlsx)"));
	if (!m_strReportFullPath.isEmpty()) {
		QAxObject* Excel = new QAxObject(this);
		//����Excel�ؼ�
		Excel->setControl("Excel.Application");
		//����ʾ����
		Excel->dynamicCall("SetVisible (bool Visible)", "false");
		//����ʾ�κξ�����Ϣ�����Ϊtrue��ô�ڹر��ǻ�������ơ��ļ����޸ģ��Ƿ񱣴桱����ʾ
		Excel->setProperty("DisplayAlerts", false);
		//��ȡ����������
		QAxObject* workbooks = Excel->querySubObject("WorkBooks");
		//�½�һ��������
		workbooks->dynamicCall("Add");
		//��ȡ��ǰ������
		QAxObject* workbook = Excel->querySubObject("ActiveWorkBook");
		//��ȡ��������
		QAxObject* worksheets = workbook->querySubObject("Sheets");
		//��ȡ�������ϵĹ�����1����sheet1
		QAxObject* worksheet = worksheets->querySubObject("Item(int)", 1);

		//������Ͻ�
		QAxObject* Range = worksheet->querySubObject("Cells(int,int)", 1, 1);//�����excel�ļ��ڶ���
		Range->dynamicCall("SetValue(const QString &)", this->model()->index(0, 0).data().toString());
		//���ñ�ͷֵ�����ͷ
		int ncol = this->columnCount() - 1;
		for (int i = 1; i < ncol + 1; i++)
		{
			//���ö��и���
			QAxObject* Range = worksheet->querySubObject("Cells(int,int)", 1, i+1);//�����excel�ļ��ڶ���
			Range->dynamicCall("SetValue(const QString &)", this->model()->index(1,i).data().toString());
			//Range->dynamicCall("SetValue(const QString &)", this->horizontalHeaderItem(i - 1)->text());
		}
		//���ñ�ͷֵ���ݱ�ͷ
		int nrow = this->rowCount() - 2;
		for (int i = 1; i < nrow + 1; i++)
		{
			//���õڶ��и���
			QAxObject* Range = worksheet->querySubObject("Cells(int,int)", i+1, 1);//�����excel�ļ��ڶ���
			Range->dynamicCall("SetValue(const QString &)", this->model()->index(i + 1, 0).data().toString());
			//Range->dynamicCall("SetValue(const QString &)", this->horizontalHeaderItem(i - 1)->text());
		}


		//���ñ������
		int nrow1 = this->rowCount() - 2;
		for (int i = 1; i < nrow1 + 1; i++)
		{
			for (int j = 1; j < this->columnCount() + 1; j++)
			{
				QAxObject* Range = worksheet->querySubObject("Cells(int,int)", i + 1, j);
				//Range->dynamicCall("SetValue(const QString &)", this->item(i - 1, j - 1)->data(Qt::DisplayRole).toString());
				//Range->dynamicCall("SetValue(const QString &)", this->item(i - 1, j - 1)->data(Qt::DisplayRole).toString());
			}
		}
		workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(m_strReportFullPath));//������filepath
		workbook->dynamicCall("Close()");//�رչ�����
		Excel->dynamicCall("QUIt()");//�ر�Excel
		delete Excel;
		Excel = NULL;
		//qDebug() << "�����ɹ���������";
	}

	switch (m_nReportType)
	{
	case REPORT_DAY:
		//�����ձ���
		break;
	case REPORT_MONTH:
		//�����±�
		break;
	case REPORT_SECSON:
		//���漾��
		break;
	case REPORT_YEAR:
		//�����걨
		break;
	default:
		break;
	}
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

void ZTableWgt::contextMenuEvent(QContextMenuEvent* event)
{
	Q_UNUSED(event);
	QMenu menu;
	//����Ҽ��˵���ѡ��
	menu.addAction("����1��ѡ��1");
	menu.addAction("����1��ѡ��2");
	menu.addAction("����1��ѡ��3");
	//��ʾmenu�˵�����������ʾλ��Ϊ���λ��
	menu.exec(QCursor::pos());
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

void ZTableWgt::tableContexMenuRequested(QPoint& pos)
{
	m_pContextMenu->addAction(m_pActionDel);
	m_pContextMenu->exec(QCursor::pos());
}
void ZTableWgt::on_tableViewCustomContextMenuRequested(const QPoint& pos)
{
	//! ��չ���˴���pos��������ʹ��QTableView��indexAt ������ȡ��ǰ����¿ؼ���QModelIndex���󣨿������жϲ�����
	//Q_UNUSED(pos);
	QTableWidgetItem* item = this->currentItem();
	if (item == NULL)
	{
		return;
	}
	QMenu menu;
	//����Ҽ��˵���ѡ��
	menu.addAction("����2��ѡ��1");
	menu.addAction("����2��ѡ��2");
	menu.addAction("����2��ѡ��3");
	//��ʾmenu�˵�����������ʾλ��Ϊ���λ��
	menu.exec(QCursor::pos());
}

void ZTableWgt::SlotMenuClicked(QAction* act)
{
	/*if (act == m_pActionDel)
	{
		int nRow = m_pSelectItem->row();
		QTableWidgetItem* item =this->item(nRow, 1);

		removeRow(nRow);
	}*/
}

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
	saveReport();
	openReport();
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
