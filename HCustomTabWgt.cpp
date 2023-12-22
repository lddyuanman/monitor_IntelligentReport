#include"HCustomTabWgt.h"
#include<QHeaderView>
#include<QScrollBar>
#include<QPainter>
#include<QPushButton>
#include<QHBoxLayout>

HCustomTabWgt::HCustomTabWgt(QWidget* parent,int nrow, int ncolumn)
    : QTableWidget(parent) , m_nRowFrame(nrow) , m_nColumnFrame(ncolumn)
{
    initFrozenFrame();
    initFrame();

    for (int i = 0; i < 10; i++)
        appendRowData();

}

HCustomTabWgt::~HCustomTabWgt()
{

}

void HCustomTabWgt::appendRowData()
{
    if (rowCount() >= ROWCOUNTPERPAGE)
        return;

    //添加到最后一行
    int rowIndex = rowCount();
    setRowCount(rowIndex + 1);

    //设置行高
    setRowHeight(rowIndex, ROWHEIGHT);

    //填充最后一行的内容
    for (int col = 0; col < 10; col++) {
        setItem(rowIndex, col, new QTableWidgetItem(QString("item%1%2").arg(rowIndex).arg(col)));
        item(rowIndex, col)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }
}

void HCustomTabWgt::initFrame()
{
    clearContents();
    setColumnCount(10);
    horizontalHeader()->setVisible(true);//表头不可见
    int headerHeight = m_frozenTableWgt->rowHeight(0) +
        m_frozenTableWgt->rowHeight(1);//设置成被m_frozenTableWgt遮挡住
    horizontalHeader()->setFixedHeight(headerHeight);
    verticalHeader()->setVisible(false);//表头不可见
    //setShowGrid(false);//网格线不可见
    setEditTriggers(QAbstractItemView::NoEditTriggers);//设置单元格不可编辑
    setSelectionMode(QAbstractItemView::SingleSelection);//单选
    setSelectionBehavior(QAbstractItemView::SelectRows);//选行`
    horizontalHeader()->setStretchLastSection(true);//最后一个单元格扩展
    setFocusPolicy(Qt::NoFocus);//解决选中虚框问题
    setFrameShape(QFrame::NoFrame);//去除边框

    setVerticalScrollMode(ScrollPerPixel);
    setHorizontalScrollMode(ScrollPerPixel);

    //设置行高模式为自动调整（自动拉伸列宽填充窗口，无法手动调整）
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // 设置列宽模式为自动调整（自动拉伸列宽填充窗口，无法手动调整）
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    setColumnWidth(0, INT_FIRST_COLUMN_WHEIGHT);

    setItemDelegate(new ItemDelegate(1));//设置绘画代理（主要在代理中画出来header）
}

void HCustomTabWgt::initOldExample()
{
    m_frozenTableWgt->setColumnCount(10);//header10列
    m_frozenTableWgt->setRowCount(2);//header2行

    m_frozenTableWgt->setRowHeight(0, 42);//第一行设置高度42px
    m_frozenTableWgt->setRowHeight(1, 42);//第二行设置高度42px  

    for (int row = 2; row < m_frozenTableWgt->rowCount(); ++row)//隐藏2行后的行
        m_frozenTableWgt->setRowHidden(row, true);

    //===================设置header内容=================//
    //合并单元格
    m_frozenTableWgt->setSpan(0, 0, 2, 1);//老师ID
    m_frozenTableWgt->setSpan(0, 1, 2, 1);//老师姓名
    m_frozenTableWgt->setSpan(0, 2, 2, 1);//老师姓名
    m_frozenTableWgt->setSpan(0, 3, 1, 4);//最新日期（8月20）
    m_frozenTableWgt->setSpan(0, 7, 1, 2);//前一日（8月19）
    m_frozenTableWgt->setSpan(0, 9, 2, 1);//操作

    m_frozenTableWgt->setItem(0, 0, new QTableWidgetItem(QString::fromLocal8Bit("老师ID")));
    m_frozenTableWgt->setItem(0, 1, new QTableWidgetItem(QString::fromLocal8Bit("老师姓名")));
    m_frozenTableWgt->setItem(0, 2, new QTableWidgetItem(QString::fromLocal8Bit("老师姓名")));
    m_frozenTableWgt->setItem(0, 3, new QTableWidgetItem(QString::fromLocal8Bit("8月20日")));
    m_frozenTableWgt->setItem(0, 7, new QTableWidgetItem(QString::fromLocal8Bit("8月19日")));
    m_frozenTableWgt->setItem(0, 9, new QTableWidgetItem(QString::fromLocal8Bit("操作")));
    m_frozenTableWgt->setItem(1, 3, new QTableWidgetItem(QString::fromLocal8Bit("续报率")));
    m_frozenTableWgt->setItem(1, 4, new QTableWidgetItem(QString::fromLocal8Bit("新学员续报率")));
    m_frozenTableWgt->setItem(1, 5, new QTableWidgetItem(QString::fromLocal8Bit("续报增长人数")));
    m_frozenTableWgt->setItem(1, 6, new QTableWidgetItem(QString::fromLocal8Bit("续报增长率")));
    m_frozenTableWgt->setItem(1, 7, new QTableWidgetItem(QString::fromLocal8Bit("续报增长率")));
    m_frozenTableWgt->setItem(1, 8, new QTableWidgetItem(QString::fromLocal8Bit("新学员续报率")));
}

