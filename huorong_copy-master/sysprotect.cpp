#include "sysprotect.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QStateMachine>
#include <QLabel>
#include <QStackedWidget>
#include <QAbstractTransition>
#include <QEventTransition>
#include "configlist.h"

#include <functional>
typedef std::function<void()> Function;

QPushButton *CreateNavBtn(QString title, QString img, Function&& fn = nullptr)
{
    struct TItem
    {
        QPushButton *btn;
        QIcon ico1;
        QIcon ico2;
    };

    static QList <TItem> btns;
    QPushButton *btn = new QPushButton(title);

    btn->setStyleSheet(QString(
                       "QPushButton{border-style:none; color: #444444; font-size: 14px;}"
                       "QPushButton:checked{color: #ffa924;}"
                       "QPushButton:pressed{color: #ffa924;}"));

    btn->setCursor(Qt::PointingHandCursor);
    btn->setCheckable(true);

    QPixmap pixImg(img);
    QIcon ico1(pixImg.copy(0, 0, 20, 20));
    QIcon ico2(pixImg.copy(20, 0, 20, 20));
    btn->setIcon(ico1);
    btn->setIconSize(QSize(20, 20));
    btn->setFixedHeight(32);
    btns.append({btn, ico1, ico2});

    QObject::connect(btn, &QPushButton::clicked, [=]() {
        foreach (TItem item, btns) {
            if (item.btn != btn)
            {
                item.btn->setIcon(item.ico1);
                item.btn->setChecked(false);
            }
        }
        btn->setIcon(ico2);
        btn->setChecked(true);

        if(fn) fn();
    });

    QStateMachine *shadowStateMachine = new QStateMachine(btn);
    QState *normalState      = new QState;
    QState *hoverState       = new QState;
    QState *pressedState     = new QState;

    shadowStateMachine->addState(normalState);
    shadowStateMachine->addState(pressedState);

    normalState->assignProperty(btn, "icon", ico1);
    hoverState->assignProperty(btn, "icon", ico2);
    pressedState->assignProperty(btn, "icon", ico2);

    QAbstractTransition *transition;

    transition = new QEventTransition(btn, QEvent::MouseButtonPress);
    transition->setTargetState(pressedState);
    normalState->addTransition(transition);

    transition = new QEventTransition(btn, QEvent::MouseButtonDblClick);
    transition->setTargetState(pressedState);
    normalState->addTransition(transition);

    transition = new QEventTransition(btn, QEvent::MouseButtonRelease);
    transition->setTargetState(pressedState);
    pressedState->addTransition(transition);

    shadowStateMachine->setInitialState(normalState);
    shadowStateMachine->start();

    return btn;
}

SysProtect::SysProtect(QWidget *parent) : BaseChildPane(parent)
{
    m_strTitle = "防护中心";
    m_pLeftPane = new QWidget(this);
    m_RightPane = new QWidget(this);

    InitCtrl();
}

void SysProtect::InitCtrl()
{
    InitLeftPane();
    InitRightPane();

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 10, 0, 10);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_pLeftPane);
    mainLayout->addWidget(m_RightPane);
}

void SysProtect::InitLeftPane()
{
    m_pLeftPane->setFixedWidth(180);
    QVBoxLayout *leftLayout = new QVBoxLayout(m_pLeftPane);
    leftLayout->setContentsMargins(0, 4, 0, 4);
    leftLayout->setSpacing(8);
    QPushButton *btn = CreateNavBtn("病毒防护", ":/img/100/sysprotect/virus.png", [=]() { m_pStackedWidget->setCurrentIndex(0); });
    btn->setChecked(true);
    leftLayout->addWidget(btn);
    leftLayout->addWidget(CreateNavBtn("系统防护", ":/img/100/sysprotect/sys.png", [=]() { m_pStackedWidget->setCurrentIndex(1); }));
    leftLayout->addWidget(CreateNavBtn("网络防护", ":/img/100/sysprotect/net.png", [=]() { m_pStackedWidget->setCurrentIndex(2); }));
    leftLayout->addStretch(1);
    leftLayout->addWidget(CreateNavBtn("高级防护", ":/img/100/sysprotect/advance.png", [=]() { m_pStackedWidget->setCurrentIndex(3); }));
    m_pLeftPane->setStyleSheet(".QWidget{border-right: 2px solid #f0f0f0;}");
}

