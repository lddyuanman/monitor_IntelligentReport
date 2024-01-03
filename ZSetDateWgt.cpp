#include"ZSetDateWgt.h"
#include <QLabel>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QDateTime>
#include <QCoreApplication>

ZSetDateWgt::ZSetDateWgt(QWidget* parent)
	: QWidget(parent)
{
	initUI();
	initCalendarWgt();
}
ZSetDateWgt::~ZSetDateWgt()
{
	if (m_pCalendarWgt != NULL)
	{
		delete m_pCalendarWgt;
	}
}

//ʵ�������ק�ƶ�
void ZSetDateWgt::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton )
    {
		m_pCalendarWgt->hide();
    }
}

void ZSetDateWgt::initUI()
{
	//this->setAttribute(Qt::WA_TranslucentBackground);//���ô��ڱ���͸��
	//this->setWindowFlags(Qt::FramelessWindowHint);   //�����ޱ߿򴰿�
	//�Ӵ�����ʾ��ȫ���⣬newһ��ͬ����С���Ӵ���
	QWidget* pSetDateWgt = new QWidget(this);
	pSetDateWgt->resize(INI_SETDATEWGT_WIDTH, INI_SETDATEWGT_HEIGHT);
	pSetDateWgt->setStyleSheet("background-color:#addfff;border-radius:5px;");

    //���ⴰ��
	QWidget* pTitleWgt = new QWidget(pSetDateWgt);
	pTitleWgt->setFixedHeight(INI_SETDATEWGT_TITLE_HEIGHT);
	pTitleWgt->setGeometry(0, 0, INI_SETDATEWGT_WIDTH, INI_SETDATEWGT_TITLE_HEIGHT);
	pTitleWgt->setStyleSheet("background-color:#fdfcfd;");

	QLabel* pLaTitle = new QLabel(pTitleWgt);
	pLaTitle->setText(QString::fromLocal8Bit("��ʷ��������ʱ������"));
	pLaTitle->setStyleSheet("QLabel {font-family:Microsoft Yahei;color: black; font-size: 15px; }");
		
	QHBoxLayout* pTitlehblayout = new QHBoxLayout();
	pTitlehblayout->setSpacing(0);
	
	QSpacerItem* pHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	
	m_pBtnClose = new QPushButton(pTitleWgt);    
	m_pBtnClose->setStyleSheet("QPushButton {background-color:#fdfcfd; border-radius:5px; font-family:Microsoft Yahei; color: black; font-size: 15px; text-align:content;}");
	m_pBtnClose->setText(QString::fromLocal8Bit("�ر�"));
	
	pTitlehblayout->addWidget(pLaTitle);
	pTitlehblayout->addItem(pHorizontalSpacer);
	pTitlehblayout->addWidget(m_pBtnClose);
	pTitleWgt->setLayout(pTitlehblayout);

	//���ڿؼ���ʾ����
	QWidget* pDateWgt = new QWidget(pSetDateWgt);
	pDateWgt->setFixedSize(INI_SETDATEWGT_WIDTH - 20, INI_SETDATEWGT_DATE_HEIGHT);
	pDateWgt->setGeometry(10, 50, INI_SETDATEWGT_WIDTH - 20, INI_SETDATEWGT_DATE_HEIGHT);
	pDateWgt->setStyleSheet(QString::fromUtf8("border:1px solid #fdfcfd"));

	QVBoxLayout* pDateVbl = new QVBoxLayout();
	pDateVbl->setSpacing(10);

	QHBoxLayout* pdateTimeHbl = new QHBoxLayout();
	pdateTimeHbl->setSpacing(0);

	m_pDateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime(), pDateWgt);
	m_pDateTimeEdit->setFixedHeight(INI_SETDATEWGT_LINEEDIT_HEIGHT);
	m_pDateTimeEdit->setFixedWidth(INI_SETDATEWGT_WIDTH - 120);
	//m_pDateTimeEdit->setGeometry(130, 10, INI_SETDATEWGT_WIDTH - 120, INI_SETDATEWGT_LINEEDIT_HEIGHT);
	m_pDateTimeEdit->setGeometry(130, 10, INI_SETDATEWGT_WIDTH - 120, INI_SETDATEWGT_LINEEDIT_HEIGHT);
	QString strqssDate = QString("QDateTimeEdit{border:0.5px white; border-radius:5px; background-color:rgba(255, 255, 255, 1); \
                               color:black; font-size:18px; font-family:Microsoft Yahei;}\
                               QDateTimeEdit::drop-down{border:none; width:20px;}");
	m_pDateTimeEdit->setStyleSheet(strqssDate);
	m_pDateTimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
	/*QDateTimeEdit
		{
	   border:none;
	   border - radius:10px;
	   background - color:rgba(8, 55, 132, 1);
	   color:white;
	   font - size:18px;
	   padding:10px 40px 10px 40px;
		}
			QDateTimeEdit::up - arrow
		{
				image: url(: / res / dlg / up - button.png);
		}
			QDateTimeEdit::down - arrow
		{
			   image: url(: / res / dlg / dropArrow.png);
		}*/

	m_pBtnDateTime = new QPushButton(pDateWgt);
	m_pBtnDateTime->setFixedHeight(INI_SETDATEWGT_LINEEDIT_HEIGHT - 5);
	m_pBtnDateTime->setFixedWidth(INI_SETDATEWGT_LINEEDIT_HEIGHT - 5);
	//m_pBtnDateTime->setText(QString::fromLocal8Bit("����"));
	QString imgPathStr = ":/MonitorSys/images/date.png";
	QString current_path = QCoreApplication::applicationDirPath(); // ����ͼƬ�ļ�·��
	QString styleSheet = QString("%1/../MonitorSys/images/date.png").arg(current_path);
    m_pBtnDateTime->setStyleSheet(QString("QPushButton{border-image:url(%1);}").arg(styleSheet));

	pdateTimeHbl->addWidget(m_pDateTimeEdit);
	pdateTimeHbl->addWidget(m_pBtnDateTime);

	QHBoxLayout* pYearhblayout = new QHBoxLayout();
	pYearhblayout->setSpacing(0);

	QPushButton* pBtnLastYear = new QPushButton(pDateWgt);
	pBtnLastYear->setFixedSize(INI_SETDATEWGT_BTN_WIDTH, INI_SETDATEWGT_BTN_HEIGHT);
	pBtnLastYear->setText(QString::fromLocal8Bit("��һ��"));
	QString strqss = QString("QPushButton {background-color:#37c5f8; border:0px solid red; border-radius:5px; font-family:Microsoft Yahei; color: black; font-size: 15px; text-align:content;}"\
	                         "QPushButton:hover{background-color:#2c83e9; border:0px solid red; border-radius:5px; font-family:Microsoft Yahei; color: black; font-size: 15px; text-align:content;}");
	pBtnLastYear->setStyleSheet(strqss);

	QPushButton* pBtnNextYear = new QPushButton(pDateWgt);
	pBtnNextYear->setFixedSize(INI_SETDATEWGT_BTN_WIDTH, INI_SETDATEWGT_BTN_HEIGHT);
	pBtnNextYear->setText(QString::fromLocal8Bit("��һ��"));
	pBtnNextYear->setStyleSheet(strqss);

	QPushButton* pBtnHalfYear = new QPushButton(pDateWgt);
	pBtnHalfYear->setFixedSize(INI_SETDATEWGT_BTN_WIDTH, INI_SETDATEWGT_BTN_HEIGHT);
	pBtnHalfYear->setText(QString::fromLocal8Bit("�����"));
	pBtnHalfYear->setStyleSheet(strqss);

	pYearhblayout->addWidget(pBtnLastYear);
	pYearhblayout->addWidget(pBtnNextYear);
	pYearhblayout->addWidget(pBtnHalfYear);

	QHBoxLayout* pMonthhblayout = new QHBoxLayout();
	pMonthhblayout->setSpacing(0);

	QPushButton* pBtnLastMonth = new QPushButton(pDateWgt);
	pBtnLastMonth->setFixedSize(INI_SETDATEWGT_BTN_WIDTH, INI_SETDATEWGT_BTN_HEIGHT);
	pBtnLastMonth->setText(QString::fromLocal8Bit("��һ��"));
	pBtnLastMonth->setStyleSheet(strqss);

	QPushButton* pBtnNextMonth = new QPushButton(pDateWgt);
	pBtnNextMonth->setFixedSize(INI_SETDATEWGT_BTN_WIDTH, INI_SETDATEWGT_BTN_HEIGHT);
	pBtnNextMonth->setText(QString::fromLocal8Bit("��һ��"));
	pBtnNextMonth->setStyleSheet(strqss);

	QPushButton* pBtnHalfMonth = new QPushButton(pDateWgt);
	pBtnHalfMonth->setFixedSize(INI_SETDATEWGT_BTN_WIDTH, INI_SETDATEWGT_BTN_HEIGHT);
	pBtnHalfMonth->setText(QString::fromLocal8Bit("���º�"));
	pBtnHalfMonth->setStyleSheet(strqss);

	pMonthhblayout->addWidget(pBtnLastMonth);
	pMonthhblayout->addWidget(pBtnNextMonth);
	pMonthhblayout->addWidget(pBtnHalfMonth);

	QHBoxLayout* pDayhblayout = new QHBoxLayout();
	pDayhblayout->setSpacing(0);

	QPushButton* pBtnLastDay = new QPushButton(pDateWgt);
	pBtnLastDay->setFixedSize(INI_SETDATEWGT_BTN_WIDTH, INI_SETDATEWGT_BTN_HEIGHT);
	pBtnLastDay->setText(QString::fromLocal8Bit("��һ��"));
	pBtnLastDay->setStyleSheet(strqss);

	QPushButton* pBtnNextDay = new QPushButton(pDateWgt);
	pBtnNextDay->setFixedSize(INI_SETDATEWGT_BTN_WIDTH, INI_SETDATEWGT_BTN_HEIGHT);
	pBtnNextDay->setText(QString::fromLocal8Bit("��һ��"));
	pBtnNextDay->setStyleSheet(strqss);

	QPushButton* pBtnToday = new QPushButton(pDateWgt);
	pBtnToday->setFixedSize(INI_SETDATEWGT_BTN_WIDTH, INI_SETDATEWGT_BTN_HEIGHT);
	pBtnToday->setText(QString::fromLocal8Bit("��  ��"));
	pBtnToday->setStyleSheet(strqss);

	pDayhblayout->addWidget(pBtnLastDay);
	pDayhblayout->addWidget(pBtnNextDay);
	pDayhblayout->addWidget(pBtnToday);

	pDateVbl->addLayout(pdateTimeHbl);
	pDateVbl->addLayout(pYearhblayout);	
	pDateVbl->addLayout(pMonthhblayout);
	pDateVbl->addLayout(pDayhblayout);
	pDateWgt->setLayout(pDateVbl);
	
	//������ʾ����
	QWidget* pInfoWgt = new QWidget(pSetDateWgt);
	pInfoWgt->setFixedSize(INI_SETDATEWGT_WIDTH - 20, INI_SETDATEWGT_INFO_HEIGHT);
	pInfoWgt->setGeometry(10, 245, INI_SETDATEWGT_WIDTH - 20, INI_SETDATEWGT_INFO_HEIGHT);
	//pInfoWgt->setStyleSheet("background-color:#fdfcfd;");

	QVBoxLayout* plbVbl = new QVBoxLayout();
	plbVbl->setSpacing(0);

	QLabel* plbInfo = new QLabel(pInfoWgt);
	plbInfo->setText(QString::fromLocal8Bit("������ʷ��������֮�󣬺�̨���л������ʷ���ݰ���������ʱ��ȡֵ�������ڻ��ڵ��챣�ֲ��䣬ֱ���������Զ������Ϊ��������ڡ�������ȡֵΪ�ۼ���ֵʱ����ʱ����ʱ�̾�����Ӱ��ȡֵ��������ȡֵΪ��ʷֵ��δָ��ʱ�̣���Ӵ˴����õ�ʱ��ȡֵ��"));
	plbInfo->setStyleSheet("QLabel { font-family:Microsoft Yahei; color: black; font-size: 12px;}");
	plbInfo->setWordWrap(true);//�����Զ�����

	QHBoxLayout* pbtnHbl = new QHBoxLayout();
	pbtnHbl->setSpacing(0);

	QPushButton* pBtnUse = new QPushButton(pInfoWgt);
	pBtnUse->setFixedSize(INI_SETDATEWGT_BTN_WIDTH, INI_SETDATEWGT_BTN_HEIGHT);
	pBtnUse->setText(QString::fromLocal8Bit("Ӧ  ��"));
	pBtnUse->setStyleSheet(strqss);

	QPushButton* pBtnSure = new QPushButton(pInfoWgt);
	pBtnSure->setFixedSize(INI_SETDATEWGT_BTN_WIDTH, INI_SETDATEWGT_BTN_HEIGHT);
	pBtnSure->setText(QString::fromLocal8Bit("ȷ  ��"));
	pBtnSure->setStyleSheet(strqss);

	QPushButton* pBtnCancel = new QPushButton(pInfoWgt);
	pBtnCancel->setFixedSize(INI_SETDATEWGT_BTN_WIDTH, INI_SETDATEWGT_BTN_HEIGHT);
	pBtnCancel->setText(QString::fromLocal8Bit("ȡ  ��"));
	pBtnCancel->setStyleSheet(strqss);

	pbtnHbl->addWidget(pBtnUse);
	pbtnHbl->addWidget(pBtnSure);
	pbtnHbl->addWidget(pBtnCancel);

	plbVbl->addWidget(plbInfo);
	plbVbl->addLayout(pbtnHbl);
	pInfoWgt->setLayout(plbVbl);

	connect(pBtnCancel, SIGNAL(clicked(bool)), this, SLOT(slotCancelBtnClicked()));
	connect(m_pBtnClose, SIGNAL(clicked(bool)), this, SLOT(sloCloseBtnClicked()));

	connect(m_pBtnDateTime, SIGNAL(clicked(bool)), this, SLOT(slotDateBtnClicked()));
	connect(pBtnLastYear, SIGNAL(clicked(bool)), this, SLOT(slotLastYearBtnClicked()));
	connect(pBtnNextYear, SIGNAL(clicked(bool)), this, SLOT(slotNextYearBtnClicked()));
	connect(pBtnHalfYear, SIGNAL(clicked(bool)), this, SLOT(slotHalfYearBtnClicked()));

	connect(pBtnLastMonth, SIGNAL(clicked(bool)), this, SLOT(slotLastMonthBtnClicked()));
	connect(pBtnNextMonth, SIGNAL(clicked(bool)), this, SLOT(slotNextMonthBtnClicked()));
	connect(pBtnHalfMonth, SIGNAL(clicked(bool)), this, SLOT(slotHalfMonthBtnClicked()));

	connect(pBtnLastDay, SIGNAL(clicked(bool)), this, SLOT(slotLastDayBtnClicked()));
	connect(pBtnNextDay, SIGNAL(clicked(bool)), this, SLOT(slotNextDayBtnClicked()));
	connect(pBtnToday, SIGNAL(clicked(bool)), this, SLOT(slotTodayBtnClicked()));

	hide();	
}

