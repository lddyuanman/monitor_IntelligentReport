#pragma once
/*
* ���ϵͳ�����ڶ���������
* ����widget���࣬�ڸ����ڴ������Ӵ��ڲ���ʾ����
* 
*/
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>

#define INI_TITLE_HEIGHT 50
#define INI_LABEL_HEIGHT 50
#define INT_NAMEWIDTH 100
#define INT_LABWIDTH  40
#define INT_BTNWIDTH  50
#define INT_BTNHEIGHT 35

class HMonSysTitleWgt : public QWidget
{
    Q_OBJECT

public:
    HMonSysTitleWgt(QWidget* parent = Q_NULLPTR, int nWidth = 0);
    ~HMonSysTitleWgt();

    void reSize(QSize size);
    void setWndMaxFlag(bool bFlag);
    void setBtnMax();
    void setBtnNormal();

private:
    void initUI();

signals:
    // �ۺ���;
    void sigMinBtnClicked();
    void sigMaxBtnClicked(bool);
    void sigCloseBtnClicked();

public slots:
    void slotMinBtnClicked();
    void slotMaxBtnClicked();
    void slotCloseBtnClicked();


private:
    QWidget*       m_pWndTitle;
    QPushButton*   m_pbtnMonth;

    int       m_nWgtWidth;
    bool      m_bMaxFlag;

};
