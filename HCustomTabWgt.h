#pragma once
#include <QTableWidget>
#include <QStyledItemDelegate>

#define ROWCOUNTPERPAGE 15
#define ROWHEIGHT 60//行高
#define INT_FIRST_COLUMN_WIDTH 100//表头和表内容首列宽度
#define INT_HEAD_ROW_HEIGHT 40//表头首行和第二行高度

class ItemDelegate;
class HCustomTabWgt : public QTableWidget
{
    Q_OBJECT

public:
    HCustomTabWgt(QWidget* parent = Q_NULLPTR, int nrow = 0, int ncolumn =0);
    ~HCustomTabWgt();

    //m_frozenTableWgt的固定行（冻结）
    //自定义表头m_frozenTableWgt与HCustomTabWgt的联动，表格的尺寸变化、滚动条移动、界面平移等问题
    void resizeEvent(QResizeEvent* event);  //重载虚函数 resize事件，同时更新m_frozenTableWgt的位置
    QModelIndex moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers);//重载虚函数 鼠标移动事件
    void scrollTo(const QModelIndex& index, QAbstractItemView::ScrollHint hint);//TableWidget移动事件
    void updateFrozenTableGeometry();//确定m_frozenTableWgt与HCustomTabWgt位置

    void initFrozenFrame();//表头处理m_frozenTableWgt
    //void initOldExample();
    //void initNewFrame();
    
    void setFrozenFrameRow(int nrow);//设置冻结表头的行数

    void initFrame(); //数据显示表HCustomTabWgt
    void setFrameRow(int nrow);//设置数据表的行数

    void setFrameFirstColContent(QStringList strlst);//设置数据表首列内容
    void setFrozenHeaderContent(QString str);//设置表头第一行的内容
    void setFrozenHeaderContent(QStringList strlst);//设置表头第二行的内容

    void setCloumnWidth(int ncloumn, int nwidth);//设置某列的宽度,同时调整冻结表头和数据表的列宽
    
    void setColumn(int ncloumn);//设置列，同时调整冻结表头和数据表的列数

    void appendHeaderConcent(QStringList strlst);
    void appendRowData();
    void updateRowData();


   
signals:
    void sigViewBtnClicked(int i);

private:
    QTableWidget* m_frozenTableWgt;// 使用TableWidget 作为header，并冻结


    int  m_nRowFrame;
    int  m_nColumnFrame;

    QStringList m_strlstName;//表头名称
    QString  m_strDeviceName;//设备名称
};

//完成m_frozenTableWgtde 的样式重绘，在paint方法中，根据每个单元格的背景不同进行绘制背景
class ItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ItemDelegate(int type, QObject* parent = 0);

    void paint(QPainter* painter,
        const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void OldPaint(QPainter* painter,
        const QStyleOptionViewItem& option, const QModelIndex& index) const;
private:
    int     m_type;//type=0: header    type=1：content
};