void ZSetDateWgt::initCalendarWgt()
{
	m_pCalendarWgt = new QCalendarWidget(this);
	m_pCalendarWgt->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
	m_pCalendarWgt->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);
	m_pCalendarWgt->setGridVisible(true);//��ʾ������
	m_pCalendarWgt->adjustSize();
	m_pCalendarWgt->raise();
		
	QString strqssedit = QString("QCalendarWidget QWidget{ background-color:rgb(44, 131, 233); }");
	m_pCalendarWgt->setStyleSheet(strqssedit);

	connect(m_pCalendarWgt, &QCalendarWidget::activated, this, [=](QDate date) {
		m_pDateTimeEdit->setDate(date);
		//m_pCalendarWgt->close();
		//delete m_pCalendarWgt;
		m_pCalendarWgt->hide();
		});

	m_pCalendarWgt->hide();
}

void ZSetDateWgt::slotShowSetDateWgt()
{
	show();
}

void ZSetDateWgt::slotCancelBtnClicked()
{
	if (m_pCalendarWgt != NULL)
	{
		m_pCalendarWgt->hide();
	}

	close();
}

void ZSetDateWgt::sloCloseBtnClicked()
{
	if (m_pCalendarWgt != NULL)
	{
		m_pCalendarWgt->hide();
	}
	close();
}