void HCustomTabWgt::initNewFrame()
{
    m_frozenTableWgt->setColumnCount(10);//header10列
    m_frozenTableWgt->setRowCount(2);//header2行

    m_frozenTableWgt->setRowHeight(0, 42);//第一行设置高度42px
    m_frozenTableWgt->setRowHeight(1, 42);//第二行设置高度42px

    // 设置列宽模式为自动调整（自动拉伸列宽填充窗口，无法手动调整）
    //为保持表头列宽和数据内容列宽一致，首列宽度必须保持一致
    m_frozenTableWgt->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_frozenTableWgt->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    m_frozenTableWgt->setColumnWidth(0, INT_FIRST_COLUMN_WHEIGHT); //第一列设置高度42px

    for (int row = 2; row < m_frozenTableWgt->rowCount(); ++row)//隐藏2行后的行
        m_frozenTableWgt->setRowHidden(row, true);
    //===================设置header内容=================//
    //合并单元格
    m_frozenTableWgt->setSpan(0, 0, 2, 1);//名称，时间
    m_frozenTableWgt->setSpan(0, 1, 1, 9);//设备名称

    m_frozenTableWgt->setItem(0, 0, new QTableWidgetItem(QString::fromLocal8Bit("名称时间")));
    m_frozenTableWgt->setItem(0, 1, new QTableWidgetItem(QString::fromLocal8Bit("设备名称")));
    m_frozenTableWgt->setItem(1, 1, new QTableWidgetItem(QString::fromLocal8Bit("UA")));
    m_frozenTableWgt->setItem(1, 2, new QTableWidgetItem(QString::fromLocal8Bit("UB")));
    m_frozenTableWgt->setItem(1, 3, new QTableWidgetItem(QString::fromLocal8Bit("UC")));
    m_frozenTableWgt->setItem(1, 4, new QTableWidgetItem(QString::fromLocal8Bit("IA")));
    m_frozenTableWgt->setItem(1, 5, new QTableWidgetItem(QString::fromLocal8Bit("IB")));
    m_frozenTableWgt->setItem(1, 6, new QTableWidgetItem(QString::fromLocal8Bit("IC")));
    m_frozenTableWgt->setItem(1, 7, new QTableWidgetItem(QString::fromLocal8Bit("P")));
    m_frozenTableWgt->setItem(1, 8, new QTableWidgetItem(QString::fromLocal8Bit("Q")));
    m_frozenTableWgt->setItem(1, 9, new QTableWidgetItem(QString::fromLocal8Bit("Cos")));
}

