#pragma push_macro("slots")
#undef slots
#include <Python.h>
#pragma pop_macro("slots")

#include "mainwnd.h"
#include <QVariant>
#include <QGraphicsDropShadowEffect>
#include <QVBoxLayout>
#include <QtWidgets>
#include <QPixmap>
#include "tools.h"
#include "sysprotect.h"
#include "Reconstruction.h"
// #include "virscan.h"
// #include "textshow.h"
// #include "utils.h"
#include "subreconstruction.h"
#include "constraintcode.h"

#include "QAbstractTransition"
#include <QStateMachine>
#include <QEventTransition>
#include <SequenceReconstructionForm.h>
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif


MainWnd::MainWnd(QWidget *parent)
    : QDialog(parent)
{
    //Py_SetPythonHome(L"D:\\Anaconda");
    //Python初始化  与exe文件的相对位置

    Py_SetPythonHome(L"./PY38ENV");
    Py_Initialize();

    // 检查Python初始化是否成功
    if (PyErr_Occurred()) {
        PyErr_Print();
        qDebug() << "Python初始化失败";
    } else {
        qDebug() << "Python初始化成功";
    }
    //导入sys模块设置模块地址
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.argv = ['python.py']");
    //PyRun_SimpleString("sys.path.append('C:/Users/fairysc/AppData/Local/Programs/Python/Python313/')");//说明系统文件所在路径
    // PyRun_SimpleString("sys.path.append('D:/xiangmu/huorong_copy/build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule')");

    QString setSysPath = QString("sys.path.append('%1')").arg(QCoreApplication::applicationDirPath()+"/PYModule");
    PyRun_SimpleString(setSysPath.toStdString().c_str());


    m_pMianPane = new MainPane(this);

#ifdef Q_OS_WIN32
    setWindowFlags(windowFlags() | (Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint));
#else
    setWindowFlags(windowFlags() | (Qt::FramelessWindowHint));
#endif // Q_OS_WIN32

    setProperty("canMove", true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowTitle("DNA编解码算法软件");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_pMianPane);
    mainLayout->setContentsMargins(5, 0, 5, 0);;
    setLayout(mainLayout);
}

MainWnd::~MainWnd()
{
    Py_Finalize();
}

void MainWnd::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(9, 9, this->width()-18, this->height()-18);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));
    QColor color(0, 0, 0, 50);
    for(int i=0; i<9; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(9-i, 9-i, this->width()-(9-i)*2, this->height()-(9-i)*2);
        color.setAlpha(150 - qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }
}

MainPane::MainPane(QWidget *parent)
{
    m_pTopTools = new QWidget(this);
    m_pCenter = new QWidget(this);
    m_pBottom = new QWidget(this);
    m_pVirusKill = new QWidget(this);


    /* 参数1:显示文本内容   参数2:对应的图片 格式 QString("background-image: url(:/img/dnaMain.png)") */
    // m_pTextShowBackGround = new TextShow(this,QString("DNA存储研究背景介绍"),QString("background-image: url(:/img/dnaMain.png)"));
    // m_pTextShowStatus = new TextShow(this,QString("DNA存储研究现状"),QString("background-image: url(:/img/dnaMain.png)"));
    // m_pTextShowProgress = new TextShow(this,QString("DNA存储研究进度"),QString("background-image: url(:/img/dnaMain.png)"));
    // m_pTextShowConstraint = new TextShow(this,QString("DNA约束编码"),QString("background-image: url(:/img/dnaMain.png)"));

    m_pReconstruction = new Reconstruction(this);
    m_pTools = new Tools(this);
    m_pSubReconstruction = new subReconstruction(this);
    //m_pConstraintCode = new subReconstruction(this);
    m_pConstraintCode = new ConstraintCode(this);


    m_pSysProtect = new SysProtect(this);
    m_pixFlash = new QPixmap(":/img/100/ani_flash.png");
    m_bShowChild = false;

    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    // setFixedSize(1020, 690);
    setFixedSize(1220, 690);

    setStyleSheet("MainPane{"
                  "background: #fff;"
                    "background-size: 32px 32px;"
                  "background-image: url(:/img/100/bk_main_normal.png);"
                  //"background-repeat: repeat;"
                    "background-position: center;                    }");



    // m_pTextShowBackGround->hide();
    // m_pTextShowStatus->hide();
    // m_pTextShowProgress->hide();
    // m_pTextShowConstraint->hide();
    // m_pVirscan->hide();

    m_pSysProtect->hide();

    m_pTools->hide();
    m_pReconstruction->hide();
    m_pSubReconstruction->hide();
    m_pConstraintCode->hide();

    InitCtrl();
}

