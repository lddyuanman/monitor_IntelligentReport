#pragma once
/*
* 基于QWidget的类声明
*/

#include <QtWidgets/QWidget>
class HExampleWgt : public QWidget
{
	Q_OBJECT

public:
	HExampleWgt(QWidget* parent = Q_NULLPTR, int nWidth = 0);
	~HExampleWgt();

private:


signals:


public slots:

};

