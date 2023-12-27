#include "MonitorSys.h"
#include <QtWidgets/QDesktopwidget>


MonitorSys::MonitorSys(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    getScreenSize();

    
    initUI();
}

MonitorSys::~MonitorSys()
{
    if (m_pTitleWgt != NULL)
    {
        delete m_pTitleWgt;
    }
}

//ʵ�������ק�ƶ�
void MonitorSys::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton  && !m_bWndMaxFlag)
    {
        m_bDrag = true;
        //������ĳ�ʼλ��
        mouseStartPoint = event->globalPos();
        //mouseStartPoint = event->pos();
        //��ô��ڵĳ�ʼλ��
        windowTopLeftPoint = this->frameGeometry().topLeft();
    }
}

void MonitorSys::mouseMoveEvent(QMouseEvent* event)
{
    if (m_bDrag && !m_bWndMaxFlag)
    {	//����if����жϣ���������ض��ؼ��Ͻ����϶�����Ч�������Ի�������ؼ�
        if (!m_pTitleWgt) {
            return;
        }
        //�������ƶ��ľ���
        QPoint distance = event->globalPos() - mouseStartPoint;
        //QPoint distance = event->pos() - mouseStartPoint;
        //�ı䴰�ڵ�λ��
        this->move(windowTopLeftPoint + distance);
    }
}

void MonitorSys::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bDrag = false;
    }
}

void MonitorSys::showEvent(QShowEvent* e)
{
    //�������С���󣬵ڶ��δ��������������������20231220
    //����˱�������ť��ʧ����20231220
    if (m_bWndMaxFlag)
    {
        setWindowState(Qt::WindowMaximized); // ���
    }
    else
    {
        setWindowState(Qt::WindowNoState); // �ָ�����״̬
    }
    
    setAttribute(Qt::WA_Mapped);
    QWidget::showEvent(e);
}

void MonitorSys::initUI()
{
    //���ع�����
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint | Qt::WindowCloseButtonHint);
    this->setStyleSheet("background-color:#1E1E1E;");//���ñ�����ɫ*/
    this->resize(m_nScreenWidth, m_nSCreenHeight);

    //����widget���࣬�ڸ����ڴ������Ӵ��ڲ���ʾ����
    m_pTitleWgt = new HMonSysTitleWgt(this, m_nScreenWidth);
    m_pTitleWgt->setGeometry(0, 0, m_nScreenWidth, INI_TITLE_HEIGHT);

    QRect rect = QRect(50, 100, 1550, 750);
    int nrow = 24;
    int ncol = 21;
    m_pIntelligentReportWgt = new HIntelligentReportWgt(this, rect,nrow,ncol);
    m_pIntelligentReportWgt->setGeometry((m_nScreenWidth - rect.width()) / 2, (m_nSCreenHeight - rect.height()) / 2,rect.width(),rect.height());

    connect(m_pTitleWgt, SIGNAL(sigMinBtnClicked()), this, SLOT(slotMin()));
    bool b = connect(m_pTitleWgt, SIGNAL(sigMaxBtnClicked(bool)), this, SLOT(slotMax(bool)));
    connect(m_pTitleWgt, SIGNAL(sigCloseBtnClicked()), this, SLOT(slotClose()));
}

QSize MonitorSys::getScreenSize()
{
    // ��ȡ��Ļ�ߴ�
    QDesktopWidget* desktopWidget = QApplication::desktop();
    m_nScreenWidth = desktopWidget->width();
    m_nSCreenHeight = desktopWidget->height();

    // ����QWidget�������ô�С
    QWidget w;
    float widthRatio = 0.8;  // ���ռ��Ļ�ı���Ϊ80%
    float heightRatio = 0.6;  // �߶�ռ��Ļ�ı���Ϊ60%
    int width = m_nScreenWidth * widthRatio;
    int height = m_nSCreenHeight * heightRatio;
    w.resize(width, height);

    // ������ʾQWidget����
    w.move((m_nScreenWidth - width) / 2, (m_nSCreenHeight - height) / 2);

    return QSize(m_nScreenWidth, m_nSCreenHeight);
}

void MonitorSys::slotMin()
{
    this->setWindowState(Qt::WindowMinimized);
    
}

void MonitorSys::slotMax(bool bMaxFlag)
{
    if (bMaxFlag)
    {
        
        setWindowState(Qt::WindowNoState); // �ָ�����״̬
        this->setGeometry((m_nScreenWidth - INT_NORMAL_WIDTH) / 2, (m_nSCreenHeight - INT_NORMAL_HEIGHT) / 2, INT_NORMAL_WIDTH, INT_NORMAL_HEIGHT);
        m_pTitleWgt->setGeometry(0, 0, INT_NORMAL_WIDTH, INI_TITLE_HEIGHT);
        m_pTitleWgt->reSize(QSize(INT_NORMAL_WIDTH, INI_TITLE_HEIGHT));
        m_pTitleWgt->setBtnMax();
 
    }       
    else
    {
        setWindowState(Qt::WindowMaximized); // ���
        m_pTitleWgt->setGeometry(0, 0, m_nScreenWidth, INI_TITLE_HEIGHT);
        m_pTitleWgt->reSize(QSize(m_nScreenWidth, INI_TITLE_HEIGHT));
        m_pTitleWgt->setBtnNormal();

    }
    m_pTitleWgt->setWndMaxFlag(!bMaxFlag);
    //�޸���������󻯱�־λ����֤���ʱ���ڲ�������ƶ���ֻ����������ʱ������ƶ�
    m_bWndMaxFlag = !bMaxFlag;  
}

void MonitorSys::slotClose()
{
    //�ͷ���Դ������������

    close();
}