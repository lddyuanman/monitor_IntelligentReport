#include"HTitleWgt.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>

HMonSysTitleWgt::HMonSysTitleWgt(QWidget* parent, int nWidth)
    : QWidget(parent) , m_nWgtWidth(nWidth)
{
    m_bMaxFlag = true;
    initUI();
}

HMonSysTitleWgt::~HMonSysTitleWgt()
{
    if (m_pWndTitle != NULL)
    {
        delete m_pWndTitle;
    }
}

void HMonSysTitleWgt::initUI()
{
   // this->setStyleSheet("background-color:#7F7F7F;");
    this->setStyleSheet("background-color:#FCFCFC;");

    m_pWndTitle = new QWidget(this);
    m_pWndTitle->setFixedHeight(INI_TITLE_HEIGHT);
    m_pWndTitle->setGeometry(QRect(0, 0, m_nWgtWidth, INI_TITLE_HEIGHT));

    QHBoxLayout* pWgtHBlayout = new QHBoxLayout(m_pWndTitle);
    pWgtHBlayout->setSpacing(6);
    pWgtHBlayout->setContentsMargins(11, 11, 11, 11);
    pWgtHBlayout->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    pWgtHBlayout->setContentsMargins(0, 0, 0, 0);

    //��ǩˮƽ����
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

    //ˮƽ���
    QSpacerItem* pHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    pWgtHBlayout->addItem(pHorizontalSpacer);

    //��ť����
    QHBoxLayout* pBtnHBlayout = new QHBoxLayout(m_pWndTitle);
    pBtnHBlayout->setSpacing(6);
    
    QPushButton* m_pbtnDay = new QPushButton(m_pWndTitle);
    m_pbtnDay->setObjectName(QString::fromUtf8("minPushButton"));
    m_pbtnDay->setText(QString::fromLocal8Bit("��С��"));
    m_pbtnDay->setFixedSize(INT_BTNWIDTH, INT_BTNHEIGHT);

    m_pbtnMonth = new QPushButton(m_pWndTitle);
    m_pbtnMonth->setObjectName(QString::fromUtf8("maxPushButton"));
    m_pbtnMonth->setText(QString::fromLocal8Bit("��ԭ"));
    m_pbtnMonth->setFixedSize(INT_BTNWIDTH, INT_BTNHEIGHT);

    QPushButton* m_pbtnYear = new QPushButton(m_pWndTitle);
    m_pbtnYear->setObjectName(QString::fromUtf8("closePushButton"));
    m_pbtnYear->setText(QString::fromLocal8Bit("�ر�"));
    m_pbtnYear->setFixedSize(INT_BTNWIDTH, INT_BTNHEIGHT);

    pBtnHBlayout->addWidget(m_pbtnDay);
    pBtnHBlayout->addWidget(m_pbtnMonth);
    pBtnHBlayout->addWidget(m_pbtnYear);

    pWgtHBlayout->addLayout(pBtnHBlayout);
    m_pWndTitle->setLayout(pWgtHBlayout);

    //�ź�-�ۺ�������
    connect(m_pbtnDay, SIGNAL(clicked(bool)), this, SLOT(slotMinBtnClicked()));
    connect(m_pbtnMonth, SIGNAL(clicked(bool)), this, SLOT(slotMaxBtnClicked()));
    connect(m_pbtnYear, SIGNAL(clicked(bool)), this, SLOT(slotCloseBtnClicked()));
}

void HMonSysTitleWgt::reSize(QSize size)
{
    m_pWndTitle->resize(size);
    m_pWndTitle->update();
}

void HMonSysTitleWgt::setWndMaxFlag(bool bFlag)
{
    m_bMaxFlag = bFlag;
}

void HMonSysTitleWgt::setBtnMax()
{
    m_pbtnMonth->setText(QString::fromLocal8Bit("���"));
}

void HMonSysTitleWgt::setBtnNormal()
{
    m_pbtnMonth->setText(QString::fromLocal8Bit("��ԭ"));
}

void HMonSysTitleWgt::slotMinBtnClicked()
{
    //�����źţ�֪ͨ�����ڣ�ִ����С������
    emit sigMinBtnClicked();
}

void HMonSysTitleWgt::slotMaxBtnClicked()
{
    //��󻯰�ťͼ�귢���仯���ɡ���󻯡�ͼ��仯Ϊ����ԭ��ͼ��
    // ������������������


    emit sigMaxBtnClicked(m_bMaxFlag);
}

void HMonSysTitleWgt::slotCloseBtnClicked()
{
    emit sigCloseBtnClicked();
}