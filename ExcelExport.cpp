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
	QString str_hex = str;                //��ȡʮ��������
	int dec = str_hex.toInt(0, 16);          //ʮ������תʮ����
	char st = dec;                       //ʮ��������char���ͱ�ʾ--->�����д˲�ֱ��ת��������
	QString str_ascii = QString(st);        //ת��ΪASCIIֵ
	int str_int = str_ascii.toInt();           //ת��Ϊintֵ
	return str_int;                       //����ʮ�����Ʒ��ŵ�ascii��ֵ

}

QString ExcelExport::changeAsciiToString(int num)
{
	QByteArray bytearray;
	bytearray.append(num);
	char ch(bytearray.at(0));
	//char asciiChar = static_cast<char>(num); // ������ת��ΪASCII�ַ�
	QString strTemp(ch);
	return strTemp;
}

QString ExcelExport::getRangeLetter(int nsize)
{
	if (nsize < 0)
	{
		return NULL;
	}
	
	QString strLetter = "A";//��Ӧexcel������
	int numstart = changeStringToAscii(strLetter);

	int multipleTemp = nsize / 26;//����
	QString strEnd;
	int remainderTemp = nsize % 26;//����
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
		//�ж��ļ��Ƿ��Ѵ�
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
		msgBox.setWindowTitle(QString::fromLocal8Bit("ע��"));
		msgBox.setText(QString::fromLocal8Bit("�ļ��Ѵ��ڣ��Ƿ�ɾ����"));
		msgBox.setIcon(QMessageBox::Question);
		msgBox.addButton(QString::fromLocal8Bit("ȷ��"), QMessageBox::AcceptRole);
		msgBox.addButton(QString::fromLocal8Bit("ȡ��"), QMessageBox::RejectRole);
		msgBox.setDefaultButton(QMessageBox::Yes);
		int ret = msgBox.exec();
		if (ret == QMessageBox::AcceptRole)
		{
			// �û������ȷ����ť
			if (!file.remove(m_strExcelPath))
			{
				QMessageBox::warning(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�ļ�����ռ�ã�"));
				qDebug() << "flie isn't delete. Be using!";
				return false;
			}

			qDebug() << " old file delete!";
			return true;
		}
		else if (ret == QMessageBox::RejectRole)
		{
			// �û������ȡ����ť
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

	//STL�͵���
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
	//����Excel�ؼ�
	if (!m_pExcel->setControl("Excel.Application"))
	{
		return false;
	}	
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
		//m_strExcelPath = "E:/";
		m_pWorkbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(m_strExcelPath));//������filepath��ע��һ��Ҫ��QDir::toNativeSeparators��·���е�"/"ת��Ϊ"\"����Ȼһ�����治�ˡ�
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

	//��ȡ��������
	QAxObject* worksheets = m_pWorkbook->querySubObject("Sheets");
	//��ȡ�������ϵĹ�����1����sheet1
	QAxObject* worksheet = worksheets->querySubObject("Item(int)", 1);

	//���ñ�ͷֵ�����ͷ
	if (m_nTabRow == 0 || m_nTabColumn == 0 || m_strlstCol.size() < 0 || m_strlstRow.size() < 0)
	{
		qDebug() << "row,column, row_content,or col_content is null";
		return;
	}
	//������Ͻ�
	QAxObject* Range = worksheet->querySubObject("Cells(int,int)", 1, 1);//�����excel�ļ��ڶ���
	Range->dynamicCall("SetValue(const QString &)", QString::fromLocal8Bit("ʱ��/����"));
	
	//�������Ͻ�,�ϲ�A1��A2
	QAxObject* pCellLeftContor = worksheet->querySubObject("Range(const QString&)", "A1:A2");
	QAxObject* RangeC = worksheet->querySubObject("Range(QString)", "A1:A2");
	if (RangeC)
	{
		pCellLeftContor->setProperty("MergeCells", true); //�ϲ���Ԫ��
	}

	//�ϲ�����
	//QString strRange = "%1%2%3";
	//strRange.arg("B1:").arg(getRangeLetter(m_strlstCol.size())).arg("1"); 
	QString strRange =QString("B1:%1").arg(getRangeLetter(m_strlstCol.size())) + "1";
	QAxObject* pCellMerge = worksheet->querySubObject("Range(const QString&)", strRange);
	QAxObject* oRangeMerge = worksheet->querySubObject("Range(QString)", strRange);
	if (oRangeMerge)
	{
		pCellMerge->setProperty("MergeCells", true); //�ϲ���Ԫ��
		pCellMerge->setProperty("HorizontalAlignment", -4108);
	}
	oRangeMerge->dynamicCall("SetValue(const QString &)", QString::fromLocal8Bit("%1").arg(m_strName));
	
	//////////////////////////////////////////////////////////////////////////
	// ���ñ�ͷ
	int ncol = m_nTabColumn - 1;
	for (int i = 1; i < ncol + 1 ; i++)
	{
		//���ö��и���
		QAxObject* Range = worksheet->querySubObject("Cells(int,int)", 2, i + 1);//�����excel�ļ��ڶ���
		Range->dynamicCall("SetValue(const QString &)", m_strlstCol.at(i - 1));
		//Range->dynamicCall("SetValue(const QString &)", this->horizontalHeaderItem(i - 1)->text());
		Range->setProperty("HorizontalAlignment", -4108);
	}
	//���ñ�ͷֵ���ݱ�ͷ
	int nrow = m_nTabRow - 2;
	for (int i = 1; i < nrow  + 1; i++)
	{
		//���õڶ��и���
		QAxObject* Range = worksheet->querySubObject("Cells(int,int)", i + 2, 1);//�����excel�ļ��ڶ���
		Range->dynamicCall("SetValue(const QString &)", m_strlstRow.at(i - 1));
		//Range->dynamicCall("SetValue(const QString &)", this->horizontalHeaderItem(i - 1)->text());
		Range->setProperty("HorizontalAlignment", -4108);
	}
	

	//���Ƶ�Ԫ��߿򣨺�ɫ��
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
	//���ñ������,��������Ǵ�(3,2)��ʼ���
	int nrow1 = m_nTabRow - 2;//3:��ͷ��ʾ2�� + excel�����ĸ��0��ռһ��
	int ncolumn = m_nTabColumn - 1;//�ݱ�ͷ��ʾ����ռһ�У�excel������ռһ��
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
	
	//�������Ӧ
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

	//���¿�ʼ����
	//������Щָ��û���пգ�һ��Ҫ����ָ���пյĺ�ϰ��

	////����д��excel��Ԫ������
	////��ʽһ��ʹ��Range����ͳһд��excel�������������ʱ��������������
	//{
	//	QList<QVariant> oRowdata;
	//	QList<QVariant> aline;
	//	aline.append(QVariant(QStringLiteral("����")));
	//	aline.append(QVariant(QStringLiteral("�Ǻ�")));
	//	aline.append(QVariant(QStringLiteral("�ٺ�")));
	//	QVariant conv(aline);
	//	oRowdata.append(conv);
	//	QVariant oData(oRowdata);
	//	QString strRange = "A" + QString::number(1) + ":" + "C" + QString::number(1);//A1:C1,��д�����ݵı��Χ
	//	QAxObject* oRange = worksheet->querySubObject("Range(QString)", strRange);
	//	if (oRange)
	//	{
	//		oRange->setProperty("Value2", oData);//���õ�Ԫ��ֵ,ʹ��Value2 wps �� office����������������
	//	}
	//}
	// 
	////��ʽ����ָ������д�����ݣ����ַ�ʽ�����Եúܱ�׾�������������ܴ�ʱ������Ҫ������Ҫ��ÿд��һ�����ݶ�Ҫ����һ�α�����ܺܵ͡�
	//{
	//	//��5�е�3��
	//	QAxObject* cell_5_3 = work_sheet->querySubObject("Cells(int,int)", 5, 3);
	//	cell_5_3->setProperty("Value2", "C++");
	//}

	//{
	//	QAxObject* pCell = work_sheet->querySubObject("Range(const QString&)", "A1:C1");
	//	if (pCell)
	//	{
	//		//������루���У�
	//		pCell->setProperty("HorizontalAlignment", -4108);//����루xlLeft����-4131  ���У�xlCenter����-4108  �Ҷ��루xlRight����-4152
	//		pCell->setProperty("VerticalAlignment", -4108); //�϶��루xlTop��-4160 ���У�xlCenter����-4108  �¶��루xlBottom����-4107

	//		//��������
	//		QAxObject* font = pCell->querySubObject("Font");  //��ȡ��Ԫ������
	//		font->setProperty("Bold", true);  //����Ӵ�
	//		font->setProperty("Name", QStringLiteral("���Ĳ���"));  //���õ�Ԫ������
	//		font->setProperty("Bold", true);  //���õ�Ԫ������Ӵ�
	//		font->setProperty("Size", 20);  //���õ�Ԫ�������С
	//		font->setProperty("Italic", true);  //���õ�Ԫ������б��
	//		font->setProperty("Underline", 2);  //���õ�Ԫ���»���
	//		font->setProperty("Color", QColor(255, 0, 0));  //���õ�Ԫ��������ɫ����ɫ��

	//		//���õ�Ԫ�񱳾�ɫ����ɫ��
	//		QColor bkColor(125, 125, 125);
	//		QAxObject* interior = pCell->querySubObject("Interior");
	//		interior->setProperty("Color", bkColor);

	//		//���Ƶ�Ԫ��߿򣨺�ɫ��
	//		QAxObject* border = pCell->querySubObject("Borders");
	//		border->setProperty("Color", QColor(0, 0, 0));

	//		//������
	//		QAxObject* rows = pCell->querySubObject("Rows");
	//		rows->querySubObject("Group");
	//	}

	//	//�������Ӧ
	//	auto range = work_sheet->querySubObject("UsedRange");
	//	QAxObject* cells = range->querySubObject("Columns");
	//	if (cells)
	//	{
	//		cells->dynamicCall("AutoFit");
	//	}

	//	//���õ�Ԫ���ʽ���ı���
	//	QAxObject* oRange = work_sheet->querySubObject("Range(QString)", "A1:A99");
	//	if (oRange)
	//	{
	//		oRange->setProperty("NumberFormatLocal", "@");
	//	}

	//	oRange = work_sheet->querySubObject("Range(QString)", "A1:B1");
	//	if (oRange)
	//	{
	//		pCell->setProperty("WrapText", true); //���ݹ��࣬�Զ�����
	//		pCell->setProperty("MergeCells", true); //�ϲ���Ԫ��
	//		//pCell ->setProperty("MergeCells", false);  //��ֵ�Ԫ��
	//		//pcell->dynamicCall("ClearContents()");  //��յ�Ԫ������
	//	}
	//}


	

	/*QAxObject* work_sheets = work_book->querySubObject("Sheets");
	QAxObject* first_sheet = work_sheets->querySubObject("Item(int)", 1);
	QAxObject* cell = first_sheet->querySubObject("Cells(int,int)", 1, 1);
	cell->setProperty("Value", "test");*/
	//    QAxObject *font = cell->querySubObject("Font");  //��ȡ��Ԫ������
	//    font->setProperty("Bold", true);  //���õ�Ԫ������Ӵ� 
	//    font->setProperty("Size", 16);  //���õ�Ԫ�������С
	//    cell->setProperty("RowHeight", 50);  //���õ�Ԫ���и�
	//    cell->setProperty("ColumnWidth", 30);  //���õ�Ԫ���п�
	//    cell->setProperty("HorizontalAlignment", -4108); //����루xlLeft����-4131  ���У�xlCenter����-4108  �Ҷ��루xlRight����-4152
	//    cell->setProperty("VerticalAlignment", -4108);  //�϶��루xlTop��-4160 ���У�xlCenter����-4108  �¶��루xlBottom����-4107
	//    cell->setProperty("WrapText", true);  //���ݹ��࣬�Զ�����
	//    //cell->dynamicCall("ClearContents()");  //��յ�Ԫ������
	//    QAxObject* interior = cell->querySubObject("Interior");
	//    interior->setProperty("Color", QColor(0, 255, 0));   //���õ�Ԫ�񱳾�ɫ����ɫ��
	//    QAxObject* border = cell->querySubObject("Borders");
	//    border->setProperty("Color", QColor(0, 0, 255));   //���õ�Ԫ��߿�ɫ����ɫ��
	//    QAxObject *font = cell->querySubObject("Font");  //��ȡ��Ԫ������
	//    font->setProperty("Name", QStringLiteral("���Ĳ���"));  //���õ�Ԫ������
	//    font->setProperty("Bold", true);  //���õ�Ԫ������Ӵ�
	//    font->setProperty("Size", 20);  //���õ�Ԫ�������С
	//    font->setProperty("Italic", true);  //���õ�Ԫ������б��
	//    font->setProperty("Underline", 2);  //���õ�Ԫ���»���
	//    font->setProperty("Color", QColor(255, 0, 0));  //���õ�Ԫ��������ɫ����ɫ��




	////���������˶�ԭ���ļ�����д���ˢ�µ����⣬�ͽ�ԭ���ļ�ɾ��������д�ļ�
	////��ȡ����·��
	////QString filepath = QFileDialog::getSaveFileName(this, tr("Save"), ".", tr(" (*.xlsx)"));
	//if (!m_strReportFullPath.isEmpty()) {
	//	QAxObject* Excel = new QAxObject(this);
	//	//����Excel�ؼ�
	//	Excel->setControl("Excel.Application");
	//	//����ʾ����
	//	Excel->dynamicCall("SetVisible (bool Visible)", "false");
	//	//����ʾ�κξ�����Ϣ�����Ϊtrue��ô�ڹر��ǻ�������ơ��ļ����޸ģ��Ƿ񱣴桱����ʾ
	//	Excel->setProperty("DisplayAlerts", false);
	//	//��ȡ����������
	//	QAxObject* workbooks = Excel->querySubObject("WorkBooks");
	//	//�½�һ��������
	//	workbooks->dynamicCall("Add");
	//	//��ȡ��ǰ������
	//	QAxObject* workbook = Excel->querySubObject("ActiveWorkBook");
	//	//��ȡ��������
	//	QAxObject* worksheets = workbook->querySubObject("Sheets");
	//	//��ȡ�������ϵĹ�����1����sheet1
	//	QAxObject* worksheet = worksheets->querySubObject("Item(int)", 1);

	//	//������Ͻ�
	//	QAxObject* Range = worksheet->querySubObject("Cells(int,int)", 1, 1);//�����excel�ļ��ڶ���
	//	Range->dynamicCall("SetValue(const QString &)", this->model()->index(0, 0).data().toString());
	//	//���ñ�ͷֵ�����ͷ
	//	int ncol = this->columnCount() - 1;
	//	for (int i = 1; i < ncol + 1; i++)
	//	{
	//		//���ö��и���
	//		QAxObject* Range = worksheet->querySubObject("Cells(int,int)", 1, i+1);//�����excel�ļ��ڶ���
	//		Range->dynamicCall("SetValue(const QString &)", this->model()->index(1,i).data().toString());
	//		//Range->dynamicCall("SetValue(const QString &)", this->horizontalHeaderItem(i - 1)->text());
	//	}
	//	//���ñ�ͷֵ���ݱ�ͷ
	//	int nrow = this->rowCount() - 2;
	//	for (int i = 1; i < nrow + 1; i++)
	//	{
	//		//���õڶ��и���
	//		QAxObject* Range = worksheet->querySubObject("Cells(int,int)", i+1, 1);//�����excel�ļ��ڶ���
	//		Range->dynamicCall("SetValue(const QString &)", this->model()->index(i + 1, 0).data().toString());
	//		//Range->dynamicCall("SetValue(const QString &)", this->horizontalHeaderItem(i - 1)->text());
	//	}


	//	//���ñ������
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
	//	workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(m_strReportFullPath));//������filepath
	//	workbook->dynamicCall("Close()");//�رչ�����
	//	Excel->dynamicCall("QUIt()");//�ر�Excel
	//	delete Excel;
	//	Excel = NULL;
	//	//qDebug() << "�����ɹ���������";
}