MainPane::~MainPane()
{

}

void MainPane::InitCtrl()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_pTopTools);
    mainLayout->addWidget(m_pCenter);
    mainLayout->addWidget(m_pBottom);
    mainLayout->setContentsMargins(7, 0, 7, 0);;
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    InitTop();
    InitCenter();
    InitBottom();
    // InitDNAINTRO();
}

void MainPane::InitTop()
{
    m_pTopTools->setFixedHeight(24);
    m_pTopTools->setObjectName("m_pTopTools");
    m_pTopTools->setStyleSheet("QWidget#m_pTopTools{"
                  //"background-image: url(:/img/100/logo_gold.png);"
                  "background-repeat: no-repeat}");

    QHBoxLayout *mainLayout = new QHBoxLayout(m_pTopTools);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addStretch(1);
    m_btnBack = CreateMiniBtn("返回", ":/img/100/back.png");
    connect(m_btnBack, &QPushButton::clicked, [=]() {
       qDebug()<<"执行HideChild";
       HideChild();
    });
    mainLayout->addWidget(m_btnBack);
    mainLayout->addWidget(CreateMiniBtn("最小化", ":/img/100/min_gray.png", QSize(36, 24), [=]() {
       parentWidget()->setWindowState(Qt::WindowMinimized);
    }));
    mainLayout->addWidget(CreateMiniBtn("关闭", ":/img/100/close_gray.png", QSize(36, 24), [=]() {
        qApp->quit();
    }));
    m_btnBack->hide();
}

