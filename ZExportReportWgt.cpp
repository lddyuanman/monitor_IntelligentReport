#include"ZExportReportWgt.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QCoreApplication>

ZExportReportWgt::ZExportReportWgt(QWidget* parent)
	: QWidget(parent)
{
	initUI();
}
ZExportReportWgt::~ZExportReportWgt()
{

}

void ZExportReportWgt::initUI()
{
	QWidget* pEXportWgt = new QWidget(this);
	pEXportWgt->resize(INI_EXPORT_WGT_WIDTH, INI_EXPORT_WGT_HEIGHT);
	pEXportWgt->setStyleSheet("background-color:#eeeae3;border-radius:5px;");

	//标题窗口
	QWidget* pTitleWgt = new QWidget(pEXportWgt);
	pTitleWgt->setFixedHeight(INI_EXPORT_WGT_TITLE_HEIGHT);
	pTitleWgt->setGeometry(0, 0, INI_EXPORT_WGT_WIDTH, INI_EXPORT_WGT_TITLE_HEIGHT);
	pTitleWgt->setStyleSheet("background-color:#fdfcfd;");

	QLabel* pLaTitle = new QLabel(pTitleWgt);
	pLaTitle->setText(QString::fromLocal8Bit("报表导出"));
	pLaTitle->setStyleSheet("QLabel {font-family:Microsoft Yahei;color: black; font-size: 15px; }");

	QHBoxLayout* pTitlehblayout = new QHBoxLayout();
	pTitlehblayout->setSpacing(0);

	QSpacerItem* pHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

	QPushButton* pBtnClose = new QPushButton(pTitleWgt);
	pBtnClose->setStyleSheet("QPushButton {background-color:#fdfcfd; border-radius:5px; font-family:Microsoft Yahei; color: black; font-size: 15px; text-align:content;}");
	pBtnClose->setText(QString::fromLocal8Bit("关闭"));

	pTitlehblayout->addWidget(pLaTitle);
	pTitlehblayout->addItem(pHorizontalSpacer);
	pTitlehblayout->addWidget(pBtnClose);
	pTitleWgt->setLayout(pTitlehblayout);

	//确认信息
	QWidget* pHintWgt = new QWidget(pEXportWgt);
	pHintWgt->setFixedSize(INI_EXPORT_HINT_WGT_WIDTH, INI_EXPORT_HINT_WGT_HEIGHT);
	pHintWgt->setGeometry(25, 40, INI_EXPORT_HINT_WGT_WIDTH, INI_EXPORT_HINT_WGT_HEIGHT);
	//pHintWgt->setStyleSheet("background-color:blue;");

	QVBoxLayout* pvblHint = new QVBoxLayout();
	pvblHint->setSpacing(0);

	QLabel* plbHint = new QLabel(pHintWgt);
	plbHint->setText(QString::fromLocal8Bit("报表已导出到："));
	plbHint->setFixedHeight(INI_EXPORT_HINT_LABEL_HEIGHT);
	plbHint->setStyleSheet("QLabel {font-family:Microsoft Yahei;color: black; font-size: 13px; }");

	QLabel* plbline1 = new QLabel(pHintWgt);
	plbline1->setText(QString::fromLocal8Bit("- - - - - - - - - - - - - - - - - - - -"));
	plbline1->setFixedHeight(1);

	m_plbDirectory = new QLabel(pHintWgt);
	m_plbDirectory->setFixedSize(INI_EXPORT_HINT_WGT_WIDTH, INI_EXPORT_HINT_WGT_HEIGHT - 80);
	m_plbDirectory->setWordWrap(true);//设置自动换行
	m_plbDirectory->setAlignment(Qt::AlignVCenter );
	//QString strdirPath = QCoreApplication::applicationDirPath();
	//m_plbDirectory->setText(QString::fromLocal8Bit("%1/../MonitorSys/export/reports/").arg(strdirPath));
	m_plbDirectory->setStyleSheet("QLabel {font-family:Microsoft Yahei;color: black; font-size: 13px; }");

	QLabel* plbline2 = new QLabel(pHintWgt);
	plbline2->setText(QString::fromLocal8Bit("- - - - - - - - - - - - - - - - - - - -"));
	plbline2->setFixedHeight(1);

	QLabel* plbHint2 = new QLabel(pHintWgt);
	plbHint2->setText(QString::fromLocal8Bit("是否需要打开报表？"));
	plbHint2->setFixedHeight(INI_EXPORT_HINT_LABEL_HEIGHT);
	plbHint2->setStyleSheet("QLabel {font-family:Microsoft Yahei;color: black; font-size: 13px; }");

	pvblHint->addWidget(plbHint);
	pvblHint->addWidget(plbline1);
	pvblHint->addWidget(m_plbDirectory);
	pvblHint->addWidget(plbline2);
	pvblHint->addWidget(plbHint2);
	pHintWgt->setLayout(pvblHint);

	QPushButton* pbtnOK = new QPushButton(pEXportWgt);
	pbtnOK->setFixedSize(INI_EXPORT_BTN_WIDTH, INI_EXPORT_BTN_HEIGHT);
	pbtnOK->setText(QString::fromLocal8Bit("确 定"));
	pbtnOK->setGeometry(290, 200, INI_EXPORT_BTN_WIDTH,INI_EXPORT_BTN_HEIGHT);
	QString strqss = QString("QPushButton {background-color:#bfd6e8; border:0px solid red; border-radius:5px; font-family:Microsoft Yahei; color: black; font-size: 15px; text-align:content;}"\
		"QPushButton:hover{background-color:#fcf5f7; border:0px solid red; border-radius:5px; font-family:Microsoft Yahei; color: black; font-size: 15px; text-align:content;}");
	pbtnOK->setStyleSheet(strqss);
	
	QPushButton* pbtnCancel = new QPushButton(pEXportWgt);
	pbtnCancel->setFixedSize(INI_EXPORT_BTN_WIDTH,INI_EXPORT_BTN_HEIGHT);
	pbtnCancel->setText(QString::fromLocal8Bit("取 消"));
	pbtnCancel->setGeometry(360, 200, INI_EXPORT_BTN_WIDTH, INI_EXPORT_BTN_HEIGHT);
	pbtnCancel->setStyleSheet(strqss);

	connect(pBtnClose, SIGNAL(clicked(bool)), this, SLOT(sloCloseBtnClicked()));
	connect(pbtnCancel, SIGNAL(clicked(bool)), this, SLOT(sloCancelBtnClicked()));
	connect(pbtnOK, SIGNAL(clicked(bool)), this, SLOT(sloOkBtnClicked()));

	hide();
}

void ZExportReportWgt::setReportPath(QString strpath)
{
	m_plbDirectory->setText(strpath);
}

void ZExportReportWgt::sloOkBtnClicked()
{
	hide();

	//打开报表
	emit sigOpenReport();
}

void ZExportReportWgt::slotShowExportWgt()
{
	show();
}

void ZExportReportWgt::sloCloseBtnClicked()
{
	hide();
}

void ZExportReportWgt::sloCancelBtnClicked()
{
	close();
}