void SysProtect::InitRightPane()
{
    m_pStackedWidget = new QStackedWidget(this);
    ConfigList *virus = new ConfigList(this);
    virus->AddItem(":/img/100/sysprotect/virus/file.png", "文件实时监控", "当文件被执行、创建、打开时，进行病毒扫描");
    virus->AddItem(":/img/100/sysprotect/virus/behavior.png", "恶意行为监控", "监控程序在运行过程中，是否有恶意行为");
    virus->AddItem(":/img/100/sysprotect/virus/udisk.png", "U盘保护", "在接入U盘时，自动对U盘根目录下的文件进行扫描");
    virus->AddItem(":/img/100/sysprotect/virus/download.png", "下载保护", "实时扫描通过浏览器、即时通讯软件下载的文件");
    virus->AddItem(":/img/100/sysprotect/virus/mail.png", "邮件监控", "对邮件客户端收发的邮件及附件进行病毒扫描");
    virus->AddItem(":/img/100/sysprotect/virus/web.png", "Web扫描", "对HTTP协议接收的数据进行病毒扫描");
    m_pStackedWidget->addWidget(virus);

    ConfigList *sys = new ConfigList(this);
    sys->AddItem(":/img/100/sysprotect/sys/sys.png", "系统加固", "针对计算机潜在弱点进行防护");
    sys->AddItem(":/img/100/sysprotect/sys/app.png", "应用加固", "控制应用程序的行为，防止被恶意软件利用");
    sys->AddItem(":/img/100/sysprotect/sys/install.png", "软件安装拦截", "实时监控并提示软件安装行为");
    sys->AddItem(":/img/100/sysprotect/sys/camera.png", "摄像头保护", "发现并提示应用程序开启摄像头");
    sys->AddItem(":/img/100/sysprotect/sys/browser.png", "浏览器保护", "保护浏览器首页和浅索不被复改");
    sys->AddItem(":/img/100/sysprotect/sys/appnetctrl.png", "联网控制", "管控应用程序的联网行为");
    m_pStackedWidget->addWidget(sys);

    ConfigList *net = new ConfigList(this);
    net->AddItem(":/img/100/sysprotect/net/hack.png", "网络入侵拦截", "在网络层拦截漏洞攻击、黑客入侵等威胁");
    net->AddItem(":/img/100/sysprotect/net/tpprot.png", "横向渗透防护", "在网络层拦载横向渗透攻击");
    net->AddItem(":/img/100/sysprotect/net/attack.png", "对外攻击拦截", "在网络层拦载本机对外部计算机的漏洞攻击等行为");
    net->AddItem(":/img/100/sysprotect/net/zombie_net.png", "僵尸网络防护", "在网络层栏载潜在后门攻击");
    net->AddItem(":/img/100/sysprotect/net/remote_login.png", "暴破攻击防护", "发现暴玻攻击行为，拦载潜在暴力破解攻击");
    net->AddItem(":/img/100/sysprotect/net/web_service.png", "Web服务保护", "针对高危Wb服务漏洞渗透攻击进行防护");
    net->AddItem(":/img/100/sysprotect/net/malicious_web.png", "恶意网址拦截", "自动阻止木马、欺诈、钓鱼类等网址");
    m_pStackedWidget->addWidget(net);

    ConfigList *advance = new ConfigList(this);
    advance->AddItem(":/img/100/sysprotect/advance/custom.png", "自定义防护", "对文件、注册表以及程序的执行进行控制以及保护");
    advance->AddItem(":/img/100/sysprotect/advance/ip_backlist.png", "IP黑名单", "限制对指定IP的出站、入站请求");
    advance->AddItem(":/img/100/sysprotect/advance/ip_protocol.png", "IP协议控制", "在IP协议层进行网络访问控制");
    m_pStackedWidget->addWidget(advance);
    m_pStackedWidget->setCurrentIndex(0);

    QVBoxLayout *rightLayout = new QVBoxLayout(m_RightPane);
    rightLayout->setContentsMargins(10, 4, 10, 4);
    rightLayout->setSpacing(8);
    rightLayout->addWidget(m_pStackedWidget);
}
