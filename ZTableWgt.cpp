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

	////5�У���ȥ���У�ʣ4�У��ڶ��п�ʼ�����ӣ�1.1����ʼ
	//setItem(1, 1, new QTableWidgetItem(QString::fromLocal8Bit("1")));
	//setItem(1, 2, new QTableWidgetItem(QString::fromLocal8Bit("2")));
	//setItem(1, 3, new QTableWidgetItem(QString::fromLocal8Bit("3")));


	if (strlst.size() <= 0)
	{
		return;
	}
	//ע�����m_nColumnFrame��ֵ��ÿ���޸ı�������ʱ�����£���������
	//��������Ϊm_nTabColumn - 1= strlst.size()
	if (m_nTabColumn != strlst.size() + 1)
	{
		return;
	}
	//��ͷ�ڶ��е����ݣ��Ǵ����ݱ��ĵ�1�п�ʼ��,��strlstҪ������0~strlst.size()
	for (int nIndex = 0; nIndex < strlst.size(); nIndex++)
	{
		setItem(1, nIndex + 1, new QTableWidgetItem(QString::fromLocal8Bit("%1").arg(strlst.at(nIndex))));
	}
}

void ZTableWgt::setFirstColumnContent(QStringList strlst)
{
	/*//6��
	setItem(2, 0, new QTableWidgetItem(QString("1:00")));
	setItem(3, 0, new QTableWidgetItem(QString("1:00")));
	setItem(4, 0, new QTableWidgetItem(QString("1:00")));
	setItem(5, 0, new QTableWidgetItem(QString("1:00")));*/
	
	//���е����ݣ��Ǵ����ݱ��ĵ�0�п�ʼ��
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

void ZTableWgt::InitTabHeader(QString str)
{
	if (INT_HEAD_ROW_COUNT == 2)
	{
		//�ϲ���Ԫ��
		setSpan(0, 0, 2, 1);//���ƣ�ʱ��
		setSpan(0, 1, 1, m_nTabColumn - 1);//�豸����
		setItem(0, 0, new QTableWidgetItem(QString::fromLocal8Bit("ʱ��/����")));
		setItem(0, 1, new QTableWidgetItem(QString::fromLocal8Bit("%1").arg(str)));
	}
	else if ( INT_HEAD_ROW_COUNT == 1)
	{
		//���Ӵ���
	}
	else if (INT_HEAD_ROW_COUNT == 3)
	{
		//���Ӵ���
	}
	
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

	setRowHeight(0, INT_HEAD_ROW_HEIGHT);//��һ�����ø߶�42px
	setRowHeight(1, INT_HEAD_ROW_HEIGHT);//�ڶ������ø߶�42px
    
	//setItemDelegate(new ZItemDelegate(0));//���û滭��������Ҫ�ڴ����л�����header��
	// 
	//ˮƽ���ã���ͷ���ܳ���������
	horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);// ����Ӧ����
	horizontalScrollBar()->setDisabled(true);//����ʾ������
	horizontalHeader()->setStretchLastSection(true);// �����һ�����������		
	horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);	// �����п�ģʽΪ�Զ��������޷��ֶ����죩
	horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);//�������й̶�����
	setColumnWidth(0, INT_FIRST_COLUMN_WIDTH);                      //��һ�����ø߶�100px

	//��ֱ���ã������и�ģʽΪ�Զ��������Զ������п���䴰�ڣ��޷��ֶ�������
	verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);// ����Ӧ�߶�
	verticalScrollBar()->setDisabled(true);//����ʾ������
	verticalHeader()->setStretchLastSection(true);// �����һ�����������
	verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);// �����и�ģʽΪ�Զ��������޷��ֶ����죩

	InitTabHeader(m_strFirstRowContent);

	setItemDelegate(new ZItemDelegate(1));
	show();
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
			font.setPixelSize(14);
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