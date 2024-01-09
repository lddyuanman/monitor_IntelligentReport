#include <QColor>
#include <QDir>
#include <QMessageBox>
//#include <QPushButton>
#include <QDebug>
#include"ExcelExport.h"

ExcelExport::ExcelExport()
{
	
}

ExcelExport::~ExcelExport()
{
	endExport();
}


int ExcelExport::changeStringToAscii(QString str)
{
	int num;
	QVector<uint>v = str.toUcs4();
	foreach(num, v)
	{
		return num;
	}
}

int ExcelExport::changeStringToInt(QString str)
{
	QString str_hex = str;                //获取十六进制数
	int dec = str_hex.toInt(0, 16);          //十六进制转十进制
	char st = dec;                       //十进制数用char类型表示--->必须有此步直接转化不可行
	QString str_ascii = QString(st);        //转化为ASCII值
	int str_int = str_ascii.toInt();           //转化为int值
	return str_int;                       //返回十六进制符号的ascii码值

}

QString ExcelExport::changeAsciiToString(int num)
{
	QByteArray bytearray;
	bytearray.append(num);
	char ch(bytearray.at(0));
	//char asciiChar = static_cast<char>(num); // 将整数转换为ASCII字符
	QString strTemp(ch);
	return strTemp;
}

QString ExcelExport::getRangeLetter(int nsize)
{
	if (nsize < 0)
	{
		return NULL;
	}
	
	QString strLetter = "A";//对应excel中首列
	int numstart = changeStringToAscii(strLetter);

	int multipleTemp = nsize / 26;//倍数
	QString strEnd;
	int remainderTemp = nsize % 26;//余数
	switch (multipleTemp)
	{
	case 0:
		numstart += nsize;
		strEnd = changeAsciiToString(numstart);
		break;
	case 1:
		numstart = numstart + remainderTemp;
		strEnd = "A" + changeAsciiToString(numstart);
		break;
	case 2:
		numstart += remainderTemp;
		strEnd = "B" + changeAsciiToString(numstart);
	case 3:
		numstart += remainderTemp;
		strEnd = "C" + changeAsciiToString(numstart);
	default:
		break;
	}

	return strEnd;
}

void ExcelExport::setSavePath(QString strpath)
{
	m_strExcelPath = strpath;
}

bool ExcelExport::isFileExist(QString strfile)
{
	QFile file(strfile);
	if (file.exists(strfile))
	{
		return true;
	}
	return false;
}

bool ExcelExport::isFileOpen(QString strfile)
{
	QFile file(strfile);
	bool wasUsed = false;
	if (file.exists())
	{
		QString strTemp = m_strExcelPath + "X";
		//判断文件是否已打开
		bool canRename = file.rename(m_strExcelPath, strTemp);
		if (canRename == false)
		{
			wasUsed = true;
		}
		else
		{
			wasUsed = false;
			file.rename(strTemp, m_strExcelPath);
		}
	}

	return wasUsed;
}

bool ExcelExport::isDeleteOldExcel()
{
	QFile file(m_strExcelPath);

	if (file.exists(m_strExcelPath))
	{
		QMessageBox msgBox(NULL);
		msgBox.resize(400, 200);
		msgBox.setWindowTitle(QString::fromLocal8Bit("注意"));
		msgBox.setText(QString::fromLocal8Bit("文件已存在，是否删除？"));
		msgBox.setIcon(QMessageBox::Question);
		msgBox.addButton(QString::fromLocal8Bit("确定"), QMessageBox::AcceptRole);
		msgBox.addButton(QString::fromLocal8Bit("取消"), QMessageBox::RejectRole);
		msgBox.setDefaultButton(QMessageBox::Yes);
		int ret = msgBox.exec();
		if (ret == QMessageBox::AcceptRole)
		{
			// 用户点击了确定按钮
			if (!file.remove(m_strExcelPath))
			{
				QMessageBox::warning(NULL, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("文件正在占用！"));
				qDebug() << "flie isn't delete. Be using!";
				return false;
			}

			qDebug() << " old file delete!";
			return true;
		}
		else if (ret == QMessageBox::RejectRole)
		{
			// 用户点击了取消按钮
			qDebug() << "user don't delete file!";
			return false;
		}
	}
	else
	{
		qDebug() << "file is not exits!";
		return false;
	}
}

void ExcelExport::setRow(int nrow)
{
	m_nTabRow = nrow;
}

void ExcelExport::setColumn(int ncol)
{
	m_nTabColumn = ncol;
}

