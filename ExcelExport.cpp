#include <QColor>
#include <QDir>
#include"ExcelExport.h"

ExcelExport::ExcelExport()
{
	
}

ExcelExport::~ExcelExport()
{

}

bool ExcelExport::addWorkbook()
{

	m_pExcel = new QAxObject();

	//连接Excel控件
	if (!m_pExcel->setControl("Excel.Application"))
		return false;

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
	m_pWorkbook = new QAxObject();
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
		m_strSavePath = "E:/";
		m_pWorkbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(m_strSavePath));//保存至filepath，注意一定要用QDir::toNativeSeparators将路径中的"/"转换为"\"，不然一定保存不了。
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

	QAxObject* work_sheet /*= setWorkBook(strSheetName)*/;
	if (!work_sheet)
	{
		return;
	}

	//以下开始乱炖
	//以下有些指针没有判空，一定要养成指针判空的好习惯

	//处理写入excel单元格数据
	//方式一，使用Range方法统一写入excel表格，数据量过大时，可以提升性能
	{
		QList<QVariant> oRowdata;
		QList<QVariant> aline;
		aline.append(QVariant(QStringLiteral("哈哈")));
		aline.append(QVariant(QStringLiteral("呵呵")));
		aline.append(QVariant(QStringLiteral("嘿嘿")));
		QVariant conv(aline);
		oRowdata.append(conv);
		QVariant oData(oRowdata);
		QString strRange = "A" + QString::number(1) + ":" + "C" + QString::number(1);//A1:C1,需写入数据的表格范围
		QAxObject* oRange = work_sheet->querySubObject("Range(QString)", strRange);
		if (oRange)
		{
			oRange->setProperty("Value2", oData);//设置单元格值,使用Value2 wps 和 office可以正常导出数据
		}
	}

	//方式二，指定行列写入数据，这种方式不仅显得很笨拙，而且数据量很大时，慢的要死，主要是每写入一个数据都要访问一次表格，性能很低。
	{
		//第5行第3列
		QAxObject* cell_5_3 = work_sheet->querySubObject("Cells(int,int)", 5, 3);
		cell_5_3->setProperty("Value2", "C++");
	}

	{
		QAxObject* pCell = work_sheet->querySubObject("Range(const QString&)", "A1:C1");
		if (pCell)
		{
			//字体对齐（居中）
			pCell->setProperty("HorizontalAlignment", -4108);//左对齐（xlLeft）：-4131  居中（xlCenter）：-4108  右对齐（xlRight）：-4152
			pCell->setProperty("VerticalAlignment", -4108); //上对齐（xlTop）-4160 居中（xlCenter）：-4108  下对齐（xlBottom）：-4107

			//设置字体
			QAxObject* font = pCell->querySubObject("Font");  //获取单元格字体
			font->setProperty("Bold", true);  //字体加粗
			font->setProperty("Name", QStringLiteral("华文彩云"));  //设置单元格字体
			font->setProperty("Bold", true);  //设置单元格字体加粗
			font->setProperty("Size", 20);  //设置单元格字体大小
			font->setProperty("Italic", true);  //设置单元格字体斜体
			font->setProperty("Underline", 2);  //设置单元格下划线
			font->setProperty("Color", QColor(255, 0, 0));  //设置单元格字体颜色（红色）

			//设置单元格背景色（灰色）
			QColor bkColor(125, 125, 125);
			QAxObject* interior = pCell->querySubObject("Interior");
			interior->setProperty("Color", bkColor);

			//绘制单元格边框（黑色）
			QAxObject* border = pCell->querySubObject("Borders");
			border->setProperty("Color", QColor(0, 0, 0));

			//创建组
			QAxObject* rows = pCell->querySubObject("Rows");
			rows->querySubObject("Group");
		}

		//宽度自适应
		auto range = work_sheet->querySubObject("UsedRange");
		QAxObject* cells = range->querySubObject("Columns");
		if (cells)
		{
			cells->dynamicCall("AutoFit");
		}

		//设置单元格格式（文本）
		QAxObject* oRange = work_sheet->querySubObject("Range(QString)", "A1:A99");
		if (oRange)
		{
			oRange->setProperty("NumberFormatLocal", "@");
		}

		oRange = work_sheet->querySubObject("Range(QString)", "A1:B1");
		if (oRange)
		{
			pCell->setProperty("WrapText", true); //内容过多，自动换行
			pCell->setProperty("MergeCells", true); //合并单元格
			//pCell ->setProperty("MergeCells", false);  //拆分单元格
			//pcell->dynamicCall("ClearContents()");  //清空单元格内容
		}
	}
}