void HCustomTabWgt::initFrozenFrame()
{
    m_frozenTableWgt = new QTableWidget(this);
    m_frozenTableWgt->horizontalHeader()->setVisible(false);//表头不可见
    m_frozenTableWgt->verticalHeader()->setVisible(false);//表头不可见
    //m_frozenTableWgt->setShowGrid(false);//网格线不可见
    m_frozenTableWgt->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置单元格不可编辑
    m_frozenTableWgt->horizontalHeader()->setStretchLastSection(true);//最后一个单元格扩展
    m_frozenTableWgt->setFocusPolicy(Qt::NoFocus);//解决选中虚框问题
    m_frozenTableWgt->setFrameShape(QFrame::NoFrame);//去除边框 尴尬
    m_frozenTableWgt->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏滚动条
    m_frozenTableWgt->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//
    m_frozenTableWgt->setHorizontalScrollMode(ScrollPerPixel);

    m_frozenTableWgt->setItemDelegate(new ItemDelegate(0));//设置绘画代理（主要在代理中画出来header）

    viewport()->stackUnder(m_frozenTableWgt);//设置窗口层次

   // initOldExample();
    initNewFrame();
    
    //连接信号槽。用于滚动条联动
    connect(m_frozenTableWgt->verticalScrollBar(), &QAbstractSlider::valueChanged, verticalScrollBar(), &QAbstractSlider::setValue);
    connect(verticalScrollBar(), &QAbstractSlider::valueChanged, m_frozenTableWgt->verticalScrollBar(), &QAbstractSlider::setValue);

    updateFrozenTableGeometry();//更新位置
    m_frozenTableWgt->show();
}

void HCustomTabWgt::updateFrozenTableGeometry()
{
    m_frozenTableWgt->setGeometry(frameWidth(),
        frameWidth(),
        viewport()->width(),
        horizontalHeader()->height());
}

void HCustomTabWgt::resizeEvent(QResizeEvent* event)
{
    QTableView::resizeEvent(event);
    updateFrozenTableGeometry();
}

QModelIndex HCustomTabWgt::moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
    //只有当鼠标向上移动，并且HCustomTabWgt还未显示到第一行，并且可视区域的顶点应该小于m_frozenTableWgt的第一行，才允许继续向上移动
    QModelIndex current = QTableView::moveCursor(cursorAction, modifiers);

    if (cursorAction == MoveUp && current.row() > 0
        && visualRect(current).topLeft().y() < m_frozenTableWgt->rowHeight(1)) {
        const int newValue = verticalScrollBar()->value() + visualRect(current).topLeft().y()
            - m_frozenTableWgt->rowHeight(0) - m_frozenTableWgt->rowHeight(1);
        verticalScrollBar()->setValue(newValue);
    }
   // updateFrozenTableGeometry();
    return current;
}

void HCustomTabWgt::scrollTo(const QModelIndex& index, QAbstractItemView::ScrollHint hint)
{
    if (index.row() > 0)
        QTableView::scrollTo(index, hint);
    //updateFrozenTableGeometry();
}


//绘制m_frozenTableWgtde 的样式，字体、背景颜色等
ItemDelegate::ItemDelegate(int type, QObject* parent)
    : QStyledItemDelegate(parent),
    m_type(type)
{

}

void ItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (0 == m_type) //header tablewidget
    {
        int rowIndex = index.row();//行号
        int colIndex = index.column();//列号
        if (rowIndex == 0 || rowIndex == 1)//前两行作为header
        {
            //背景
            QColor color;
            color.setRgb(231, 238, 251);
            
            //绘制背景
            painter->setPen(color);
            painter->setBrush(QBrush(color));
            painter->drawRect(option.rect);            

            //字体
            painter->setPen(QColor(51, 51, 51));
            QTextOption op;
            op.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

            QFont font;
            font.setFamily("Microsoft YaHei");
            font.setPixelSize(14);
            font.setBold(true);
            painter->setFont(font);

            QRect rect;
            rect = option.rect;
            painter->drawText(rect, index.data(Qt::DisplayRole).toString(), op);
        }
    }
    else {  //content table widget
        //文字
        painter->setPen(QColor(102, 102, 102));
        QTextOption op;
        op.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        QFont font;
        font.setFamily("Microsoft YaHei");
        font.setPixelSize(12);
        painter->setFont(font);

        if (option.state & QStyle::State_Selected) {
            painter->fillRect(option.rect, QBrush(QColor(239, 244, 255)));
        }

        painter->drawText(option.rect, index.data(Qt::DisplayRole).toString(), op);

        //底边框
        painter->setPen(QColor(248, 251, 255));
        painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());

    }

}

