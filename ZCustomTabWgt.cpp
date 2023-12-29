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
    m_pTableWgt->horizontalHeader()->setVisible(false);//��ͷ���ɼ�
    m_pTableWgt->verticalHeader()->setVisible(false);//��ͷ���ɼ�

    m_pTableWgt->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//���ع�����
    m_pTableWgt->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//
  
    m_pTableWgt->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);//���÷ǵ�Ԫ����
    m_pTableWgt->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

   // �����п�ģʽΪ�Զ��������Զ������п���䴰�ڣ��޷��ֶ�������
    //m_pTableWgt->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //����ʹ��3(�����Զ���������һ�����ù̶��п�)
    m_pTableWgt->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_pTableWgt->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    m_pTableWgt->setColumnWidth(0, 80);

    // �����и�ģʽΪ�Զ��������Զ������п���䴰�ڣ��޷��ֶ�������
   //m_pTableWgt->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   //����ʹ��3(�����Զ���������һ�����ù̶��и�)
    m_pTableWgt->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); //��������Ӧ�и�
   // m_pTableWgt->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_pTableWgt->verticalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
   // m_pTableWgt->verticalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    m_pTableWgt->setRowHeight(0, 80);
    //m_pTableWgt->setRowHeight(1, 80);

    //����ѡ��ʱΪ����ѡ��    
   // m_pTableWgt->setSelectionBehavior(QAbstractItemView::SelectRows);
   // m_pTableWgt->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ȥ��ѡ�����߿�
    m_pTableWgt->setFocusPolicy(Qt::NoFocus);//���ѡ���������
   // m_pTableWgt->setFrameShape(QFrame::NoFrame);//ȥ���߿� ����

    //��񲻿ɱ༭
    m_pTableWgt->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pTableWgt->setSelectionMode(QAbstractItemView::NoSelection);
    m_pTableWgt->setSelectionBehavior(QAbstractItemView::SelectRows);
 
}