void ExcelExport::setName(QString str)
{
	m_strName = str;
}

void ExcelExport::setHeadRow(QStringList strlst)
{
	m_strlstRow.clear();
	for (int n = 0; n < strlst.size(); n++)
	{
		m_strlstRow.append(strlst.at(n));
	}
}

void ExcelExport::setHeadColumn(QStringList strlst)
{
	m_strlstCol.clear();
	for (int n = 0; n < strlst.size(); n++)
	{
		m_strlstCol.append(strlst.at(n));
	}
}

void ExcelExport::setExcelData(QMap<QString, QStringList> mapdata)
{
	m_mapExcelData.clear();
	if (mapdata.size() <= 0)
	{
		qDebug() << "ExcelExport::setExcelData map data is null";
		return;
	}

	//STL型迭代
	QMap<QString, QStringList>::const_iterator stritr = mapdata.constBegin();
	while (stritr != mapdata.constEnd())
	{
		
		m_mapExcelData.insert(stritr.key(),stritr.value());
		stritr++;
	}
}

bool ExcelExport::addWorkbook()
{
	m_pExcel = new QAxObject();
	//连接Excel控件
	if (!m_pExcel->setControl("Excel.Application"))
	{
		return false;
	}	
	//窗体显示控制,用于调试，此处放开，导出excel整个过程都可以看到，想放电影一样
	//m_pExcel->dynamicCall("SetVisible (bool Visible)", true);
	//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
	m_pExcel->setProperty("DisplayAlerts", false);

	//获取工作簿集合
	auto pWorkbooks = m_pExcel->querySubObject("WorkBooks");
	if (!pWorkbooks)
		return false;
	//新建一个工作簿    
	pWorkbooks->dynamicCall("Add");

	//获取当前工作簿
	m_pWorkbook = m_pExcel->querySubObject("ActiveWorkBook");
	if (!m_pWorkbook)
		return false;

	return true;
}

void ExcelExport::endExport()  //在析构函数中调用
{
	if (m_pWorkbook)
	{
		QAxObject* worksheets = m_pWorkbook->querySubObject("Sheets");//获取工作表集合
		QAxObject* first_sheet = worksheets->querySubObject("Item(int)", 1);
		first_sheet->dynamicCall("Select()");//选中 sheet

		int sheet_count = worksheets->property("Count").toInt();  //获取工作表数目
		first_sheet = worksheets->querySubObject("Item(int)", sheet_count);
		first_sheet->dynamicCall("delete");//删除最后一个sheet页，为：sheet1
		//m_strExcelPath = "E:/";
		m_pWorkbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(m_strExcelPath));//保存至filepath，注意一定要用QDir::toNativeSeparators将路径中的"/"转换为"\"，不然一定保存不了。
		m_pWorkbook->dynamicCall("Close()");//关闭工作簿
	}

	if (m_pExcel)
	{
		m_pExcel->dynamicCall("Quit()");//关闭excel
		delete m_pExcel;
		m_pExcel = nullptr;
	}
}

