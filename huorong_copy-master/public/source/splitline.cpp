#include "splitline.h"
#include <QPainter>

Splitline::Splitline(QWidget *parent) : QWidget(parent)
{
    m_nMargin = 10;
    m_bHorizontal = false;
    m_color = QColor("#666769");

    SetHorizontalDirection(m_bHorizontal);
}

void Splitline::SetHorizontalDirection(bool bHorizontal)
{
    m_bHorizontal = bHorizontal;
    update();
}

void Splitline::SetColor(QColor color)
{
    m_color = color;
    update();
}

void Splitline::SetMargin(int nMargin)
{
    m_nMargin = nMargin;
    update();
}

void Splitline::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);         // 创建画家对象
    QRect rcClient = rect();
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_color);

    if (m_bHorizontal)
    {
        rcClient = rcClient.marginsRemoved(QMargins(m_nMargin, 0, m_nMargin, 0));
        rcClient.setTop(rcClient.top() + rcClient.height() / 2);
        rcClient.setHeight(1);
    }
    else
    {
        rcClient = rcClient.marginsRemoved(QMargins(0, m_nMargin, 0, m_nMargin));
        rcClient.setLeft(rcClient.left() + rcClient.width() / 2);
        rcClient.setWidth(1);
    }

    painter.drawRect(rcClient);
    painter.restore();
}
