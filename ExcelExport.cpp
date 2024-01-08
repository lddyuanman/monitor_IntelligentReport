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

	//����Excel�ؼ�
	if (!m_pExcel->setControl("Excel.Application"))
		return false;

	//������ʾ����,���ڵ��ԣ��˴��ſ�������excel�������̶����Կ�������ŵ�Ӱһ��
	//m_pExcel->dynamicCall("SetVisible (bool Visible)", true);

	//����ʾ�κξ�����Ϣ�����Ϊtrue��ô�ڹر��ǻ�������ơ��ļ����޸ģ��Ƿ񱣴桱����ʾ
	m_pExcel->setProperty("DisplayAlerts", false);

	//��ȡ����������
	auto pWorkbooks = m_pExcel->querySubObject("WorkBooks");
	if (!pWorkbooks)
		return false;

	//�½�һ��������    
	pWorkbooks->dynamicCall("Add");

	//��ȡ��ǰ������
	m_pWorkbook = new QAxObject();
	m_pWorkbook = m_pExcel->querySubObject("ActiveWorkBook");
	if (!m_pWorkbook)
		return false;

	return true;
}

void ExcelExport::endExport()  //�����������е���
{
	if (m_pWorkbook)
	{
		QAxObject* worksheets = m_pWorkbook->querySubObject("Sheets");//��ȡ��������
		QAxObject* first_sheet = worksheets->querySubObject("Item(int)", 1);
		first_sheet->dynamicCall("Select()");//ѡ�� sheet

		int sheet_count = worksheets->property("Count").toInt();  //��ȡ��������Ŀ
		first_sheet = worksheets->querySubObject("Item(int)", sheet_count);
		first_sheet->dynamicCall("delete");//ɾ�����һ��sheetҳ��Ϊ��sheet1
		m_strSavePath = "E:/";
		m_pWorkbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(m_strSavePath));//������filepath��ע��һ��Ҫ��QDir::toNativeSeparators��·���е�"/"ת��Ϊ"\"����Ȼһ�����治�ˡ�
		m_pWorkbook->dynamicCall("Close()");//�رչ�����
	}

	if (m_pExcel)
	{
		m_pExcel->dynamicCall("Quit()");//�ر�excel
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

	//���¿�ʼ����
	//������Щָ��û���пգ�һ��Ҫ����ָ���пյĺ�ϰ��

	//����д��excel��Ԫ������
	//��ʽһ��ʹ��Range����ͳһд��excel�������������ʱ��������������
	{
		QList<QVariant> oRowdata;
		QList<QVariant> aline;
		aline.append(QVariant(QStringLiteral("����")));
		aline.append(QVariant(QStringLiteral("�Ǻ�")));
		aline.append(QVariant(QStringLiteral("�ٺ�")));
		QVariant conv(aline);
		oRowdata.append(conv);
		QVariant oData(oRowdata);
		QString strRange = "A" + QString::number(1) + ":" + "C" + QString::number(1);//A1:C1,��д�����ݵı��Χ
		QAxObject* oRange = work_sheet->querySubObject("Range(QString)", strRange);
		if (oRange)
		{
			oRange->setProperty("Value2", oData);//���õ�Ԫ��ֵ,ʹ��Value2 wps �� office����������������
		}
	}

	//��ʽ����ָ������д�����ݣ����ַ�ʽ�����Եúܱ�׾�������������ܴ�ʱ������Ҫ������Ҫ��ÿд��һ�����ݶ�Ҫ����һ�α�����ܺܵ͡�
	{
		//��5�е�3��
		QAxObject* cell_5_3 = work_sheet->querySubObject("Cells(int,int)", 5, 3);
		cell_5_3->setProperty("Value2", "C++");
	}

	{
		QAxObject* pCell = work_sheet->querySubObject("Range(const QString&)", "A1:C1");
		if (pCell)
		{
			//������루���У�
			pCell->setProperty("HorizontalAlignment", -4108);//����루xlLeft����-4131  ���У�xlCenter����-4108  �Ҷ��루xlRight����-4152
			pCell->setProperty("VerticalAlignment", -4108); //�϶��루xlTop��-4160 ���У�xlCenter����-4108  �¶��루xlBottom����-4107

			//��������
			QAxObject* font = pCell->querySubObject("Font");  //��ȡ��Ԫ������
			font->setProperty("Bold", true);  //����Ӵ�
			font->setProperty("Name", QStringLiteral("���Ĳ���"));  //���õ�Ԫ������
			font->setProperty("Bold", true);  //���õ�Ԫ������Ӵ�
			font->setProperty("Size", 20);  //���õ�Ԫ�������С
			font->setProperty("Italic", true);  //���õ�Ԫ������б��
			font->setProperty("Underline", 2);  //���õ�Ԫ���»���
			font->setProperty("Color", QColor(255, 0, 0));  //���õ�Ԫ��������ɫ����ɫ��

			//���õ�Ԫ�񱳾�ɫ����ɫ��
			QColor bkColor(125, 125, 125);
			QAxObject* interior = pCell->querySubObject("Interior");
			interior->setProperty("Color", bkColor);

			//���Ƶ�Ԫ��߿򣨺�ɫ��
			QAxObject* border = pCell->querySubObject("Borders");
			border->setProperty("Color", QColor(0, 0, 0));

			//������
			QAxObject* rows = pCell->querySubObject("Rows");
			rows->querySubObject("Group");
		}

		//�������Ӧ
		auto range = work_sheet->querySubObject("UsedRange");
		QAxObject* cells = range->querySubObject("Columns");
		if (cells)
		{
			cells->dynamicCall("AutoFit");
		}

		//���õ�Ԫ���ʽ���ı���
		QAxObject* oRange = work_sheet->querySubObject("Range(QString)", "A1:A99");
		if (oRange)
		{
			oRange->setProperty("NumberFormatLocal", "@");
		}

		oRange = work_sheet->querySubObject("Range(QString)", "A1:B1");
		if (oRange)
		{
			pCell->setProperty("WrapText", true); //���ݹ��࣬�Զ�����
			pCell->setProperty("MergeCells", true); //�ϲ���Ԫ��
			//pCell ->setProperty("MergeCells", false);  //��ֵ�Ԫ��
			//pcell->dynamicCall("ClearContents()");  //��յ�Ԫ������
		}
	}
}
