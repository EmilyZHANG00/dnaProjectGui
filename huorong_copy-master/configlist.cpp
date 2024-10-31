#include "configlist.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QTime>
#include <QRandomGenerator>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

ConfigList::ConfigList(QWidget *parent) : QWidget(parent)
{
    m_model = new QStandardItemModel(this);
    m_pListView = new QListView(this);
    m_pListView->setModel(m_model);
    m_pListView->setItemDelegate(new ConfigListDelegate);
    m_pListView->setEditTriggers(QAbstractItemView::NoEditTriggers); // 不允许编辑

    QTime randtime;
    randtime = QTime::currentTime();
    //qsrand(randtime.msec()+randtime.second()*1000); //以当前时间ms为随机种子

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);;
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_pListView);

    setStyleSheet("QListView{background: #fff; border: 0; }"
                  "QListView::item:selected {background: #fff; border: 0; }"
                  "QListView::item:hover {background: #fffcf8; border: 1px solid #ffe7c1; }");

    m_pListView->setStyleSheet("QScrollBar:vertical\
                                {\
                                    width:10px;\
                                    background:rgba(0,0,0,0);\
                                    padding-bottom:9px;                        \
                                    background-position: right;\
                                }                                              \
                                QScrollBar::handle:vertical                    \
                                {                                              \
                                    width:10px;                                 \
                                    background: #bababa;                       \
                                }                                              \
                                QScrollBar::add-line:vertical\
                                {\
                                    height:0px;width:0px;\
                                    subcontrol-position:bottom;\
                                }\
                                QScrollBar::sub-line:vertical\
                                {\
                                    height:0px;width:0px;\
                                    subcontrol-position:top;\
                               }");
}

void ConfigList::AddItem(QString icon, QString title, QString tip)
{
    QStandardItem *item = new QStandardItem();
    item->setData(icon, Qt::UserRole + 1);
    item->setData(title, Qt::UserRole + 2);
    item->setData(tip, Qt::UserRole + 3);
    //item->setData(qrand() % 2, Qt::UserRole + 4);
    m_model->appendRow(item);
}

ConfigListDelegate::ConfigListDelegate()
{

}

ConfigListDelegate::~ConfigListDelegate()
{

}

void ConfigListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect rcClient = option.rect;
    QPixmap pixmap = QPixmap(index.data(Qt::UserRole+1).toString());
    QString strTitle = index.data(Qt::UserRole+2).toString();
    QString strTip = index.data(Qt::UserRole+3).toString();
    bool bChecked = index.data(Qt::UserRole+4).toBool();

    QStyleOptionViewItem viewoption(option);
    initStyleOption(&viewoption, index);
    if(option.state.testFlag(QStyle::State_HasFocus))
    {
        viewoption.state = viewoption.state^QStyle::State_HasFocus;
    }
    QStyledItemDelegate::paint(painter, viewoption, index);

    painter->save();
    painter->translate(rcClient.topLeft());

    painter->drawPixmap(10, 10, pixmap);

    {
        painter->save();

        //设置字体,颜色
        QFont font = painter->font();
        font.setPixelSize(14);
        painter->setFont(font);
        painter->drawText(85, 30, strTitle);

        font.setPixelSize(12);
        painter->setFont(font);
        painter->setPen(QColor("#777777"));
        painter->drawText(85, 50, strTip);

        painter->restore();
    }

    if (bChecked)
    {
        QPixmap pix(":/img/100/switch-ON.png");
        painter->drawPixmap(550, 36, pix.scaled(36, 32, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    else
    {
        QPixmap pix(":/img/100/switch-OFF.png");
        painter->drawPixmap(550, 36, pix.scaled(36, 32, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }

    painter->restore();
}

bool ConfigListDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    QRect rcClient = option.rect;

    QRect rcChecbox(rcClient.left() + 550, rcClient.top() + 40, 36, 20);

    //按钮点击事件；
    QMouseEvent *mevent = static_cast<QMouseEvent*>(event);
    if (rcChecbox.contains(mevent->pos()))
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            bool value = model->data(index, Qt::UserRole+4).toBool();
            model->setData(index, !value, Qt::UserRole+4);
            model->dataChanged(index, index);
        }
        else if (event->type() == QEvent::MouseMove)
        {
            QApplication::setOverrideCursor(Qt::PointingHandCursor);
        }
    }
    else
    {
        QApplication::setOverrideCursor(Qt::ArrowCursor);
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

QSize ConfigListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(580, 70);
}
