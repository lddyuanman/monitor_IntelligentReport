#include"HIntelligentReportWgt.h"
#include "HGlobalVariable.h"
#include<QDateTime>
#include<QMouseEvent>

HIntelligentReportWgt::HIntelligentReportWgt(QWidget* parent, stTableData stTableInfo)
    :QWidget(parent), m_stTableDataInfo(stTableInfo)
{
    m_rectReport = QRect(50, 100, 1550, 750);//������m_pTabWgt����ʾ������
    initUI();
}

HIntelligentReportWgt::HIntelligentReportWgt(QWidget* parent, QRect rect, int nrow, int ncolumn)
    : QWidget(parent) , m_rectReport(rect) ,m_nRowTab(nrow) ,m_nColumnTab(ncolumn)
{
    initUI();
}
HIntelligentReportWgt::~HIntelligentReportWgt()
{

}

//ʵ�������ק�ƶ�
//void HIntelligentReportWgt::mousePressEvent(QMouseEvent* event)
//{
//    if (event->button() == Qt::LeftButton )
//    {
//        m_bDrag = true;
//        //������ĳ�ʼλ��
//        mouseStartPoint = event->globalPos();
//        //mouseStartPoint = event->pos();
//        //��ô��ڵĳ�ʼλ��
//        windowTopLeftPoint = this->frameGeometry().topLeft();
//    }
//}

