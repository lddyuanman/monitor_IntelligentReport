#include<QDateTime>
#include<QMouseEvent>
#include <QApplication>
#include <QDir>
#include <QFileDialog>
#include <QDesktopServices>
#include <QDesktopWidget>
#include"ZIntelligentReportWgt.h"
#include "GlobalVariable.h"

ZIntelligentReportWgt::ZIntelligentReportWgt(QWidget* parent, stTableData stTableInfo)
    :QWidget(parent), m_stTableDataInfo(stTableInfo)
{
    m_rectReport = QRect(50, 100, 1550, 750);//������m_pTabWgt����ʾ������
    initUI();

    m_nTabType = REPORT_DAY;
    initMenuWgt();
}

ZIntelligentReportWgt::ZIntelligentReportWgt(QWidget* parent, QRect rect, int nrow, int ncolumn)
    : QWidget(parent) , m_rectReport(rect) ,m_nRowTab(nrow) ,m_nColumnTab(ncolumn)
{
    initUI();
}
ZIntelligentReportWgt::~ZIntelligentReportWgt()
{

}

//ʵ�������ק�ƶ�
//void ZIntelligentReportWgt::mousePressEvent(QMouseEvent* event)
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

//void ZIntelligentReportWgt::mouseMoveEvent(QMouseEvent* event)
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

//void ZIntelligentReportWgt::mouseReleaseEvent(QMouseEvent* event)
//{
//    if (event->button() == Qt::LeftButton)
//    {
//        m_bDrag = false;
//    }
//}

//void ZIntelligentReportWgt::wheelEvent(QWheelEvent* event)
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

void ZIntelligentReportWgt::getReportPath(QString &strpath)
{
	QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd ddd");
    QString strType;
    switch (m_nTabType)
    {
    case REPORT_DAY:
        strType = QString::fromLocal8Bit("���ձ���");
        break;
    case REPORT_MONTH:
        strType = QString::fromLocal8Bit("���±���");
        break;
    case REPORT_SECSON:
        strType = QString::fromLocal8Bit("��������");
        break;
    case REPORT_YEAR:
        strType = QString::fromLocal8Bit("���걨��");
        break;
    default:
        break;
    }
    QString strName = m_plbTitle->text();

    QString str = QDir::currentPath();
    strpath = QString("%1/export/reports/%2%3(%4).xls").arg(str).arg(strName).arg(strType).arg(current_date);
}

void ZIntelligentReportWgt::setData(QMap<QString, QStringList>  mapdata)
{
    m_pTabWgt->setTabData(mapdata);
}

void ZIntelligentReportWgt::setTableData()
{
    m_pTabWgt->updateData();
}

void ZIntelligentReportWgt::initUI()
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

void ZIntelligentReportWgt::initTopWgt()
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


void ZIntelligentReportWgt::initReportWgt()
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

	connect(this, SIGNAL(sigDayTableShow()), m_pTabWgt, SLOT(slotDayTableShow()));
	connect(this, SIGNAL(sigMonthTableShow()), m_pTabWgt, SLOT(slotMonthTableShow()));
    connect(this, SIGNAL(sigSeasonTableShow()), m_pTabWgt, SLOT(slotSeasonTableShow()));
	connect(this, SIGNAL(sigYearTableShow()), m_pTabWgt, SLOT(slotYearTableShow()));
  
    bool bnet = connect(m_pTabWgt, &ZTableWgt::sigTableData, this, &ZIntelligentReportWgt::slotGetReportData);

}

