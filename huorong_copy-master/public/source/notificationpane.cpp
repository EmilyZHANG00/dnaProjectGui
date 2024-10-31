#include "notificationpane.h"
#include <QGuiApplication>
#include <QScreen>
#include <QDebug>
#include <QPropertyAnimation>
#include <QDateTime>
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScreen>
#include <QApplication>
#include <QPushButton>
#include <QPainterPath>

NotificationPane::NotificationPane(QWidget *parent) : QWidget(parent)
{
    m_pTimerHide = NULL;
    m_btnClose = NULL;
    m_nIndex = 0;

    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setWindowFlags(windowFlags() | Qt::ToolTip | Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    setProperty("form", "iconfontpane");
    setAttribute(Qt::WA_TranslucentBackground, true);

    m_pTimerHide = new QTimer(this);
    connect(m_pTimerHide, SIGNAL(timeout()), this, SLOT(OnTimerHideTimeOut()));

    setFixedSize(400, 150);

    m_btnClose = new QPushButton(this);
    m_btnClose->setFixedSize(40, 40);
    m_btnClose->setProperty("white_bk", "true");
    m_btnClose->hide();

    QHBoxLayout *layoutTop = new QHBoxLayout();
    layoutTop->addStretch();
    layoutTop->addWidget(m_btnClose);
    layoutTop->setSpacing(0);
    layoutTop->setContentsMargins(0, 10, 20, 0);

    QVBoxLayout *layoutMain = new QVBoxLayout();
    layoutMain->addLayout(layoutTop);
    layoutMain->addStretch();
    layoutMain->setSpacing(0);
    layoutMain->setContentsMargins(0, 0, 0, 0);
    setLayout(layoutMain);
}

void NotificationPane::Start(int msec)
{
    m_pTimerHide->stop();

    if (m_tMsgInfo.bAutoClose)
    {
        m_pTimerHide->setInterval(msec);
        m_pTimerHide->start();
    }

    update();
}

void NotificationPane::Notice(NotificationPane::TMsgInfo tMsgInfo)
{
    m_tMsgInfo = tMsgInfo;
}

void NotificationPane::enterEvent(QEvent *event)
{
    m_pTimerHide->stop();
}

void NotificationPane::leaveEvent(QEvent *event)
{
    if (m_tMsgInfo.bAutoClose)
    {
        m_pTimerHide->start();
    }
    else
    {
        m_pTimerHide->setInterval(2000);
        m_pTimerHide->start();
    }
}

void NotificationPane::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);         // 创建画家对象
    //painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing, true); // 抗锯齿和使用平滑转换算法

    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(10, 10, this->width() - 20, this->height() - 20);

    painter.fillPath(path, QBrush(Qt::white));


    painter.save();
    painter.setPen(QColor("#000"));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(10, 10, this->width() - 20, this->height() - 20);
    painter.restore();
    QFont ft = painter.font();

    QRect rcClient = rect();


    painter.save();
    QRect rcTitle(rcClient);
    rcTitle.setTop(rcClient.top() + 25);
    rcTitle.setLeft(rcClient.left() + 25);
    rcTitle.setBottom(rcTitle.top() + 27);
    rcTitle.setRight(rcClient.right() - 25);

    QFont ftTemp = ft;
    ftTemp.setPointSize(12);
    ftTemp.setBold(false);
    painter.setFont(ftTemp);

    painter.setPen(QColor("#262626"));
    painter.drawText(rcTitle, Qt::AlignLeft | Qt::TextWordWrap, m_tMsgInfo.strTitle);
    painter.setFont(ft);
    painter.restore();

    painter.save();
    QRect rcContent(rcClient);
    rcContent.setTop(rcTitle.bottom() + 10);
    rcContent.setLeft(rcClient.left() + 25);
    rcContent.setBottom(rcContent.top() + 50);
    rcContent.setRight(rcClient.right() - 25);

    int nFontSize = 15;
    if (m_tMsgInfo.strContent.length() > 13)
        nFontSize = 12;
    if (m_tMsgInfo.strContent.length() > 18)
        nFontSize = 10;
    if (m_tMsgInfo.strContent.length() > 20)
        nFontSize = 9;

    ftTemp.setPointSize(8);
    ftTemp.setBold(false);
    painter.setFont(ftTemp);

    painter.setPen(QColor("#262626"));
    painter.drawText(rcContent, Qt::AlignLeft | Qt::TextWordWrap, m_tMsgInfo.strContent);
    painter.setFont(ft);
    painter.restore();
}

void NotificationPane::OnTimerHideTimeOut()
{
    m_pTimerHide->stop();
    hide();
    emit SignalHide(m_nIndex);
}


////////////////////////////////////////////////////////////////////


NotificationMgr* NotificationMgr::m_pNotificationMgr = NULL;
NotificationMgr::NotificationMgr(QWidget *parent)
{
    m_bSingleMode = true;

    m_listNotification.clear();

    // 默认创建10个
    for (int i = 0; i < MAX_NOTICE; i++)
    {
        NotificationPane *pNotice = new NotificationPane(parent);
        pNotice->hide();
        pNotice->SetId(i);

        connect(pNotice, SIGNAL(SignalHide(int)), this, SLOT(OnItemHide(int)));

        TNoteItem tItem;
        tItem.pNotificationPane = pNotice;
        m_listNotification << tItem;
    }
}