//void HIntelligentReportWgt::mouseMoveEvent(QMouseEvent* event)
//{
//    if (m_bDrag)
//    {	//����if����жϣ���������ض��ؼ��Ͻ����϶�����Ч�������Ի�������ؼ�
//        if (!this) {
//            return;
//        }
//        //�������ƶ��ľ���
//        QPoint distance = event->globalPos() - mouseStartPoint;
//        //QPoint distance = event->pos() - mouseStartPoint;
//        //�ı䴰�ڵ�λ��
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
//    QPoint numDegrees;                                     // ����ָ�����Ͳ���numDegrees���ڻ�ȡ����ת��
//    numDegrees = event->angleDelta();                      // ��ȡ����ת��
//    int step = 0;                                          // �����м����step���ڽ���ȡ����ֵת����������
//    if (!numDegrees.isNull())                              // �жϹ����Ƿ�ת��
//    {
//        step = numDegrees.y();                             // ������ת����ֵ�����м����step
//    }
//    event->accept();                                       // ��ȡ�¼�
//    int currentWidth = this->width();                  // ��ȡ��ǰͼ��Ŀ�
//    int currentHeight = this->height();                // ��ȡ��ǰͼ��ĸ�
//    currentWidth += step;                                  // �Ե�ǰͼ��ĸ��ۼ�
//    currentHeight += step;                                 // �Ե�ǰͼ��Ŀ��ۼ�
//    if (step > 0)                                          // �ж�ͼ���ǷŴ�����С
//    {
//        QString imgsize = QString("ͼ��Ŵ�,�ߴ�Ϊ��%1 * %2")
//            .arg(currentWidth).arg(currentHeight);
//        //qDebug() << imgsize;                               // ��ӡ�Ŵ���ͼ��ߴ�
//    }
//    else
//    {
//        QString imgsize = QString("ͼ����С,�ߴ�Ϊ��%1 * %2")
//            .arg(currentWidth).arg(currentHeight);
//        //qDebug() << imgsize;                                // ��ӡ��С���ͼ��ߴ�
//    }
//    this->resize(currentWidth, currentHeight);          // ͨ������ͼ����ʾ�ؼ��Ĵ�С������ͼ���С
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
   // m_pTopWgt->setStyleSheet("background-color:#D5E7FF;");
    m_pTopWgt->setStyleSheet("background-color: rgba(255, 255, 255, 0);");//���ñ���͸��
    m_pTopWgt->setFixedHeight(INI_TOP_HEIGHT);
    m_pTopWgt->setGeometry(0, 0, m_rectReport.width(), INI_TOP_HEIGHT);

    QHBoxLayout* pWgthblayout = new QHBoxLayout(m_pTopWgt);
    pWgthblayout->setSpacing(0);

    //��ǩˮƽ����
    QHBoxLayout* pLabHBlayout = new QHBoxLayout(m_pTopWgt);
    pLabHBlayout->setSpacing(0);

    m_plbTitle = new QLabel(m_pTopWgt);
    m_plbTitle->setObjectName("QLabel_title");
    m_plbTitle->setText(QString::fromLocal8Bit("���ܱ���ϵͳ"));
    m_plbTitle->setStyleSheet("QLabel {font-family:Microsoft Yahei; color: blue; font-size: 20px; }");   

    m_plbSysTime = new QLabel(m_pTopWgt);   
    m_plbSysTime->setObjectName("QLabel_systime");
    m_plbSysTime->setStyleSheet("QLabel {font-family:Microsoft Yahei;color: blue; font-size: 20px; }");
    QDateTime current_date_time = QDateTime::currentDateTime();
    //QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    QString current_date = current_date_time.toString("yyyy.MM.dd ddd");
    m_plbSysTime->setText(QString("<%1>").arg(current_date));

    pLabHBlayout->addWidget(m_plbTitle);
    pLabHBlayout->addWidget(m_plbSysTime);
    pWgthblayout->addLayout(pLabHBlayout);

    //ˮƽ���
    QSpacerItem* pHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    pWgthblayout->addItem(pHorizontalSpacer);

    //��ť����
    QHBoxLayout* pBtnHBlayout = new QHBoxLayout(m_pTopWgt);
    pBtnHBlayout->setSpacing(2);

    m_pbtnDay = new QPushButton(m_pTopWgt);
    m_pbtnDay->setObjectName("QPushButton_day");
    m_pbtnDay->setText(QString::fromLocal8Bit("�ձ�"));
    m_pbtnDay->setFixedSize(INT_BUTTON_WIDTH, INT_BUTTON_HEIGHT);
    m_pbtnDay->setStyleSheet("QPushButton {background-color:#f15316; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");

    m_pbtnMonth = new QPushButton(m_pTopWgt);
    m_pbtnMonth->setObjectName("QPushButton_month");
    m_pbtnMonth->setText(QString::fromLocal8Bit("�±�"));
    m_pbtnMonth->setFixedSize(INT_BUTTON_WIDTH, INT_BUTTON_HEIGHT);
    m_pbtnMonth->setStyleSheet("QPushButton { background-color:#c3e9e5; border-radius:10px;font-family:Microsoft Yahei; color: blue; font-size: 15px; }");

    m_pbtnSeason = new QPushButton(m_pTopWgt);
    m_pbtnSeason->setObjectName("QPushButton_season");
    m_pbtnSeason->setText(QString::fromLocal8Bit("����"));
    m_pbtnSeason->setFixedSize(INT_BUTTON_WIDTH, INT_BUTTON_HEIGHT);
    m_pbtnSeason->setStyleSheet("QPushButton { background-color:#c3e9e5; border-radius:10px;font-family:Microsoft Yahei; color: blue; font-size: 15px; }");

    m_pbtnYear = new QPushButton(m_pTopWgt);
    m_pbtnYear->setObjectName("QPushButton_year");
    m_pbtnYear->setText(QString::fromLocal8Bit("�걨"));
    m_pbtnYear->setFixedSize(INT_BUTTON_WIDTH, INT_BUTTON_HEIGHT);
    m_pbtnYear->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");

    m_pbtnMore = new QPushButton(m_pTopWgt);
    m_pbtnMore->setObjectName("QPushButton_more");
    m_pbtnMore->setText(QString::fromLocal8Bit("����"));
    m_pbtnMore->setFixedSize(INT_BUTTON_WIDTH, INT_BUTTON_HEIGHT);
    m_pbtnMore->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");

    pBtnHBlayout->addWidget(m_pbtnDay);
    pBtnHBlayout->addWidget(m_pbtnMonth);
    pBtnHBlayout->addWidget(m_pbtnSeason);
    pBtnHBlayout->addWidget(m_pbtnYear);
    pBtnHBlayout->addWidget(m_pbtnMore);

    m_pbtnMore->hide();

    pWgthblayout->addLayout(pBtnHBlayout);
    m_pTopWgt->setLayout(pWgthblayout);

   bool b =  connect(m_pbtnDay, SIGNAL(clicked(bool)), this, SLOT(slotDayBtnClicked()));
    connect(m_pbtnMonth, SIGNAL(clicked(bool)), this, SLOT(slotMonthBtnClicked()));
    connect(m_pbtnSeason, SIGNAL(clicked(bool)), this, SLOT(slotSeasonBtnClicked()));
    connect(m_pbtnYear, SIGNAL(clicked(bool)), this, SLOT(slotYearBtnClicked()));
    connect(m_pbtnMore, SIGNAL(clicked(bool)), this, SLOT(slotMoreBtnClicked()));
}