void ZIntelligentReportWgt::initMenuWgt()
{
	m_pMenu = new QMenu(this);    //�˵���ʼ��
	m_pMenu->setStyleSheet("background-color:#1a1a1a;color:#fff;");    //���ò˵���ʽ������ɫ

	//���ò˵���
	QAction* pSetDate = new QAction(u8"��������", this);
	QAction* pSetAttribute = new QAction(u8"��������", this);
	QAction* pExportTable = new QAction(u8"��������", this);
	QAction* pOpenDirectory = new QAction(u8"�򿪱���Ŀ¼", this);

	//���˵������˵�
	m_pMenu->addAction(pSetDate);
	//pSetDate->setIcon(QIcon(":/new/prefix1/icon/205����.png"));    //���ò˵�ͼ��
	pSetDate->setIconVisibleInMenu(true);       //ͼ������Ϊ�ɼ�
	m_pMenu->addSeparator();  //���ò˵���֮��ķָ���

	//���������÷�����ͬ
	m_pMenu->addAction(pSetAttribute);
	//pSetAttribute->setIcon(QIcon(":/new/prefix1/icon/����.png"));
	pSetAttribute->setIconVisibleInMenu(true);
	m_pMenu->addSeparator();
	m_pMenu->addAction(pExportTable);
	//pExportTable->setIcon(QIcon(":/new/prefix1/icon/ͨѶ¼.png"));
	pExportTable->setIconVisibleInMenu(true);
	m_pMenu->addSeparator();
	m_pMenu->addAction(pOpenDirectory);
	//pOpenDirectory->setIcon(QIcon(":/new/prefix1/icon/��Ⱥ.png"));
	pOpenDirectory->setIconVisibleInMenu(true);

    m_pSetDateWgt = new ZSetDateWgt(this);
    m_pSetDateWgt->resize(INI_SETDATEWGT_WIDTH, INI_SETDATEWGT_HEIGHT);
    m_pSetDateWgt->setGeometry((this->width() - INI_SETDATEWGT_WIDTH )/ 2, (this->height() - INI_SETDATEWGT_HEIGHT ) / 2, INI_SETDATEWGT_WIDTH, INI_SETDATEWGT_HEIGHT);
	
    m_pExportWgt = new ZExportReportWgt(this);
    m_pExportWgt->resize(INI_EXPORT_WGT_WIDTH, INI_EXPORT_WGT_HEIGHT);
    m_pExportWgt->setGeometry((this->width() - INI_EXPORT_WGT_WIDTH) / 2, (this->height() - INI_EXPORT_WGT_HEIGHT) / 2, INI_EXPORT_WGT_WIDTH, INI_EXPORT_WGT_HEIGHT);

    //�˵��ť�����ۺ���
	//console* con = new console;    //��ʼ��Ҫ���ӵ���ģ��
	connect(pSetDate, &QAction::triggered, m_pSetDateWgt, &ZSetDateWgt::slotShowSetDateWgt);
	bool b1 = connect(pExportTable, &QAction::triggered, m_pExportWgt, &ZExportReportWgt::slotShowExportWgt);
    connect(m_pExportWgt, SIGNAL(sigOpenReport()), m_pTabWgt, SLOT(sltOpenReport()));

    connect(pOpenDirectory, &QAction::triggered, this, &ZIntelligentReportWgt::slotOpenDirectory);

	//������Ҽ�����ĵط���ʾ�˵�
    m_pTabWgt->setContextMenuPolicy(Qt::CustomContextMenu);//�����һ��˵�
	bool b = connect(m_pTabWgt, &QTableWidget::customContextMenuRequested, this, &ZIntelligentReportWgt::slotShowMenu);

}

void ZIntelligentReportWgt::slotShowMenu(QPoint pos)
{
	QTableWidgetItem* selectedItem = m_pTabWgt->itemAt(pos); //��ȡ�һ���item
    /*if (nullptr == selectedItem)
	{
		return;
	}*/

	m_pMenu->popup(m_pTabWgt->viewport()->mapToGlobal(pos));//���˵���ʾ���������λ��

    QString strPath;
    getReportPath(strPath);
    m_pExportWgt->setReportPath(strPath);

    m_pTabWgt->setReportFullPath(strPath);
}

