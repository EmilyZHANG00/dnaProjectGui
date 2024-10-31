#include "appinit.h"
#include "qmutex.h"
#include "qapplication.h"
#include "qevent.h"
#include "qwidget.h"
#include "qtimer.h"
#include <QDebug>


#define STANDBY_TRIGGER_TIME  2 * 1000     // 鼠标无操作，自动进入屏保界面

AppInit *AppInit::self = 0;
AppInit *AppInit::Instance()
{
    if (!self) {
        QMutex mutex;
        QMutexLocker locker(&mutex);
        if (!self) {
            self = new AppInit;
        }
    }

    return self;
}

AppInit::AppInit(QObject *parent) : QObject(parent)
{
    m_timeMouseTrigger = QTime::currentTime();
    m_bNoUserOperationing = false;
    m_bHasUserOperation = false;

    m_pMouseWatcher = new QTimer(this);
    connect(m_pMouseWatcher, &QTimer::timeout, [=]()
    {
        if (!m_timeMouseTrigger.isNull())
        {
            if (!m_bNoUserOperationing && qAbs(m_timeMouseTrigger.msecsTo(QTime::currentTime())) > STANDBY_TRIGGER_TIME)
            {
                emit SignalNoUserOperation();
                m_bNoUserOperationing = true;
                m_bHasUserOperation = true;
            }
        }
    });
}

bool AppInit::eventFilter(QObject *obj, QEvent *evt)
{
    switch (evt->type())
    {
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseButtonDblClick:
        case QEvent::MouseMove:
        {
            m_timeMouseTrigger = QTime::currentTime();

            if (m_bHasUserOperation)
            {
                emit SignalUserOperation();
                m_bNoUserOperationing = false;
                m_bHasUserOperation = false;
            }
        }
        break;
        case QEvent::KeyPress:
        case QEvent::KeyRelease:
        {
            QKeyEvent *event = static_cast<QKeyEvent *>(evt);
            if(event->key() != Qt::Key_ScrollLock)
            {
                m_timeMouseTrigger = QTime::currentTime();

                if (m_bHasUserOperation)
                {
                    emit SignalUserOperation();
                    m_bNoUserOperationing = false;
                    m_bHasUserOperation = false;
                }
            }
        }
        break;
    }

    QWidget *w = (QWidget *)obj;
    if (!w->property("canMove").toBool()) {
        return QObject::eventFilter(obj, evt);
    }

    static QPoint mousePoint;
    static bool mousePressed = false;

    QMouseEvent *event = static_cast<QMouseEvent *>(evt);
    if (event->type() == QEvent::MouseButtonPress) {
        if (event->button() == Qt::LeftButton) {
            mousePressed = true;
            mousePoint = event->globalPos() - w->pos();
            return true;
        }
    } else if (event->type() == QEvent::MouseButtonRelease) {
        if (event->button() == Qt::LeftButton) {
            mousePressed = false;
            return true;
        }
    } else if (event->type() == QEvent::MouseMove) {
        if (mousePressed && (event->buttons() && Qt::LeftButton)) {
            w->move(event->globalPos() - mousePoint);
            return true;
        }
    }

    return QObject::eventFilter(obj, evt);
}

void AppInit::start()
{
    qApp->installEventFilter(this);
}

void AppInit::StartWatchMouse()
{
    m_pMouseWatcher->start(1000);
    m_timeMouseTrigger = QTime::currentTime();
}

void AppInit::StopWatchMouse()
{
    m_pMouseWatcher->stop();
}