void ExcelExport::startExport()
{
	if (!addWorkbook())
	{
		return;
	}

	//获取工作表集合
	QAxObject* worksheets = m_pWorkbook->querySubObject("Sheets");
	//获取工作表集合的工作表1，即sheet1
	QAxObject* worksheet = worksheets->querySubObject("Item(int)", 1);

	//设置表头值，横表头
	if (m_nTabRow == 0 || m_nTabColumn == 0 || m_strlstCol.size() < 0 || m_strlstRow.size() < 0)
	{
		qDebug() << "row,column, row_content,or col_content is null";
		return;
	}
	//表格左上角
	QAxObject* Range = worksheet->querySubObject("Cells(int,int)", 1, 1);//保存的excel文件第二行
	Range->dynamicCall("SetValue(const QString &)", QString::fromLocal8Bit("时间/姓名"));
	
	//处理左上角,合并A1和A2
	QAxObject* pCellLeftContor = worksheet->querySubObject("Range(const QString&)", "A1:A2");
	QAxObject* RangeC = worksheet->querySubObject("Range(QString)", "A1:A2");
	if (RangeC)
	{
		pCellLeftContor->setProperty("MergeCells", true); //合并单元格
	}

	//合并首行
	//QString strRange = "%1%2%3";
	//strRange.arg("B1:").arg(getRangeLetter(m_strlstCol.size())).arg("1"); 
	QString strRange =QString("B1:%1").arg(getRangeLetter(m_strlstCol.size())) + "1";
	QAxObject* pCellMerge = worksheet->querySubObject("Range(const QString&)", strRange);
	QAxObject* oRangeMerge = worksheet->querySubObject("Range(QString)", strRange);
	if (oRangeMerge)
	{
		pCellMerge->setProperty("MergeCells", true); //合并单元格
		pCellMerge->setProperty("HorizontalAlignment", -4108);
	}
	oRangeMerge->dynamicCall("SetValue(const QString &)", QString::fromLocal8Bit("%1").arg(m_strName));
	
	//////////////////////////////////////////////////////////////////////////
	// 设置表头
	int ncol = m_nTabColumn - 1;
	for (int i = 1; i < ncol + 1 ; i++)
	{
		//设置二行各列
		QAxObject* Range = worksheet->querySubObject("Cells(int,int)", 2, i + 1);//保存的excel文件第二行
		Range->dynamicCall("SetValue(const QString &)", m_strlstCol.at(i - 1));
		//Range->dynamicCall("SetValue(const QString &)", this->horizontalHeaderItem(i - 1)->text());
		Range->setProperty("HorizontalAlignment", -4108);
	}
	//设置表头值，纵表头
	int nrow = m_nTabRow - 2;
	for (int i = 1; i < nrow  + 1; i++)
	{
		//设置第二列各行
		QAxObject* Range = worksheet->querySubObject("Cells(int,int)", i + 2, 1);//保存的excel文件第二行
		Range->dynamicCall("SetValue(const QString &)", m_strlstRow.at(i - 1));
		//Range->dynamicCall("SetValue(const QString &)", this->horizontalHeaderItem(i - 1)->text());
		Range->setProperty("HorizontalAlignment", -4108);
	}
	

	//绘制单元格边框（黑色）
	QString strLine; 
	for (int nindex = 1; nindex < nrow + 3; nindex++)
	{
		strLine = QString("A%1:%2%3").arg(nindex).arg(getRangeLetter(m_strlstCol.size())).arg(nindex);
		QAxObject* pCellLine = worksheet->querySubObject("Range(const QString&)", strLine);
		//QAxObject* oRangeLine = worksheet->querySubObject("Range(QString)", "A1:A99");
		if (pCellLine)
		{
			QAxObject* border = pCellLine->querySubObject("Borders");
			border->setProperty("Color", QColor(0, 0, 0));
		}
	}	
	//////////////////////////////////////////////////////////////////////////
	//设置表格数据,表格数据是从(3,2)开始填充
	int nrow1 = m_nTabRow - 2;//3:表头显示2行 + excel表格字母第0行占一行
	int ncolumn = m_nTabColumn - 1;//纵表头显示内容占一列，excel表格序号占一列
	QString strstart = m_strlstCol.at(0);
	if (m_mapExcelData[strstart].size() != nrow || m_mapExcelData.size() != ncolumn)
	{
		qDebug() << "table'column or table's row   is not same whit map data!";
		return;
	}
	for (int j = 1; j < ncolumn + 1; j++)	
	{
		QString strdata = m_strlstCol.at(j - 1);
		for (int i = 1; i < nrow1 + 1; i++)
		{
			QAxObject* Range = worksheet->querySubObject("Cells(int,int)", i + 2, j + 1);
			Range->dynamicCall("SetValue(const QString &)", m_mapExcelData[strdata].at(i - 1));
			Range->setProperty("HorizontalAlignment", -4108);
		}
	}
	
	//宽度自适应
	auto range = worksheet->querySubObject("UsedRange");
	QAxObject* cells = range->querySubObject("Columns");
	if (cells)
	{
		cells->dynamicCall("AutoFit");
	}

	endExport();
}