void ZSetDateWgt::slotDateBtnClicked()
{
	QDate date = QDateTime::currentDateTime().date();
	m_pCalendarWgt->setSelectedDate(date);

	QPoint pos = m_pBtnDateTime->pos();
	m_pCalendarWgt->move(pos.x() - 180 , pos.y() + 100 );
	m_pCalendarWgt->show();
}

void ZSetDateWgt::slotLastYearBtnClicked()
{
	QDate date = m_pDateTimeEdit->date().addYears(-1);
	m_pDateTimeEdit->setDate(date);
}

void ZSetDateWgt::slotNextYearBtnClicked()
{
	QDate date = m_pDateTimeEdit->date().addYears(1);
	m_pDateTimeEdit->setDate(date);
}

void ZSetDateWgt::slotHalfYearBtnClicked()
{
	QDate date = m_pDateTimeEdit->date().addMonths(6);
	m_pDateTimeEdit->setDate(date);
}

void ZSetDateWgt::slotLastMonthBtnClicked()
{
	QDate date = m_pDateTimeEdit->date().addMonths(-1);
	m_pDateTimeEdit->setDate(date);
}

void ZSetDateWgt::slotNextMonthBtnClicked()
{
	QDate date = m_pDateTimeEdit->date().addMonths(1);
	m_pDateTimeEdit->setDate(date);
}

void ZSetDateWgt::slotHalfMonthBtnClicked()
{
	QDate date = m_pDateTimeEdit->date().addDays(15);
	m_pDateTimeEdit->setDate(date);
}

void ZSetDateWgt::slotLastDayBtnClicked()
{
	QDate date = m_pDateTimeEdit->date().addDays(-1);
	m_pDateTimeEdit->setDate(date);
}

void ZSetDateWgt::slotNextDayBtnClicked()
{
	QDate date = m_pDateTimeEdit->date().addDays(1);
	m_pDateTimeEdit->setDate(date);
}

void ZSetDateWgt::slotTodayBtnClicked()
{
	QDate date = QDateTime::currentDateTime().date();
	m_pDateTimeEdit->setDate(date);
}

void ZSetDateWgt::slotUseBtnClicked()
{
	//Ӧ�ù���
}

void ZSetDateWgt::slotSureBtnClicked()
{
	//ȷ��
}
