#ifndef CONFIGLIST_H
#define CONFIGLIST_H

#include <QWidget>
#include <QStandardItemModel>
#include <QListView>
#include <QStyledItemDelegate>

class ConfigListDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ConfigListDelegate();
    ~ConfigListDelegate();

private:    //描绘画面显示
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    //处理鼠标事件
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE;
};

class ConfigList : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigList(QWidget *parent = 0);
    void AddItem(QString icon, QString title, QString tip);

private:
    QStandardItemModel *m_model;
    QListView *m_pListView;
};

#endif // CONFIGLIST_H
