#include "dynamicbtn.h"
#include <QPainter>
#include <QTimerEvent>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QTimer>
#include <QCheckBox>
#include <QPushButton>
#include <QDebug>
#include "utils.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif


DynamicBtn::DynamicBtn(QWidget *parent) : QWidget(parent)
{
    m_nRotate = 0;
    m_bRuning = false;
    m_bStart = false;

    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setWindowFlags(Qt::FramelessWindowHint);
    setStyleSheet("DynamicBtn{background: #fdfdfd; border: 1px solid #f0f0f0;}");
    m_colorBg = QColor("#eeeeee");
    m_colorBorder = QColor("#f6a424");
    m_nTimeId = startTimer(5);

    m_labelIcon = new QLabel();
    m_labelTitle = CreateCustomLabel("", "#444444", 14);
    m_labelTip = CreateCustomLabel("", "#777777", 12);
    m_labelIcon->setFixedWidth(50);
    m_labelTitle->setAlignment(Qt::AlignCenter);
    m_labelTip->setAlignment(Qt::AlignCenter);

    QHBoxLayout *layoutTop = new QHBoxLayout();
    layoutTop->addStretch(1);
    layoutTop->addWidget(m_labelIcon);
    layoutTop->addStretch(1);

    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    layoutMain->addStretch(1);
    layoutMain->addLayout(layoutTop);
    layoutMain->addWidget(m_labelTitle);
    layoutMain->addWidget(m_labelTip);
    layoutMain->addStretch(1);
}

void DynamicBtn::SetParam(QString icon, QString title, QString tip)
{
    m_icon = icon;
    m_labelIcon->setPixmap(QPixmap(icon));

    m_labelTitle->setText(title);
    m_labelTip->setText(tip);
}

void DynamicBtn::Start()
{
    m_bStart = true;
    m_bRuning = true;
    // m_labelIcon->setPixmap(QPixmap(m_icon).copy(50, 0, 50, 50));
    // m_labelTip->setText("正在扫描");
    update();
}

void DynamicBtn::Stop()
{
    if (!m_bStart) return;

    m_bStart = false;
    m_bRuning = false;

    // m_labelTip->setText("安全");

    update();
}

void DynamicBtn::Pause()
{
    m_bRuning = false;
    update();
}

void DynamicBtn::Clear()
{
    m_bStart = false;
    m_bRuning = false;
    m_labelIcon->setPixmap(QPixmap(m_icon));
    // m_labelTip->setText("等待扫描");
    update();
}

void DynamicBtn::paintEvent(QPaintEvent *ev)
{
    QWidget::paintEvent(ev);

    if (m_bStart)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QRect rcClient = rect();

        QRegion region = rcClient;
        QRegion region2 = rcClient.marginsRemoved(QMargins(2, 2, 2, 2));
        painter.setClipRegion(region.subtracted(region2));

        painter.save();
        painter.translate(rcClient.center());
        painter.setPen(Qt::NoPen);
        painter.setBrush(m_colorBorder);

        QConicalGradient gradient(0, 0, 0);
        gradient.setColorAt(0, QColor("#fff0db"));
        gradient.setColorAt(1.0, m_colorBorder);
        painter.setBrush(gradient);

        painter.rotate(m_nRotate);
        int nW = qMax(rcClient.width(), rcClient.height());
        painter.drawEllipse(QPoint(0, 0), nW, nW);
        painter.restore();
    }
}

void DynamicBtn::timerEvent(QTimerEvent *event)
{
    if (m_bRuning && m_nTimeId == event->timerId())
    {
        m_nRotate++;
        if (m_nRotate > 360)
            m_nRotate = 0;

        update();
    }
}