void NotificationMgr::Init(QWidget *parent)
{
    if (NULL == m_pNotificationMgr)
    {
        m_pNotificationMgr = new NotificationMgr(parent);
    }
}

NotificationMgr *NotificationMgr::GetInstance()
{
    if (NULL == m_pNotificationMgr)
    {
        m_pNotificationMgr = new NotificationMgr();
    }

    return m_pNotificationMgr;
}

void NotificationMgr::ExitInstance()
{
    if (m_pNotificationMgr != NULL)
    {
        delete m_pNotificationMgr;
        m_pNotificationMgr = NULL;
    }
}

bool NotificationMgr::CompareData(const TNoteItem &tItem1, const TNoteItem &tItem2)
{
    if (tItem1.currentTime < tItem2.currentTime)
    {
        return true;
    }

    return false;
}

void NotificationMgr::Notice(QString strContent, QString strTitle, bool bAutoClose, uint dwFlag)
{
    int nPos = 10;
    int nStartHeight = 10;

    for (int i = 0; i < m_listNotification.size(); i++)
    {
        if (m_bSingleMode)
        {
            m_listNotification[0].bShow = true;
            m_listNotification[0].bNew = true;
            m_listNotification[0].pNotificationPane->hide();
            m_listNotification[0].dwFlag = dwFlag;

            NotificationPane::TMsgInfo tMsgInfo;
            tMsgInfo.bAutoClose = bAutoClose;
            tMsgInfo.strContent = strContent;
            tMsgInfo.strTitle = strTitle;
            m_listNotification[0].pNotificationPane->Notice(tMsgInfo);
            break;
        }
        else
        {
            TNoteItem tItem = m_listNotification.at(i);
            NotificationPane *pNotice = tItem.pNotificationPane;

            if (!tItem.bShow)
            {
                m_listNotification[i].bShow = true;
                m_listNotification[i].bNew = true;
                m_listNotification[i].currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                m_listNotification[i].dwFlag = dwFlag;

                NotificationPane::TMsgInfo tMsgInfo;
                tMsgInfo.bAutoClose = bAutoClose;
                tMsgInfo.strContent = strContent;
                tMsgInfo.strTitle = strTitle;
                pNotice->Notice(tMsgInfo);

                break;
            }
            else
            {
                QSize size = pNotice->size();
                nStartHeight += size.height();
                nStartHeight += nPos;
            }
        }
    }

    ShowAll();
}

void NotificationMgr::ShowAll()
{
    QScreen *desktopWidget = QGuiApplication::primaryScreen();
    QRect screenRect = desktopWidget->availableGeometry();

    int dWidth = screenRect.width();
    int dHeight = screenRect.height();

    int nPos = 10;
    int nStartHeight = 10;
    for (int i = 0; i < m_listNotification.size(); i++)
    {
        TNoteItem tItem = m_listNotification.at(i);
        NotificationPane *pNotice = tItem.pNotificationPane;
        if (tItem.bShow)
        {
           pNotice->show();

           const int nSpace = 10;
           QSize size = pNotice->size();
           QRect rcStart, rcEnd;
           QPoint ptStart, ptEnd;
           if (tItem.dwFlag & AlignLeft)
           {
               ptStart.setX(-size.width());
               ptEnd.setX(nSpace);
           }
           if (tItem.dwFlag & AlignTop)
           {
               ptStart.setY(nStartHeight);
               ptEnd.setY(nStartHeight);
           }
           if (tItem.dwFlag & AlignRight)
           {
               ptStart.setX(dWidth);
               ptEnd.setX(dWidth - size.width() - nSpace);
           }
           if (tItem.dwFlag & AlignBottom)
           {
               ptStart.setY(dHeight - size.height() - nStartHeight);
               ptEnd.setY(dHeight - size.height() - nStartHeight);
           }

           rcStart = QRect(ptStart.x(), ptStart.y(), size.width(), size.height());
           rcEnd = QRect(ptEnd.x(), ptEnd.y(), size.width(), size.height());

           if (tItem.bNew)
           {
               QPropertyAnimation *animation = new QPropertyAnimation(pNotice, "geometry");
               animation->setDuration(200);
               animation->setStartValue(rcStart);
               animation->setEndValue(rcEnd);
               animation->start(QAbstractAnimation::DeleteWhenStopped);

               pNotice->Start(tItem.nInterval);
               m_listNotification[i].bNew = false;
           }
           else
           {
               QSize size = pNotice->size();
               pNotice->move(dWidth - size.width() - nSpace, nStartHeight);
           }

           nStartHeight += size.height();
           nStartHeight += nPos;

           if (m_bSingleMode)
           {
               break;
           }
        }
    }
}

void NotificationMgr::OnItemHide(int nIndex)
{
    m_listNotification[nIndex].bShow = false;
    ShowAll();
}
