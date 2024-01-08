#pragma once
//报表导出窗口
#include <QtWidgets/QWidget>
#include <QLabel>

#define INI_EXPORT_WGT_HEIGHT 250
#define INI_EXPORT_WGT_WIDTH 450
#define INI_EXPORT_WGT_TITLE_HEIGHT 40
#define INI_EXPORT_HINT_WGT_HEIGHT 150
#define INI_EXPORT_HINT_WGT_WIDTH 400
#define INI_EXPORT_HINT_LABEL_HEIGHT 30
#define INI_EXPORT_BTN_HEIGHT 30
#define INI_EXPORT_BTN_WIDTH 60

class ZExportReportWgt : public QWidget
{
    Q_OBJECT

public:
    ZExportReportWgt(QWidget* parent = Q_NULLPTR);
    ~ZExportReportWgt();

    void initUI();

    void setReportPath(QString strpath);
signals:
    void sigOpenReport();

public slots:
    void slotShowExportWgt();
    void sloCloseBtnClicked();
    void sloCancelBtnClicked();
    void sloOkBtnClicked();

private:
	QLabel* m_plbDirectory;
    QString m_strReportPth;
};
