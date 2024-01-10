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

	//定时刷新
	m_pTimerUpadate = new QTimer(this);
	connect(m_pTimerUpadate, SIGNAL(timeout()), this, SLOT(slotTimeout()));
	m_pTimerUpadate->setInterval(6000);//毫秒
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
	setColumnCount(ncolumn);//设置列
	m_nTabColumn = ncolumn + INT_HEAD_COLUMN_COUNT;
}

void ZTableWgt::setCurrentRow(int nrow)
{
	setRowCount(nrow);//设置行
	m_nTabRow = nrow + INT_HEAD_ROW_COUNT;
}

void ZTableWgt::setFirstRowContent(QString str)
{
	setItem(0, 1, new QTableWidgetItem(QString::fromLocal8Bit("%1").arg(str)));
}

void ZTableWgt::setSecondRowContent(QStringList strlst)
{

	////示例：5列，减去首列，剩4列，第二行开始，即从（1.1）开始
	//setItem(1, 1, new QTableWidgetItem(QString::fromLocal8Bit("1")));
	//setItem(1, 2, new QTableWidgetItem(QString::fromLocal8Bit("2")));
	//setItem(1, 3, new QTableWidgetItem(QString::fromLocal8Bit("3")));
	//setItem(1,4, new QTableWidgetItem(QString::fromLocal8Bit("4")));

	if (strlst.size() <= 0)
	{
		return;
	}
	//注意更新m_nColumnFrame的值，每次修改报表的列时，更新？？？？？
	//数据列数为m_nTabColumn - 1= strlst.size()
	if (m_nTabColumn != strlst.size() + INT_HEAD_COLUMN_COUNT)
	{
		return;
	}
	//表头第二行的内容，是从数据表的第1列开始的,但strlst要从索引0~strlst.size()
	for (int nIndex = 0; nIndex < strlst.size(); nIndex++)
	{
		setItem(1, nIndex + 1, new QTableWidgetItem(QString::fromLocal8Bit("%1").arg(strlst.at(nIndex))));
	}
}