void MainPane::InitCenter()
{
    QLabel *mianLab = new QLabel("DNA 下一代存储介质", this);
    mianLab->setObjectName("mianLab");
    mianLab->setAlignment(Qt::AlignCenter);
    mianLab->setStyleSheet("font-size: 22px; font-weight: 500; color: #85724b");

    QLabel *mianLogo = new QLabel(this);
    mianLogo->setObjectName("mianLogo");
    mianLogo->setFixedSize(200, 220);
    mianLogo->setStyleSheet("background-image: url(:/img/100/icon_main_normal.png);"
                  "background-repeat: no-repeat");

    QLabel *labelTip1 = new QLabel(this);
    labelTip1->setAlignment(Qt::AlignRight);

    QVBoxLayout *tipLayout = new QVBoxLayout();
    tipLayout->setContentsMargins(0, 0, 0, 70);
    tipLayout->setSpacing(10);
    tipLayout->addStretch();
    tipLayout->addWidget(labelTip1);
    //tipLayout->addWidget(labelTip2);


    QHBoxLayout *centerLayout = new QHBoxLayout();
    centerLayout->setContentsMargins(0, 0, 0, 0);
    centerLayout->setSpacing(0);
    centerLayout->addStretch(1);
    centerLayout->addWidget(mianLogo);
    centerLayout->addLayout(tipLayout, 1);


    QVBoxLayout *mainLayout = new QVBoxLayout(m_pCenter);
    mainLayout->setContentsMargins(0, 60, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(mianLab);
    mainLayout->addLayout(centerLayout);


    setProperty("rotate", 0);
    QPropertyAnimation *animation1 = new QPropertyAnimation(this, "rotate");
    animation1->setDuration(3000);
    animation1->setStartValue(-1);
    animation1->setEndValue(35);
    //connect(animation1, SIGNAL(valueChanged(const QVariant &)), this, SLOT(update()));
    connect(animation1, &QPropertyAnimation::valueChanged, [=](const QVariant &v)
    {
        QSize sizeImg(470, 320);
        QPoint topleft((width() - 470) / 2, 0);
        QRect rcImg(topleft, sizeImg);
        update(rcImg);
    });

    QPropertyAnimation *animation2 = new QPropertyAnimation(this, "rotate");
    animation2->setDuration(2000);
    animation2->setStartValue(-1);
    animation2->setEndValue(-1);

    QSequentialAnimationGroup *paraGroup = new QSequentialAnimationGroup(this);
    paraGroup->addAnimation(animation1);
    paraGroup->addAnimation(animation2);
    paraGroup->setLoopCount(-1);
    paraGroup->start();
}

void MainPane::InitBottom()
{
    m_pBottom->setFixedHeight(150);

    QHBoxLayout *mainLayout = new QHBoxLayout(m_pBottom);
    mainLayout->setContentsMargins(0, 0, 0, 50);
    mainLayout->setSpacing(110);
    mainLayout->addStretch();

    QPushButton *btn = CreateBtn("约束编码", ":/img/100/virscan.png");
    connect(btn, &QPushButton::clicked, [=]() {
      ShowChild(m_pConstraintCode);
    });
    mainLayout->addWidget(btn);

    QPushButton *btnSysProtect = CreateBtn("替换重构", ":/img/100/sysprotect.png");
    mainLayout->addWidget(btnSysProtect);
    connect(btnSysProtect, &QPushButton::clicked, [=]() {
       ShowChild(m_pSubReconstruction);
    });


    QPushButton *btnReconstruction = CreateBtn("删除重构", ":/img/100/kidsprotect.png");
    mainLayout->addWidget(btnReconstruction);
    connect(btnReconstruction, &QPushButton::clicked, [=]() {
       ShowChild(m_pReconstruction);
    });

    QPushButton *btnTools = CreateBtn("纠删码", ":/img/100/tools.png");
    mainLayout->addWidget(btnTools);
    connect(btnTools, &QPushButton::clicked, [=]() {
       ShowChild(m_pTools);
    });
    mainLayout->addStretch();
}

void MainPane::UpdateCtrlState()
{
    //移除原有样式
    style()->unpolish(this);
    //必须要有下面这行不然还是不会卸载
    this->setStyleSheet("");

    if (m_bShowChild)
    {
        setStyleSheet("MainPane{background: #f8f9f9;}");
        m_btnBack->show();
    }
    else
    {
        setStyleSheet("MainPane{"
                      "background: #fff;"
                      "background-size: 32px 32px;"
                      "background-image: url(:/img/100/bk_main_normal.png);"
                      //"background-repeat: repeat;"
                      "background-position: center;                    }");
        m_btnBack->hide();
    }

    //重新设置新的该控件的样式。
    style()->polish(this);

    update();
}

/* 弹出框的内容  */
// void MainPane::InitDNAINTRO()
// {
//     m_pVirusKill->hide();
//     m_pVirusKill->setFixedHeight(180);
//     m_pVirusKill->setObjectName("m_pVirusKill");
//     m_pVirusKill->setStyleSheet("QWidget#m_pVirusKill{background: #fff; background-image: url(:/img/100/viruscan/expand_bk.png); background-repeat: no-repeat; background-position: bottom}");

//     QHBoxLayout *mainLayout1 = new QHBoxLayout();
//     mainLayout1->setContentsMargins(0, 0, 0, 0);
//     mainLayout1->setSpacing(110);
//     mainLayout1->addStretch(1);

//     //  ShowChild(m_pVirscan) 分别进入到不同的界面
//     /*
//         m_pVirscan->hide();
//         m_pTextShowBackGround->hide();
//         m_pTextShowStatus->hide();
//         m_pTextShowProgress->hide();
//     */
//     QPushButton *btnBackGround = CreateBtn("研究背景", ":/img/100/viruscan/all.png");
//     mainLayout1->addWidget(btnBackGround);
//     connect(btnBackGround, &QPushButton::clicked, [=]() {
//        ShowChild(m_pTextShowBackGround);
//         HideVirusKill();
//     });
//     QPushButton *btnStatus = CreateBtn("研究现状", ":/img/100/viruscan/quick.png");
//     mainLayout1->addWidget(btnStatus);
//     connect(btnStatus, &QPushButton::clicked, [=]() {
//        ShowChild(m_pTextShowStatus);
//        HideVirusKill();
//     });
//     QPushButton *btnProgress = CreateBtn("研究进度", ":/img/100/viruscan/custom.png");
//     mainLayout1->addWidget(btnProgress);
//     connect(btnProgress, &QPushButton::clicked, [=]() {
//         ShowChild(m_pTextShowProgress);
//         HideVirusKill();
//     });
//     mainLayout1->addStretch(1);


//     QHBoxLayout *mainLayout2 = new QHBoxLayout();
//     mainLayout2->setContentsMargins(0, 0, 0, 0);
//     mainLayout2->addStretch(1);
//     QPushButton *btn = CreateMiniBtn("", ":/img/100/viruscan/expand.png", QSize(28, 28));
//     connect(btn, &QPushButton::clicked, [=]() {
//        HideVirusKill();
//     });
//     mainLayout2->addWidget(btn);
//     mainLayout2->addStretch(1);

//     QVBoxLayout *mainLayout = new QVBoxLayout(m_pVirusKill);
//     mainLayout->setSpacing(0);
//     mainLayout->setContentsMargins(0, 0, 0, 0);
//     mainLayout->addLayout(mainLayout1);
//     mainLayout->addStretch(1);
//     mainLayout->addLayout(mainLayout2);
// }

// void MainPane::ShowVirusKill()
// {
//     m_pVirusKill->show();

//     QPoint point(0, height() - m_pVirusKill->height());
//     QPoint point2(0, height());
//     QRect rcStart, rcEnd;
//     rcEnd = QRect(point, QSize(width(), m_pVirusKill->height()));
//     rcStart = QRect(point2, QSize(width(), m_pVirusKill->height()));

//     QPropertyAnimation *animation = new QPropertyAnimation(m_pVirusKill, "geometry");
//     animation->setDuration(180);
//     animation->setStartValue(rcStart);
//     animation->setEndValue(rcEnd);
//     animation->start(QAbstractAnimation::DeleteWhenStopped);

//     UpdateCtrlState();
// }

// void MainPane::HideVirusKill()
// {
//     QPoint point(0, height() - m_pVirusKill->height());
//     QPoint point2(0, height());
//     QRect rcStart, rcEnd;
//     rcStart = QRect(point, QSize(width(), m_pVirusKill->height()));
//     rcEnd = QRect(point2, QSize(width(), m_pVirusKill->height()));

//     QPropertyAnimation *animation = new QPropertyAnimation(m_pVirusKill, "geometry");
//     connect(animation, &QPropertyAnimation::finished, [=]() {
//        m_pVirusKill->hide();
//     });
//     animation->setDuration(180);
//     animation->setStartValue(rcStart);
//     animation->setEndValue(rcEnd);
//     animation->start(QAbstractAnimation::DeleteWhenStopped);
// }

void MainPane::ShowChild(QWidget *child)
{

    // SequenceReconstructionForm *form = new SequenceReconstructionForm;
    // form->setWindowTitle(QStringLiteral("序列重构"));
    // form->show();
    child->show();
    child->raise();
    {
        BaseChildPane *child = GetChild();
        child->OpenPage();
    }

    QParallelAnimationGroup *group = new QParallelAnimationGroup(child);

    QPoint point(0, 40);
    QPoint point2(0, height());
    QRect rcStart, rcEnd;
    rcEnd = QRect(point, QSize(width(), height() - 40));
    rcStart = QRect(point2, QSize(width(), 0));

    QPropertyAnimation *animation = new QPropertyAnimation(child, "geometry");
    animation->setDuration(180);
    animation->setStartValue(rcStart);
    animation->setEndValue(rcEnd);

    group->addAnimation(animation);

    group->start(QAbstractAnimation::DeleteWhenStopped);

    m_bShowChild = true;
    UpdateCtrlState();
}

void MainPane::HideChild()
{

    BaseChildPane *child = GetChild();
    child->ClosePage();


    QPoint point(0, 40);
    QPoint point2(0, height());
    QRect rcStart, rcEnd;
    rcStart = QRect(point, QSize(width(), height() - 40));
    rcEnd = QRect(point2, QSize(width(), 0));

    QPropertyAnimation *animation = new QPropertyAnimation(child, "geometry");
    connect(animation, &QPropertyAnimation::finished, [=]() {
       child->hide();
    });
    animation->setDuration(180);
    animation->setStartValue(rcStart);
    animation->setEndValue(rcEnd);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    m_bShowChild = false;
    UpdateCtrlState();
}

BaseChildPane *MainPane::GetChild()
{
    QList<BaseChildPane *> listChilds = this->findChildren<BaseChildPane *>();
    foreach (BaseChildPane *child, listChilds) {
        if (child && child->isVisible())
            return child;
    }
    return nullptr;
}

QString MainPane::GetTitle()
{
    BaseChildPane *child = GetChild();
    if (child)
        return child->GetTitle();

    return "";
}

void MainPane::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int rotate = this->property("rotate").toInt();
    if (m_pixFlash && rotate >= 0)
    {
        QSize sizeImg(470, 320);
        QPoint topleft((width() - 470) / 2, 0);
        QRect rcImg(topleft, sizeImg);
        painter.drawPixmap(rcImg, m_pixFlash->copy(rotate * 470, 0, 470, 320));
    }

    if (m_bShowChild)
    {
        painter.save();
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QColor("#282828"));
        QFont font = painter.font();
        font.setPixelSize(16);
        painter.setFont(font);
        painter.drawText(QRect(0, 0, width(), 40), Qt::AlignCenter, GetTitle());
        painter.restore();
    }
}