void ZIntelligentReportWgt::slotOpenDirectory()
{
	QString strPath;
	getReportPath(strPath);

	QFileInfo fileInfo(strPath);
	QFileDialog* pFilename = new QFileDialog(m_pTabWgt, Qt::Dialog);
    pFilename->setGeometry((QApplication::desktop()->width() - 800 )/2,(QApplication::desktop()->height() - 480)/2,800, 480);
	pFilename->setDirectory(fileInfo.absolutePath());//���ô򿪵�Ĭ��Ŀ¼
	pFilename->setNameFilter(tr("exe(*.xls)"));//�����޶��ļ�����
	//pFilename->setOption(QFileDialog::DontResolveSymlinks);//���Լ�������·����������ת

	if (pFilename->exec() != QFileDialog::Accepted)
	{
		return;
	}

	QString strFileName = pFilename->selectedFiles().first();

	delete pFilename;

	if (strFileName.isEmpty())
	{
		//QMessageBox::information(this, "Error Message", "No File Selected");
		return;
	}
    QDesktopServices::openUrl(QUrl::fromLocalFile(strFileName));

   /* QString strFileName = QFileDialog::getOpenFileName(this, "Open File", fileInfo.path(),
        tr("exe(*.xls)"), 0, QFileDialog::DontResolveSymlinks);*/
    /* ���ϣ������Ϊthis����������Ϊ"Open File"��
      ""��"."����Ĭ�ϴ򿪹���Ŀ¼��
      "exe(*.exe)"����ֻ����ѡ��exe���͵��ļ���
      ���ĸ��������Բ�д������Ϊ�����õ����������������Ϊ0��
      �����������QFileDialog::DontResolveSymlinks��������Ϊ��ʹѡ�е��ļ�Ϊ��ݷ�ʽ�����ӣ�·��Ҳֻ��ʾ����·����������ת��QFileDialog::ShowDirsOnly��ʾֻ��ʾ�ļ��У�*/

    //strFileName = QDir::toNativeSeparators(strFileName);//Linuxб��תWindows��б��
}

void ZIntelligentReportWgt::slotGetReportData(QMap<QString, QStringList>& mapdata, ReportType type)
{
    emit sigGetReportData(mapdata,type);
    m_pTabWgt->setTabData(mapdata);
}

void ZIntelligentReportWgt::slotDayBtnClicked()
{
    m_pbtnDay->setStyleSheet("QPushButton {background-color:#f15316; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
	m_pbtnMonth->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
	m_pbtnYear->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
	m_pbtnSeason->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
   
    m_nTabType = REPORT_DAY;

    emit sigDayTableShow();
}

void ZIntelligentReportWgt::slotMonthBtnClicked()
{
	m_pbtnMonth->setStyleSheet("QPushButton {background-color:#f15316; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
	m_pbtnDay->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
	m_pbtnYear->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
    m_pbtnSeason->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");

    m_nTabType = REPORT_MONTH;

    emit sigMonthTableShow();
}

void ZIntelligentReportWgt::slotSeasonBtnClicked()
{
	m_pbtnSeason->setStyleSheet("QPushButton {background-color:#f15316; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
	m_pbtnDay->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
    m_pbtnMonth->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
	m_pbtnYear->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");

    m_nTabType = REPORT_SECSON;

	emit sigSeasonTableShow();
}

void ZIntelligentReportWgt::slotYearBtnClicked()
{
    m_pbtnYear->setStyleSheet("QPushButton {background-color:#f15316; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
	m_pbtnDay->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
    m_pbtnMonth->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");
    m_pbtnSeason->setStyleSheet("QPushButton {background-color:#c3e9e5; border-radius:10px; font-family:Microsoft Yahei; color: blue; font-size: 15px; }");

    m_nTabType = REPORT_YEAR;

    emit sigYearTableShow();
}


void ZIntelligentReportWgt::slotMoreBtnClicked()
{

}