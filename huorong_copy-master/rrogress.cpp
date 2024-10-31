#include "rrogress.h"
#include <QPainter>

Progress::Progress(QWidget *parent) : QWidget(parent)
{
    m_nProgress = 50;
}

void Progress::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QRect rcClient = rect();

    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#f0f0f0"));
    painter.drawRect(rcClient);

    painter.setBrush(QColor("#ffa924"));
    int nWidth = (1- (double)m_nProgress / 100.0) * width();
    painter.drawRect(rcClient.marginsRemoved(QMargins(0, 0, nWidth, 0)));
    painter.restore();
}