void HIntelligentReportWgt::initReportWgt()
{
    m_pReportWgt = new QWidget(this);
    // m_pReportWgt->setStyleSheet("background-color:blue;");
    m_pReportWgt->setGeometry(0, INI_TOP_HEIGHT, m_rectReport.width(), m_rectReport.height() - INI_TOP_HEIGHT);

    /*//����QTableWidgetʵ�ֵ�
    m_pCustomTabWgt = new HCustomTabWgt(m_pReportWgt, m_nRowTab, m_nColumnTab);
    m_pCustomTabWgt->setGeometry(0, 0, m_rectReport.width(), m_rectReport.height() - INI_TOP_HEIGHT);

    QStringList strlst;
    for (int n = 1; n <= 20; n++)
    {
        strlst.append(QString::fromLocal8Bit("ң��%1").arg(n));
    }
    m_pCustomTabWgt->setFrozenHeaderContent(strlst);
    m_pCustomTabWgt->setColumn(strlst.size());
    */

	QRect rect = QRect(0, 0, m_pReportWgt->width(), m_pReportWgt->height());
  //  m_pTabWgt = new ZTableWgt(m_pReportWgt, m_nRowTab, m_nColumnTab);
    m_pTabWgt = new ZTableWgt(m_pReportWgt, m_stTableDataInfo);
    m_pTabWgt->setGeometry(rect);

	bool b = connect(this, SIGNAL(sigDayTableShow()), m_pTabWgt, SLOT(slotDayTableShow()));
	connect(this, SIGNAL(sigMonthTableShow()), m_pTabWgt, SLOT(slotMonthTableShow()));
    connect(this, SIGNAL(sigSeasonTableShow()), m_pTabWgt, SLOT(slotSeasonTableShow()));
	connect(this, SIGNAL(sigYearTableShow()), m_pTabWgt, SLOT(slotYearTableShow()));
}


void HIntelligentReportWgt::slotDayBtnClicked()
{
    m_pbtnDay->setStyleSheet("QPushButton {background-color:#f15316; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
	m_pbtnMonth->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
	m_pbtnYear->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
	m_pbtnSeason->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");

    emit sigDayTableShow();
}

void HIntelligentReportWgt::slotMonthBtnClicked()
{
	m_pbtnMonth->setStyleSheet("QPushButton {background-color:#f15316; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
	m_pbtnDay->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
	m_pbtnYear->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
    m_pbtnSeason->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");

    emit sigMonthTableShow();
}

void HIntelligentReportWgt::slotSeasonBtnClicked()
{
	m_pbtnSeason->setStyleSheet("QPushButton {background-color:#f15316; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
	m_pbtnDay->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
    m_pbtnMonth->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
	m_pbtnYear->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");

	emit sigSeasonTableShow();
}

void HIntelligentReportWgt::slotYearBtnClicked()
{
    m_pbtnYear->setStyleSheet("QPushButton {background-color:#f15316; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
	m_pbtnDay->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
    m_pbtnMonth->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
    m_pbtnSeason->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");

    emit sigYearTableShow();
}


void HIntelligentReportWgt::slotMoreBtnClicked()
{

}