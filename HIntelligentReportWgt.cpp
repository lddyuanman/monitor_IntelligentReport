#include"HIntelligentReportWgt.h"
#include<QDateTime>
#include<QMouseEvent>

HIntelligentReportWgt::HIntelligentReportWgt(QWidget* parent, QRect rect, int nrow, int ncolumn)
    : QWidget(parent) , m_rectReport(rect) ,m_nRowTab(nrow) ,m_nColumnTab(ncolumn)
{
    initUI();
}
HIntelligentReportWgt::~HIntelligentReportWgt()
{

}

//实现鼠标拖拽移动
//void HIntelligentReportWgt::mousePressEvent(QMouseEvent* event)
//{
//    if (event->button() == Qt::LeftButton )
//    {
//        m_bDrag = true;
//        //获得鼠标的初始位置
//        mouseStartPoint = event->globalPos();
//        //mouseStartPoint = event->pos();
//        //获得窗口的初始位置
//        windowTopLeftPoint = this->frameGeometry().topLeft();
//    }
//}

//void HIntelligentReportWgt::mouseMoveEvent(QMouseEvent* event)
//{
//    if (m_bDrag)
//    {	//这里if语句判断，让鼠标在特定控件上进行拖动才有效，比如自绘标题栏控件
//        if (!this) {
//            return;
//        }
//        //获得鼠标移动的距离
//        QPoint distance = event->globalPos() - mouseStartPoint;
//        //QPoint distance = event->pos() - mouseStartPoint;
//        //改变窗口的位置
//        this->move(windowTopLeftPoint + distance);
//    }
//}

//void HIntelligentReportWgt::mouseReleaseEvent(QMouseEvent* event)
//{
//    if (event->button() == Qt::LeftButton)
//    {
//        m_bDrag = false;
//    }
//}

//void HIntelligentReportWgt::wheelEvent(QWheelEvent* event)
//{
//    QPoint numDegrees;                                     // 定义指针类型参数numDegrees用于获取滚轮转角
//    numDegrees = event->angleDelta();                      // 获取滚轮转角
//    int step = 0;                                          // 设置中间参数step用于将获取的数值转换成整数型
//    if (!numDegrees.isNull())                              // 判断滚轮是否转动
//    {
//        step = numDegrees.y();                             // 将滚轮转动数值传给中间参数step
//    }
//    event->accept();                                       // 获取事件
//    int currentWidth = this->width();                  // 获取当前图像的宽
//    int currentHeight = this->height();                // 获取当前图像的高
//    currentWidth += step;                                  // 对当前图像的高累加
//    currentHeight += step;                                 // 对当前图像的宽累加
//    if (step > 0)                                          // 判断图像是放大还是缩小
//    {
//        QString imgsize = QString("图像放大,尺寸为：%1 * %2")
//            .arg(currentWidth).arg(currentHeight);
//        //qDebug() << imgsize;                               // 打印放大后的图像尺寸
//    }
//    else
//    {
//        QString imgsize = QString("图像缩小,尺寸为：%1 * %2")
//            .arg(currentWidth).arg(currentHeight);
//        //qDebug() << imgsize;                                // 打印缩小后的图像尺寸
//    }
//    this->resize(currentWidth, currentHeight);          // 通过更新图像显示控件的大小来更新图像大小
//}

void HIntelligentReportWgt::initUI()
{
    this->setGeometry(m_rectReport);
    this->setStyleSheet("background-color:#7F7F7F;");
    this->setGeometry(m_rectReport);

    QVBoxLayout* pWgtVblayout = new QVBoxLayout(this);
    pWgtVblayout->setSpacing(0);

    initTopWgt();
    pWgtVblayout->addWidget(m_pTopWgt);

    initReportWgt();
    pWgtVblayout->addWidget(m_pReportWgt);

    this->setLayout(pWgtVblayout);
}