void ZTableWgt::setFirstColumnContent(QStringList strlst)
{
	/*//示例：6行
	setItem(2, 0, new QTableWidgetItem(QString("1:00")));
	setItem(3, 0, new QTableWidgetItem(QString("1:00")));
	setItem(4, 0, new QTableWidgetItem(QString("1:00")));
	setItem(5, 0, new QTableWidgetItem(QString("1:00")));*/
	
	//首列的内容，是从数据表的第0行开始的
	if (strlst.size() <= 0)
	{
		return;
	}

	//数行列数为m_nTabRow - 2= strlst.size()
	//if (rowCount() < m_nTabRow)
	if (m_nTabRow != strlst.size() + INT_HEAD_ROW_COUNT)
	{
		return;
	}		

	//从第三行开始
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

	//迭代器
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
	//刷新数据,从第三行第二列开始填充数据，即（2，1）开始
	//QMap<QString, QStringList>,其中QString是遥测点，QStringList是对应的时间值，比如日表，QStringList存储1:00、2:00、...、24:00点的对应的值
	
	//清楚表格数据，从第三行第二列开始清楚数据内容
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
	
	
	//获取数据
	m_mapData.clear();	
	emit sigTableData(m_mapData,m_nReportType);

	if (m_mapData.size() <= 0 || m_nTabRow <= 0 || m_nTabColumn <= 0)
	{
		return;
	}

	QString strdata1_1 = this->model()->index(1, 1).data().toString();//表头纵列值，如遥测点等
	if ((m_mapData[strdata1_1].size() != (m_nTabRow - 2)) || (m_mapData.size() != (m_nTabColumn - 1)))
	{
		qDebug() << "table'column or table's row   is not same whit map data!";
		return;
	}

	//从表格的第三行第二列（2，1）开始填充
	for (int ncol = 1; ncol < m_nTabColumn; ncol++)
	{
		QString strdata = this->model()->index(1, ncol).data().toString();//表头纵列值，如遥测点等
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

	//文件不存在，新建excel
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
	/*//解决路径中有中文问题
	QDir dir("../MonitorSys/export/reports");
	//dir.setFilter(QDir::Files | QDir::NoDotAndDotDot); // 过滤文件类型 
	QStringList nameFilters;
	nameFilters << "*.xls";	
	QFileInfoList fileList = dir.entryInfoList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);// 获取文件信息列表 
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
		//合并单元格
		setSpan(0, 0, 2, 1);//名称，时间
		setSpan(0, 1, 1, m_nTabColumn - 1);//设备名称
		setItem(0, 0, new QTableWidgetItem(QString::fromLocal8Bit("时间/名称")));
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
	int rowIndex = this->rowCount();//当前表格的行数
	//除了表头两行，开始往后插入行
	for (int n = 0; n < nrows; n++)
	{		
		this->insertRow(rowIndex + n);//在最后一行的后面插入一行
	}
}

void ZTableWgt::deleteAllRows()
{	
	int counter = this->rowCount();
	
	if (counter < INT_HEAD_ROW_COUNT)
	{
		return;
	}

	//除了表头两行，删除其他列
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
	horizontalHeader()->setVisible(false);//表头不可见
	verticalHeader()->setVisible(false);//表头不可见
	//setShowGrid(false);//网格线不可见
	setEditTriggers(QAbstractItemView::NoEditTriggers);//设置单元格不可编辑
	setSelectionMode(QAbstractItemView::SingleSelection);//单选
	setSelectionBehavior(QAbstractItemView::SelectRows);//选行`
	setFocusPolicy(Qt::NoFocus);//解决选中虚框问题
	setFrameShape(QFrame::NoFrame);//去除边框 尴尬

	setColumnCount(m_nTabColumn);//设置列
	setRowCount(m_nTabRow);//设置行
    
	//setItemDelegate(new ZItemDelegate(0));//设置绘画代理（主要在代理中画出来header）
	 
	//setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//setHorizontalScrollMode(ScrollPerPixel);
	//setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏滚动条
	//setVerticalScrollMode(ScrollPerPixel);
	//水平设置，表头不能充满的问题
	horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);// 自适应宽度
	horizontalScrollBar()->setDisabled(true);//不显示滚动条
	//horizontalHeader()->setStretchLastSection(true);// 将最后一列填充满表格	
	
	horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);	// 设置列宽模式为自动调整（无法手动拉伸）
	horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);//设置首列固定宽度
	setColumnWidth(0, INT_FIRST_COLUMN_WIDTH);                      //第一列设置高度100px
    
	//垂直设置，设置行高模式为自动调整（自动拉伸列宽填充窗口，无法手动调整）
	verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);// 自适应高度
	verticalScrollBar()->setDisabled(true);//不显示滚动条
	verticalHeader()->setStretchLastSection(true);// 将最后一列填充满表格

	verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);// 设置行高模式为自动调整（无法手动拉伸）
	verticalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);//设置首行固定高度
	setRowHeight(0, INT_HEAD_ROW_HEIGHT);//第一行设置高度42px

	verticalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);//设置首行固定高度
	setRowHeight(1, INT_HEAD_ROW_HEIGHT);//第二行设置高度42px

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
		strlstTime.append(QString::fromLocal8Bit("%1日").arg(n));
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
		strlstTime.append(QString::fromLocal8Bit("第%1季度").arg(n));
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
		strlstTime.append(QString::fromLocal8Bit("%1月").arg(n));
	}
	resetFirstColumnContent(strlstTime);
	updateData();
}

void ZTableWgt::sltOpenReport()
{
	m_pExcelExport->setSavePath(m_strReportFullPath);
	//文件存在并且不删除旧的文件
	if (m_pExcelExport->isFileExist(m_strReportFullPath))
	{
		if (m_pExcelExport->isFileOpen(m_strReportFullPath))
		{
			QMessageBox::warning(NULL, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("文件已打开！"));
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

//绘制m_frozenTableWgtde 的样式，字体、背景颜色等
ZItemDelegate::ZItemDelegate(int type, QObject* parent)
	: QStyledItemDelegate(parent),m_type(type)
{
}

void ZItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (0 == m_type) //header tablewidget
	{
		int rowIndex = index.row();//行号
		int colIndex = index.column();//列号
		if (rowIndex == 0 || rowIndex == 1)//前两行作为header
		{
			//背景
			QColor color;
			color.setRgb(231, 238, 251);

			//绘制背景
			painter->setPen(color);
			painter->setBrush(QBrush(color));
			painter->drawRect(option.rect);

			//字体
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
		//文字
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

		//底边框
		painter->setPen(QColor(248, 251, 255));
		painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());

	}

}
