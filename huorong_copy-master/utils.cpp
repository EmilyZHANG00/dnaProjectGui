#include "utils.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

QLabel *CreateCustomLabel(QString strText, QString strColor, int nSize)
{
    QLabel *label = new QLabel(strText);
    label->setStyleSheet(QString("color: %1; font-size: %2px").arg(strColor).arg(nSize));
    return label;
}


QPushButton *CreateCustomButton(QString strText)
{
    QPushButton *btn = new QPushButton(strText);
    btn->setCursor(Qt::PointingHandCursor);
    btn->setStyleSheet(QString("QPushButton{border-style:none;"
                       "text-align: center;color: #f17f05;font-size: 14px;}"
                       "QPushButton:hover{color: #ffa924;}"
                       "QPushButton:pressed{color: #df4c0b;}"));
    return btn;
}

QPushButton *CreateDefaultButton(QString strText)
{
    QPushButton *btn = new QPushButton(strText);
    btn->setCursor(Qt::PointingHandCursor);
    btn->setStyleSheet(QString("QPushButton{border-style:none; min-width: 70px; min-height: 24px; background:#ffa924; border-radius: 3px;"
                       "text-align: center;color: #f1f1f1;font-size: 14px;}"
                       "QPushButton:hover{background: #ff9600;}"
                       "QPushButton:pressed{background: #ff9600;}"));
    return btn;
}

QWidget *CreateSeparator(bool bVertical)
{
    QWidget *line = new QWidget();
    if (bVertical)
        line->setFixedWidth(1);
    else
        line->setFixedHeight(1);
    line->setStyleSheet("background: #f0f0f0;");
    return line;
}

QPushButton *CreateGroupButton(QString strText, bool bFirst = false, bool bLast = false)
{
    QPushButton *btn = new QPushButton(strText);
    btn->setCursor(Qt::PointingHandCursor);
    btn->setCheckable(true);
    if (bFirst)
    {
        btn->setStyleSheet(QString("QPushButton{border-style:none; min-width: 48px; min-height: 20px; background:#ffffff;"
                           "text-align: center;color: #a68358;font-size: 12px; border: 1px solid #c0a686; border-top-left-radius: 3px;  border-bottom-left-radius: 3px;}"
                           "QPushButton:hover{background: #ceb8a5; color: #efe4d8;}"
                           "QPushButton:checked{background: #bda184; color: #efe4d8;}"));
    }
    else if (bLast)
    {
        btn->setStyleSheet(QString("QPushButton{border-style:none; min-width: 48px; min-height: 20px; background:#ffffff;"
                           "text-align: center;color: #a68358;font-size: 12px; border: 1px solid #c0a686; border-left-width: 0; border-top-right-radius: 3px;  border-bottom-right-radius: 3px; }"
                           "QPushButton:hover{background: #ceb8a5; color: #efe4d8;}"
                           "QPushButton:checked{background: #bda184; color: #efe4d8;}"));
    }
    else
    {
        btn->setStyleSheet(QString("QPushButton{border-style:none; min-width: 48px; min-height: 20px; background:#ffffff;"
                           "text-align: center;color: #a68358;font-size: 12px; border: 1px solid #c0a686; border-left-width: 0;}"
                           "QPushButton:hover{background: #ceb8a5; color: #efe4d8;}"
                           "QPushButton:checked{background: #bda184; color: #efe4d8;}"));
    }

    return btn;
}


QWidget *CreateButtonGroup(QStringList btns, QButtonGroup **group)
{
    QWidget *line = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout(line);
    QButtonGroup *_group = new QButtonGroup();

    int nIndex = 0;
    int nCount = btns.length();
    foreach (QString var, btns) {
        QPushButton *btn1 = CreateGroupButton(var, nIndex == 0, nIndex == nCount - 1);
        mainLayout->addWidget(btn1);

        if (0 == nIndex)
            btn1->setChecked(true);

        _group->addButton(btn1, nIndex++);
    }

    mainLayout->addStretch(1);
    mainLayout->setSpacing(0);
    //mainLayout->setMargin(0);

    *group = _group;
    return line;
}

QCheckBox *CreateCheckBox(QString strText)
{
    QCheckBox *btn = new QCheckBox(strText);
    btn->setCursor(Qt::PointingHandCursor);
    btn->setStyleSheet(QString( "QCheckBox{ color: #777777; }"
                       "QCheckBox::indicator{width: 20px; height: 20px; color: #777777; }"
                       "QCheckBox::indicator:unchecked{border-image:url(:/img/100/checkbox-un.png);}"
                       "QCheckBox::indicator:unchecked:hover{border-image:url(:/img/100/checkbox-un_h.png);}"
                       "QCheckBox::indicator:checked{border-image:url(:/img/100/checkbox_n.png);}"
                       "QCheckBox::indicator:checked:hover{:/img/100/checkbox_h.png}"));
    return btn;
}

QAction *CreateAction(const QString &text, QObject *parent, const QString &icon)
{
    QAction *pCollect = new QAction(text, parent);
    pCollect->setIcon(QIcon(QPixmap(icon).copy(0, 0, 18, 18)));

    return pCollect;
}
