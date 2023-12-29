#include "ZTableWgt.h"

#include<QHeaderView>
#include<QScrollBar>
#include<QPainter>

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

	initFrame();

	setFirstColumnContent(m_strlstFirColCon);
	setSecondRowContent(m_strlstSecRowCon);
	//show();
}

ZTableWgt::~ZTableWgt()
{

}

void ZTableWgt::setFirstRowContent(QString str)
{
	setItem(0, 1, new QTableWidgetItem(QString::fromLocal8Bit("%1").arg(str)));
}

void ZTableWgt::setSecondRowContent(QStringList strlst)
{

	////5列，减去首列，剩4列，第二行开始，即从（1.1）开始
	//setItem(1, 1, new QTableWidgetItem(QString::fromLocal8Bit("1")));
	//setItem(1, 2, new QTableWidgetItem(QString::fromLocal8Bit("2")));
	//setItem(1, 3, new QTableWidgetItem(QString::fromLocal8Bit("3")));


	if (strlst.size() <= 0)
	{
		return;
	}
	//注意更新m_nColumnFrame的值，每次修改报表的列时，更新？？？？？
	//数据列数为m_nTabColumn - 1= strlst.size()
	if (m_nTabColumn != strlst.size() + 1)
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
	/*//6行
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

void ZTableWgt::InitTabHeader(QString str)
{
	if (INT_HEAD_ROW_COUNT == 2)
	{
		//合并单元格
		setSpan(0, 0, 2, 1);//名称，时间
		setSpan(0, 1, 1, m_nTabColumn - 1);//设备名称
		setItem(0, 0, new QTableWidgetItem(QString::fromLocal8Bit("时间/名称")));
		setItem(0, 1, new QTableWidgetItem(QString::fromLocal8Bit("%1").arg(str)));
	}
	else if ( INT_HEAD_ROW_COUNT == 1)
	{
		//增加处理
	}
	else if (INT_HEAD_ROW_COUNT == 3)
	{
		//增加处理
	}
	
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

	setRowHeight(0, INT_HEAD_ROW_HEIGHT);//第一行设置高度42px
	setRowHeight(1, INT_HEAD_ROW_HEIGHT);//第二行设置高度42px
    
	//setItemDelegate(new ZItemDelegate(0));//设置绘画代理（主要在代理中画出来header）
	// 
	//水平设置，表头不能充满的问题
	horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);// 自适应宽度
	horizontalScrollBar()->setDisabled(true);//不显示滚动条
	horizontalHeader()->setStretchLastSection(true);// 将最后一列填充满表格		
	horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);	// 设置列宽模式为自动调整（无法手动拉伸）
	horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);//设置首列固定宽度
	setColumnWidth(0, INT_FIRST_COLUMN_WIDTH);                      //第一列设置高度100px

	//垂直设置，设置行高模式为自动调整（自动拉伸列宽填充窗口，无法手动调整）
	verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);// 自适应高度
	verticalScrollBar()->setDisabled(true);//不显示滚动条
	verticalHeader()->setStretchLastSection(true);// 将最后一列填充满表格
	verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);// 设置行高模式为自动调整（无法手动拉伸）

	InitTabHeader(m_strFirstRowContent);

	setItemDelegate(new ZItemDelegate(1));
	show();
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
			font.setPixelSize(14);
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
