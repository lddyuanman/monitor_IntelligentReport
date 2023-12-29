#include"ZCustomTabWgt.h"
#include<QHeaderView>
#include<QLabel>
#include<QVBoxLayout>
#include<QComboBox>
#include<QScrollBar>

ZCustomTabWgt::ZCustomTabWgt(QWidget* parent,QRect rect, int nRow, int nColumn)
    : QTableWidget(parent) ,m_rectTab(rect), m_nRow(nRow) , m_nColumn(nColumn)
{
    initUI();
}
ZCustomTabWgt::~ZCustomTabWgt()
{

}

void ZCustomTabWgt::initUI()
{
    m_pTableWgt = new QTableWidget(m_nRow, m_nColumn, this);
    m_pTableWgt->setGeometry(m_rectTab);
    m_pTableWgt->horizontalHeader()->setVisible(false);//表头不可见
    m_pTableWgt->verticalHeader()->setVisible(false);//表头不可见

    m_pTableWgt->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏滚动条
    m_pTableWgt->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//
  
    m_pTableWgt->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);//设置非单元滚动
    m_pTableWgt->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

   // 设置列宽模式为自动调整（自动拉伸列宽填充窗口，无法手动调整）
    //m_pTableWgt->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //搭配使用3(整体自动调整，第一列设置固定列宽)
    m_pTableWgt->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_pTableWgt->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    m_pTableWgt->setColumnWidth(0, 80);

    // 设置行高模式为自动调整（自动拉伸列宽填充窗口，无法手动调整）
   //m_pTableWgt->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   //搭配使用3(整体自动调整，第一行设置固定行高)
    m_pTableWgt->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); //设置自适应行高
   // m_pTableWgt->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_pTableWgt->verticalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
   // m_pTableWgt->verticalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    m_pTableWgt->setRowHeight(0, 80);
    //m_pTableWgt->setRowHeight(1, 80);

    //设置选中时为整行选中    
   // m_pTableWgt->setSelectionBehavior(QAbstractItemView::SelectRows);
   // m_pTableWgt->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //去除选中虚线框
    m_pTableWgt->setFocusPolicy(Qt::NoFocus);//解决选中虚框问题
   // m_pTableWgt->setFrameShape(QFrame::NoFrame);//去除边框 尴尬

    //表格不可编辑
    m_pTableWgt->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pTableWgt->setSelectionMode(QAbstractItemView::NoSelection);
    m_pTableWgt->setSelectionBehavior(QAbstractItemView::SelectRows);
 
}