void ItemDelegate::OldPaint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index)const
{
    if (0 == m_type) //header tablewidget
    {
        int rowIndex = index.row();//行号
        int colIndex = index.column();//列号
        if (rowIndex == 0 || rowIndex == 1)//前两行作为header
        {
            //背景
            QColor color;

            if (rowIndex == 0 && (colIndex == 0 || //老师ID
                colIndex == 1 || //老师姓名
                colIndex == 2 || //课程类型
                colIndex == 9))  //操作
            {
                color.setRgb(231, 238, 251);
            }
            else if ((rowIndex == 0 && colIndex == 3) || //8月20日
                (rowIndex == 1 && (colIndex == 3 || //续报率
                    colIndex == 4 || //新学员续报率
                    colIndex == 5 || //续报增长人数
                    colIndex == 6))) //续报增长率
            {
                color.setRgb(214, 228, 253);
            }
            else if ((rowIndex == 0 && colIndex == 7) || //8月19日
                (rowIndex == 1 && (colIndex == 7 || //续报率
                    colIndex == 8))) //新学员续报率
            {
                color.setRgb(203, 221, 255);
            }

            //绘制背景
            painter->setPen(color);
            painter->setBrush(QBrush(color));
            painter->drawRect(option.rect);

            //右侧spacer
            if ((rowIndex == 0 && (colIndex == 0 || colIndex == 1))) {
                int startX = option.rect.right();
                int startY = option.rect.y() + (option.rect.height() - 40) / 2;
                int endX = startX;
                int endY = startY + 40;
                QLinearGradient linearGradient(startX, startY, endX, endY);
                linearGradient.setColorAt(0, QColor(164, 188, 240, 0));
                linearGradient.setColorAt(0.5, QColor(164, 188, 240, 255));
                linearGradient.setColorAt(1, QColor(164, 188, 240, 0));
                painter->setBrush(linearGradient);
                painter->drawRect(option.rect.right() - 2, startY, 2, 40);

            }
            else if (rowIndex == 1 && (colIndex == 3 ||
                colIndex == 4 ||
                colIndex == 5 ||
                colIndex == 7)) {

                int startX = option.rect.right();
                int startY = option.rect.y() + (option.rect.height() - 28) / 2;
                int endX = startX;
                int endY = startY + 28;
                QLinearGradient linearGradient(startX, startY, endX, endY);
                linearGradient.setColorAt(0, QColor(164, 188, 240, 0));
                linearGradient.setColorAt(0.5, QColor(164, 188, 240, 255));
                linearGradient.setColorAt(1, QColor(164, 188, 240, 0));
                painter->setBrush(linearGradient);
                painter->drawRect(option.rect.right() - 2, startY, 2, 28);
            }

            //字体
            painter->setPen(QColor(51, 51, 51));
            QTextOption op;
            op.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

            QFont font;
            font.setFamily("Microsoft YaHei");
            font.setPixelSize(14);
            font.setBold(true);
            painter->setFont(font);

            QRect rect;
            if (rowIndex == 0 && colIndex == 9) {//"操作" 左对齐
                rect = QRect(option.rect.x(), option.rect.y(), 100, option.rect.height());
            }
            else {//其他的居中
                rect = option.rect;
            }

            painter->drawText(rect, index.data(Qt::DisplayRole).toString(), op);

        }

    }
    else {  //content table widget
        //文字
        painter->setPen(QColor(102, 102, 102));
        QTextOption op;
        op.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        QFont font;
        font.setFamily("Microsoft YaHei");
        font.setPixelSize(12);
        painter->setFont(font);

        if (option.state & QStyle::State_Selected) {
            painter->fillRect(option.rect, QBrush(QColor(239, 244, 255)));
        }

        painter->drawText(option.rect, index.data(Qt::DisplayRole).toString(), op);

        //底边框
        painter->setPen(QColor(248, 251, 255));
        painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());

    }
}