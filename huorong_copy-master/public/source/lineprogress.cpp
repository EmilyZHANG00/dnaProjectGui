#include "lineprogress.h"
#include <QPainter>

LineProgress::LineProgress(QWidget *parent) : QWidget(parent)
{
    m_nTotal = 0;
    m_nValue = 0;
}

void LineProgress::SetValue(int value, int total)
{
    m_nTotal = total;
    m_nValue = value;
    update();
}

void LineProgress::paintEvent(QPaintEvent *event)
{
    QColor bgColor("#000");
    QColor progressColor(0x3d, 0x77, 0xda);

    QPainter painter(this);         // 创建画家对象
    QRect rcClient = rect();

    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(bgColor);
    painter.drawRect(rcClient);
    painter.setBrush(progressColor);

    if (m_nValue > 0 && m_nTotal > 0)
    {
        double fRadio = (double)m_nValue / m_nTotal;
        rcClient.setWidth(rcClient.width() * fRadio);
        painter.drawRect(rcClient);
    }

    painter.restore();
}