void HIntelligentReportWgt::initTopWgt()
{
    m_pTopWgt = new QWidget(this);
    m_pTopWgt->setStyleSheet("background-color:green;");
    m_pTopWgt->setFixedHeight(INI_TOP_HEIGHT);
    m_pTopWgt->setGeometry(0, 0, m_rectReport.width(), INI_TOP_HEIGHT);

    QHBoxLayout* pWgthblayout = new QHBoxLayout(m_pTopWgt);
    pWgthblayout->setSpacing(0);

    //标签水平布局
    QHBoxLayout* pLabHBlayout = new QHBoxLayout(m_pTopWgt);
    pLabHBlayout->setSpacing(0);

    m_plbTitle = new QLabel(m_pTopWgt);
    m_plbTitle->setObjectName("QLabel_title");
    m_plbTitle->setText(QString::fromLocal8Bit("智能报表系统"));
    m_plbTitle->setStyleSheet("QLabel { color: black; font-size: 20px; }");   

    m_plbSysTime = new QLabel(m_pTopWgt);   
    m_plbSysTime->setObjectName("QLabel_systime");
    m_plbSysTime->setStyleSheet("QLabel { color: black; font-size: 20px; }");
    QDateTime current_date_time = QDateTime::currentDateTime();
    //QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    QString current_date = current_date_time.toString("yyyy.MM.dd ddd");
    m_plbSysTime->setText(QString("<%1>").arg(current_date));

    pLabHBlayout->addWidget(m_plbTitle);
    pLabHBlayout->addWidget(m_plbSysTime);
    pWgthblayout->addLayout(pLabHBlayout);

    //水平间隔
    QSpacerItem* pHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    pWgthblayout->addItem(pHorizontalSpacer);

    //按钮布局
    QHBoxLayout* pBtnHBlayout = new QHBoxLayout(m_pTopWgt);
    pBtnHBlayout->setSpacing(2);

    m_pbtnDay = new QPushButton(m_pTopWgt);
    m_pbtnDay->setObjectName("QPushButton_day");
    m_pbtnDay->setText(QString::fromLocal8Bit("日报"));
    m_pbtnDay->setFixedSize(INT_BUTTON_WIDTH, INT_BUTTON_HEIGHT);

    m_pbtnMonth = new QPushButton(m_pTopWgt);
    m_pbtnMonth->setObjectName("QPushButton_month");
    m_pbtnMonth->setText(QString::fromLocal8Bit("月报"));
    m_pbtnMonth->setFixedSize(INT_BUTTON_WIDTH, INT_BUTTON_HEIGHT);

    m_pbtnYear = new QPushButton(m_pTopWgt);
    m_pbtnYear->setObjectName("QPushButton_year");
    m_pbtnYear->setText(QString::fromLocal8Bit("年报"));
    m_pbtnYear->setFixedSize(INT_BUTTON_WIDTH, INT_BUTTON_HEIGHT);

    m_pbtnMore = new QPushButton(m_pTopWgt);
    m_pbtnMore->setObjectName("QPushButton_more");
    m_pbtnMore->setText(QString::fromLocal8Bit("更多"));
    m_pbtnMore->setFixedSize(INT_BUTTON_WIDTH, INT_BUTTON_HEIGHT);

    pBtnHBlayout->addWidget(m_pbtnDay);
    pBtnHBlayout->addWidget(m_pbtnMonth);
    pBtnHBlayout->addWidget(m_pbtnYear);
    pBtnHBlayout->addWidget(m_pbtnMore);

    pWgthblayout->addLayout(pBtnHBlayout);
    m_pTopWgt->setLayout(pWgthblayout);
}


void HIntelligentReportWgt::initReportWgt()
{
    m_pReportWgt = new QWidget(this);
    // m_pReportWgt->setStyleSheet("background-color:blue;");
    m_pReportWgt->setGeometry(0, INI_TOP_HEIGHT, m_rectReport.width(), m_rectReport.height() - INI_TOP_HEIGHT);

    m_pCustomTabWgt = new HCustomTabWgt(m_pReportWgt, m_nRowTab, m_nColumnTab);
    m_pCustomTabWgt->setGeometry(0, 0, m_rectReport.width(), m_rectReport.height() - INI_TOP_HEIGHT);

    QStringList strlst;
    for (int n = 1; n <= 20; n++)
    {
        strlst.append(QString::fromLocal8Bit("遥测%1").arg(n));
    }
    m_pCustomTabWgt->setFrozenHeaderContent(strlst);
    m_pCustomTabWgt->setColumn(strlst.size());

    /*QRect rect = QRect(0, 0, m_pReportWgt->width(), m_pReportWgt->height());
    m_pCustomTabWgt = new HCustomTabWgt(m_pReportWgt,rect,m_nRowTab,m_nColumnTab);
    m_pCustomTabWgt->setGeometry(rect);*/

   

}