#include"ZTitleWgt.h"
#include "HGlobalVariable.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>

ZMonSysTitleWgt::ZMonSysTitleWgt(QWidget* parent, int nWidth)
    : QWidget(parent) , m_nWgtWidth(nWidth)
{
    m_bMaxFlag = true;
    initUI();
}

ZMonSysTitleWgt::~ZMonSysTitleWgt()
{
    if (m_pWndTitle != NULL)
    {
        delete m_pWndTitle;
    }
}

void ZMonSysTitleWgt::initUI()
{
   this->setStyleSheet("background-color:#FCFCFC;");
   // this->setStyleSheet("background-color:#D5E7FF;");

    m_pWndTitle = new QWidget(this);
    m_pWndTitle->setFixedHeight(INI_TITLE_HEIGHT);
    m_pWndTitle->setGeometry(QRect(0, 0, m_nWgtWidth, INI_TITLE_HEIGHT));

    QHBoxLayout* pWgtHBlayout = new QHBoxLayout(m_pWndTitle);
    pWgtHBlayout->setSpacing(6);
    pWgtHBlayout->setContentsMargins(11, 11, 11, 11);
    pWgtHBlayout->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    pWgtHBlayout->setContentsMargins(0, 0, 0, 0);

    //标签水平布局
    QHBoxLayout* pLabHBlayout = new QHBoxLayout(m_pWndTitle);
    pLabHBlayout->setSpacing(6);

    QLabel* pLabIcon = new QLabel(m_pWndTitle);
    pLabIcon->setText("Icon");
    pLabIcon->setStyleSheet("QLabel { color: black; font-size: 20px; }");
    pLabIcon->setFixedHeight(INI_LABEL_HEIGHT);
    pLabIcon->setFixedWidth(INT_LABWIDTH);

    QLabel* ppLabName = new QLabel(m_pWndTitle);
    ppLabName->setText("MonitorSys");
    ppLabName->setStyleSheet("QLabel { color: black; font-size: 20px; }");
    ppLabName->setFixedHeight(INI_LABEL_HEIGHT);
    ppLabName->setFixedWidth(INT_NAMEWIDTH);
    
    pLabHBlayout->addWidget(pLabIcon);
    pLabHBlayout->addWidget(ppLabName);
    pWgtHBlayout->addLayout(pLabHBlayout);

    //水平间隔
    QSpacerItem* pHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    pWgtHBlayout->addItem(pHorizontalSpacer);

    //按钮布局
    QHBoxLayout* pBtnHBlayout = new QHBoxLayout(m_pWndTitle);
    pBtnHBlayout->setSpacing(6);
    
    QPushButton* m_pbtnDay = new QPushButton(m_pWndTitle);
    m_pbtnDay->setObjectName(QString::fromUtf8("minPushButton"));
    m_pbtnDay->setText(QString::fromLocal8Bit("最小化"));
    m_pbtnDay->setFixedSize(INT_BTNWIDTH, INT_BTNHEIGHT);
    m_pbtnDay->setStyleSheet("QPushButton {background-color:#FCFCFC; border-radius:5px; font-family:Microsoft Yahei; color: black; font-size: 15px; }");


    m_pbtnMonth = new QPushButton(m_pWndTitle);
    m_pbtnMonth->setObjectName(QString::fromUtf8("maxPushButton"));
    m_pbtnMonth->setText(QString::fromLocal8Bit("还原"));
    m_pbtnMonth->setFixedSize(INT_BTNWIDTH, INT_BTNHEIGHT);
    m_pbtnMonth->setStyleSheet("QPushButton {background-color:#FCFCFC; border-radius:5px; font-family:Microsoft Yahei; color: black; font-size: 15px; }");


    QPushButton* m_pbtnYear = new QPushButton(m_pWndTitle);
    m_pbtnYear->setObjectName(QString::fromUtf8("closePushButton"));
    m_pbtnYear->setText(QString::fromLocal8Bit("关闭"));
    m_pbtnYear->setFixedSize(INT_BTNWIDTH, INT_BTNHEIGHT);
    m_pbtnYear->setStyleSheet("QPushButton {background-color:#FCFCFC; border-radius:5px; font-family:Microsoft Yahei; color: black; font-size: 15px; }");


    pBtnHBlayout->addWidget(m_pbtnDay);
    pBtnHBlayout->addWidget(m_pbtnMonth);
    pBtnHBlayout->addWidget(m_pbtnYear);

    pWgtHBlayout->addLayout(pBtnHBlayout);
    m_pWndTitle->setLayout(pWgtHBlayout);

    //信号-槽函数机制
    bool b = connect(m_pbtnDay, SIGNAL(clicked(bool)), this, SLOT(slotMinBtnClicked()));
    connect(m_pbtnMonth, SIGNAL(clicked(bool)), this, SLOT(slotMaxBtnClicked()));
    connect(m_pbtnYear, SIGNAL(clicked(bool)), this, SLOT(slotCloseBtnClicked()));
}

void ZMonSysTitleWgt::reSize(QSize size)
{
    m_pWndTitle->resize(size);
    m_pWndTitle->update();
}

void ZMonSysTitleWgt::setWndMaxFlag(bool bFlag)
{
    m_bMaxFlag = bFlag;
}

void ZMonSysTitleWgt::setBtnMax()
{
    m_pbtnMonth->setText(QString::fromLocal8Bit("最大化"));
}

void ZMonSysTitleWgt::setBtnNormal()
{
    m_pbtnMonth->setText(QString::fromLocal8Bit("还原"));
}

void ZMonSysTitleWgt::slotMinBtnClicked()
{
    //出发信号，通知主窗口，执行最小化操作
    emit sigMinBtnClicked();
}

void ZMonSysTitleWgt::slotMaxBtnClicked()
{
    //最大化按钮图标发生变化，由“最大化”图标变化为“还原”图标
    // ？？？？？？？？？


    emit sigMaxBtnClicked(m_bMaxFlag);
}

void ZMonSysTitleWgt::slotCloseBtnClicked()
{
    emit sigCloseBtnClicked();
}