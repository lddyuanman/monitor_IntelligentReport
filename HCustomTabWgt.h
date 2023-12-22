#pragma once
#include <QTableWidget>
#include <QStyledItemDelegate>

#define ROWCOUNTPERPAGE 15
#define ROWHEIGHT 60//行高
#define INT_FIRST_COLUMN_WHEIGHT 100//表头和表内容首列宽度

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
    void initOldExample();
    void initNewFrame();
    void  initFrame(); //数据显示表HCustomTabWgt

    void appendHeaderConcent(QStringList strlst);
    void appendRowData();
    void updateRowData();


   
signals:
    void sigViewBtnClicked(int i);

private:
    QTableWidget* m_frozenTableWgt;// 使用TableWidget 作为header，并冻结


    int  m_nRowFrame;
    int  m_nColumnFrame;
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