QPushButton *CreateBtn(QString title, QString img)
{
    QPushButton *btn = new QPushButton();
    btn->setStyleSheet(QString("QWidget{border-style:none;"
                       "font-size: 16px;}"
                       "QWidget:hover{color: #ffa924;}"
                       "QPushButton{border-style:none;"
                       "text-align: center;"
                       "background-image: url(%1);"
                       "background-repeat: no-repeat}"
                       "QPushButton:hover{margin-left:-80px;}"
                       "QPushButton:pressed{margin-left:-160px;color: #ffa924;}").arg(img));
    btn->setFixedSize(80, 110);
    btn->setCursor(Qt::PointingHandCursor);

    QVBoxLayout *btnLayout = new QVBoxLayout(btn);
    btnLayout->setContentsMargins(0, 60, 0, 0);
    btnLayout->setSpacing(0);
    btnLayout->addStretch();
    QLabel *label = new QLabel(title, btn);
    label->setAlignment(Qt::AlignCenter);
    btnLayout->addWidget(label);


    QStateMachine *shadowStateMachine = new QStateMachine(btn);
    QState *normalState      = new QState;
    QState *hoverState       = new QState;
    QState *pressedState     = new QState;

    shadowStateMachine->addState(normalState);
    shadowStateMachine->addState(pressedState);

    normalState->assignProperty(label, "styleSheet", "color: #444444;");
    hoverState->assignProperty(label, "styleSheet", "color: #ffa924;");
    pressedState->assignProperty(label, "styleSheet", "color: #f17f05;");

    QAbstractTransition *transition;

    transition = new QEventTransition(btn, QEvent::MouseButtonPress);
    transition->setTargetState(pressedState);
    normalState->addTransition(transition);

    transition = new QEventTransition(btn, QEvent::MouseButtonDblClick);
    transition->setTargetState(pressedState);
    normalState->addTransition(transition);

    transition = new QEventTransition(btn, QEvent::Enter);
    transition->setTargetState(pressedState);
    normalState->addTransition(transition);

    transition = new QEventTransition(btn, QEvent::Leave);
    transition->setTargetState(normalState);
    pressedState->addTransition(transition);

    transition = new QEventTransition(btn, QEvent::MouseButtonRelease);
    transition->setTargetState(pressedState);
    pressedState->addTransition(transition);

    shadowStateMachine->setInitialState(normalState);
    shadowStateMachine->start();

    return btn;
}

QPushButton *CreateMiniBtn(QString title, QString img, QSize size, Function&& fn)
{
    QPushButton *btn = new QPushButton();
    btn->setStyleSheet(QString("QWidget{border-style:none;"
                       "font-size: 16px;}"
                       "QWidget:hover{color: #ffa924;}"
                       "QPushButton{border-style:none;"
                       "text-align: center;"
                       "background-image: url(%1);"
                       "background-repeat: no-repeat}"
                       "QPushButton:hover{margin-left:-%2px;}"
                       "QPushButton:pressed{margin-left:-%3px;color: #ffa924;}").arg(img).arg(size.width()).arg(size.width() * 2));
    btn->setFixedSize(size);
    btn->setToolTip(title);
    btn->setCursor(Qt::PointingHandCursor);

    QObject::connect(btn, &QPushButton::clicked, [=]() {
        if(fn) fn();
    });

    return btn;
}
