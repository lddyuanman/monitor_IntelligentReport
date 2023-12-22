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

//实现鼠标拖拽移动
void MonitorSys::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton  && !m_bWndMaxFlag)
    {
        m_bDrag = true;
        //获得鼠标的初始位置
        mouseStartPoint = event->globalPos();
        //mouseStartPoint = event->pos();
        //获得窗口的初始位置
        windowTopLeftPoint = this->frameGeometry().topLeft();
    }
}

void MonitorSys::mouseMoveEvent(QMouseEvent* event)
{
    if (m_bDrag && !m_bWndMaxFlag)
    {	//这里if语句判断，让鼠标在特定控件上进行拖动才有效，比如自绘标题栏控件
        if (!m_pTitleWgt) {
            return;
        }
        //获得鼠标移动的距离
        QPoint distance = event->globalPos() - mouseStartPoint;
        //QPoint distance = event->pos() - mouseStartPoint;
        //改变窗口的位置
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
    //解决了最小化后，第二次从任务栏启动，假死情况20231220
    //解决了标题栏按钮消失问题20231220
    if (m_bWndMaxFlag)
    {
        setWindowState(Qt::WindowMaximized); // 最大化
    }
    else
    {
        setWindowState(Qt::WindowNoState); // 恢复正常状态
    }
    
    setAttribute(Qt::WA_Mapped);
    QWidget::showEvent(e);
}

void MonitorSys::initUI()
{
    //隐藏工具栏
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint | Qt::WindowCloseButtonHint);
    this->setStyleSheet("background-color:#1E1E1E;");//设置背景颜色*/
    this->resize(m_nScreenWidth, m_nSCreenHeight);

    //基于widget的类，在父窗口创建后，子窗口不显示问题
    m_pTitleWgt = new HMonSysTitleWgt(this, m_nScreenWidth);
    m_pTitleWgt->setGeometry(0, 0, m_nScreenWidth, INI_TITLE_HEIGHT);

    QRect rect = QRect(50, 100, 1550, 750);
    int nrow = 26;
    int ncol = 20;
    m_pIntelligentReportWgt = new HIntelligentReportWgt(this, rect,nrow,ncol);
    m_pIntelligentReportWgt->setGeometry((m_nScreenWidth - rect.width()) / 2, (m_nSCreenHeight - rect.height()) / 2,rect.width(),rect.height());

    connect(m_pTitleWgt, SIGNAL(sigMinBtnClicked()), this, SLOT(slotMin()));
    bool b = connect(m_pTitleWgt, SIGNAL(sigMaxBtnClicked(bool)), this, SLOT(slotMax(bool)));
    connect(m_pTitleWgt, SIGNAL(sigCloseBtnClicked()), this, SLOT(slotClose()));
}

QSize MonitorSys::getScreenSize()
{
    // 获取屏幕尺寸
    QDesktopWidget* desktopWidget = QApplication::desktop();
    m_nScreenWidth = desktopWidget->width();
    m_nSCreenHeight = desktopWidget->height();

    // 创建QWidget对象并设置大小
    QWidget w;
    float widthRatio = 0.8;  // 宽度占屏幕的比例为80%
    float heightRatio = 0.6;  // 高度占屏幕的比例为60%
    int width = m_nScreenWidth * widthRatio;
    int height = m_nSCreenHeight * heightRatio;
    w.resize(width, height);

    // 居中显示QWidget窗口
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
        
        setWindowState(Qt::WindowNoState); // 恢复正常状态
        this->setGeometry((m_nScreenWidth - INT_NORMAL_WIDTH) / 2, (m_nSCreenHeight - INT_NORMAL_HEIGHT) / 2, INT_NORMAL_WIDTH, INT_NORMAL_HEIGHT);
        m_pTitleWgt->setGeometry(0, 0, INT_NORMAL_WIDTH, INI_TITLE_HEIGHT);
        m_pTitleWgt->reSize(QSize(INT_NORMAL_WIDTH, INI_TITLE_HEIGHT));
        m_pTitleWgt->setBtnMax();
 
    }       
    else
    {
        setWindowState(Qt::WindowMaximized); // 最大化
        m_pTitleWgt->setGeometry(0, 0, m_nScreenWidth, INI_TITLE_HEIGHT);
        m_pTitleWgt->reSize(QSize(m_nScreenWidth, INI_TITLE_HEIGHT));
        m_pTitleWgt->setBtnNormal();

    }
    m_pTitleWgt->setWndMaxFlag(!bMaxFlag);
    //修改主窗口最大化标志位，保证最大化时窗口不随鼠标移动，只有正常窗口时随鼠标移动
    m_bWndMaxFlag = !bMaxFlag;  
}

void MonitorSys::slotClose()
{
    //释放资源？？？？？？

    close();
}