void ExcelExport::example()
{
	
	//QAxObject* work_sheet /*= setWorkBook(strSheetName)*/;
	//if (!work_sheet)
	//{
	//	return;
	//}

	//以下开始乱炖
	//以下有些指针没有判空，一定要养成指针判空的好习惯

	////处理写入excel单元格数据
	////方式一，使用Range方法统一写入excel表格，数据量过大时，可以提升性能
	//{
	//	QList<QVariant> oRowdata;
	//	QList<QVariant> aline;
	//	aline.append(QVariant(QStringLiteral("哈哈")));
	//	aline.append(QVariant(QStringLiteral("呵呵")));
	//	aline.append(QVariant(QStringLiteral("嘿嘿")));
	//	QVariant conv(aline);
	//	oRowdata.append(conv);
	//	QVariant oData(oRowdata);
	//	QString strRange = "A" + QString::number(1) + ":" + "C" + QString::number(1);//A1:C1,需写入数据的表格范围
	//	QAxObject* oRange = worksheet->querySubObject("Range(QString)", strRange);
	//	if (oRange)
	//	{
	//		oRange->setProperty("Value2", oData);//设置单元格值,使用Value2 wps 和 office可以正常导出数据
	//	}
	//}
	// 
	////方式二，指定行列写入数据，这种方式不仅显得很笨拙，而且数据量很大时，慢的要死，主要是每写入一个数据都要访问一次表格，性能很低。
	//{
	//	//第5行第3列
	//	QAxObject* cell_5_3 = work_sheet->querySubObject("Cells(int,int)", 5, 3);
	//	cell_5_3->setProperty("Value2", "C++");
	//}

	//{
	//	QAxObject* pCell = work_sheet->querySubObject("Range(const QString&)", "A1:C1");
	//	if (pCell)
	//	{
	//		//字体对齐（居中）
	//		pCell->setProperty("HorizontalAlignment", -4108);//左对齐（xlLeft）：-4131  居中（xlCenter）：-4108  右对齐（xlRight）：-4152
	//		pCell->setProperty("VerticalAlignment", -4108); //上对齐（xlTop）-4160 居中（xlCenter）：-4108  下对齐（xlBottom）：-4107

	//		//设置字体
	//		QAxObject* font = pCell->querySubObject("Font");  //获取单元格字体
	//		font->setProperty("Bold", true);  //字体加粗
	//		font->setProperty("Name", QStringLiteral("华文彩云"));  //设置单元格字体
	//		font->setProperty("Bold", true);  //设置单元格字体加粗
	//		font->setProperty("Size", 20);  //设置单元格字体大小
	//		font->setProperty("Italic", true);  //设置单元格字体斜体
	//		font->setProperty("Underline", 2);  //设置单元格下划线
	//		font->setProperty("Color", QColor(255, 0, 0));  //设置单元格字体颜色（红色）

	//		//设置单元格背景色（灰色）
	//		QColor bkColor(125, 125, 125);
	//		QAxObject* interior = pCell->querySubObject("Interior");
	//		interior->setProperty("Color", bkColor);

	//		//绘制单元格边框（黑色）
	//		QAxObject* border = pCell->querySubObject("Borders");
	//		border->setProperty("Color", QColor(0, 0, 0));

	//		//创建组
	//		QAxObject* rows = pCell->querySubObject("Rows");
	//		rows->querySubObject("Group");
	//	}

	//	//宽度自适应
	//	auto range = work_sheet->querySubObject("UsedRange");
	//	QAxObject* cells = range->querySubObject("Columns");
	//	if (cells)
	//	{
	//		cells->dynamicCall("AutoFit");
	//	}

	//	//设置单元格格式（文本）
	//	QAxObject* oRange = work_sheet->querySubObject("Range(QString)", "A1:A99");
	//	if (oRange)
	//	{
	//		oRange->setProperty("NumberFormatLocal", "@");
	//	}

	//	oRange = work_sheet->querySubObject("Range(QString)", "A1:B1");
	//	if (oRange)
	//	{
	//		pCell->setProperty("WrapText", true); //内容过多，自动换行
	//		pCell->setProperty("MergeCells", true); //合并单元格
	//		//pCell ->setProperty("MergeCells", false);  //拆分单元格
	//		//pcell->dynamicCall("ClearContents()");  //清空单元格内容
	//	}
	//}


	

	/*QAxObject* work_sheets = work_book->querySubObject("Sheets");
	QAxObject* first_sheet = work_sheets->querySubObject("Item(int)", 1);
	QAxObject* cell = first_sheet->querySubObject("Cells(int,int)", 1, 1);
	cell->setProperty("Value", "test");*/
	//    QAxObject *font = cell->querySubObject("Font");  //获取单元格字体
	//    font->setProperty("Bold", true);  //设置单元格字体加粗 
	//    font->setProperty("Size", 16);  //设置单元格字体大小
	//    cell->setProperty("RowHeight", 50);  //设置单元格行高
	//    cell->setProperty("ColumnWidth", 30);  //设置单元格列宽
	//    cell->setProperty("HorizontalAlignment", -4108); //左对齐（xlLeft）：-4131  居中（xlCenter）：-4108  右对齐（xlRight）：-4152
	//    cell->setProperty("VerticalAlignment", -4108);  //上对齐（xlTop）-4160 居中（xlCenter）：-4108  下对齐（xlBottom）：-4107
	//    cell->setProperty("WrapText", true);  //内容过多，自动换行
	//    //cell->dynamicCall("ClearContents()");  //清空单元格内容
	//    QAxObject* interior = cell->querySubObject("Interior");
	//    interior->setProperty("Color", QColor(0, 255, 0));   //设置单元格背景色（绿色）
	//    QAxObject* border = cell->querySubObject("Borders");
	//    border->setProperty("Color", QColor(0, 0, 255));   //设置单元格边框色（蓝色）
	//    QAxObject *font = cell->querySubObject("Font");  //获取单元格字体
	//    font->setProperty("Name", QStringLiteral("华文彩云"));  //设置单元格字体
	//    font->setProperty("Bold", true);  //设置单元格字体加粗
	//    font->setProperty("Size", 20);  //设置单元格字体大小
	//    font->setProperty("Italic", true);  //设置单元格字体斜体
	//    font->setProperty("Underline", 2);  //设置单元格下划线
	//    font->setProperty("Color", QColor(255, 0, 0));  //设置单元格字体颜色（红色）




	////如果解决不了对原有文件重新写入或刷新的问题，就将原本文件删除，重新写文件
	////获取保存路径
	////QString filepath = QFileDialog::getSaveFileName(this, tr("Save"), ".", tr(" (*.xlsx)"));
	//if (!m_strReportFullPath.isEmpty()) {
	//	QAxObject* Excel = new QAxObject(this);
	//	//连接Excel控件
	//	Excel->setControl("Excel.Application");
	//	//不显示窗体
	//	Excel->dynamicCall("SetVisible (bool Visible)", "false");
	//	//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
	//	Excel->setProperty("DisplayAlerts", false);
	//	//获取工作簿集合
	//	QAxObject* workbooks = Excel->querySubObject("WorkBooks");
	//	//新建一个工作簿
	//	workbooks->dynamicCall("Add");
	//	//获取当前工作簿
	//	QAxObject* workbook = Excel->querySubObject("ActiveWorkBook");
	//	//获取工作表集合
	//	QAxObject* worksheets = workbook->querySubObject("Sheets");
	//	//获取工作表集合的工作表1，即sheet1
	//	QAxObject* worksheet = worksheets->querySubObject("Item(int)", 1);

	//	//表格左上角
	//	QAxObject* Range = worksheet->querySubObject("Cells(int,int)", 1, 1);//保存的excel文件第二行
	//	Range->dynamicCall("SetValue(const QString &)", this->model()->index(0, 0).data().toString());
	//	//设置表头值，横表头
	//	int ncol = this->columnCount() - 1;
	//	for (int i = 1; i < ncol + 1; i++)
	//	{
	//		//设置二行各列
	//		QAxObject* Range = worksheet->querySubObject("Cells(int,int)", 1, i+1);//保存的excel文件第二行
	//		Range->dynamicCall("SetValue(const QString &)", this->model()->index(1,i).data().toString());
	//		//Range->dynamicCall("SetValue(const QString &)", this->horizontalHeaderItem(i - 1)->text());
	//	}
	//	//设置表头值，纵表头
	//	int nrow = this->rowCount() - 2;
	//	for (int i = 1; i < nrow + 1; i++)
	//	{
	//		//设置第二列各行
	//		QAxObject* Range = worksheet->querySubObject("Cells(int,int)", i+1, 1);//保存的excel文件第二行
	//		Range->dynamicCall("SetValue(const QString &)", this->model()->index(i + 1, 0).data().toString());
	//		//Range->dynamicCall("SetValue(const QString &)", this->horizontalHeaderItem(i - 1)->text());
	//	}


	//	//设置表格数据
	//	int nrow1 = this->rowCount() - 2;
	//	for (int i = 1; i < nrow1 + 1; i++)
	//	{
	//		for (int j = 1; j < this->columnCount() + 1; j++)
	//		{
	//			QAxObject* Range = worksheet->querySubObject("Cells(int,int)", i + 1, j);
	//			//Range->dynamicCall("SetValue(const QString &)", this->item(i - 1, j - 1)->data(Qt::DisplayRole).toString());
	//			//Range->dynamicCall("SetValue(const QString &)", this->item(i - 1, j - 1)->data(Qt::DisplayRole).toString());
	//		}
	//	}
	//	workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(m_strReportFullPath));//保存至filepath
	//	workbook->dynamicCall("Close()");//关闭工作簿
	//	Excel->dynamicCall("QUIt()");//关闭Excel
	//	delete Excel;
	//	Excel = NULL;
	//	//qDebug() << "导出成功啦！！！";
}