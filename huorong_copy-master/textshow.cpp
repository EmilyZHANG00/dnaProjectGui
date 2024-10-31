#include "textshow.h"
#include "dynamicbtn.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QTimer>
#include <QCheckBox>
#include <QPushButton>

#include "rrogress.h"
#include "utils.h"


QWidget *MyCreateTop(QString icon, QString title, QString tip)
{
    QWidget *item = new QWidget();
    QLabel *labelIcon = new QLabel();
    QLabel *labelTitle = CreateCustomLabel(title, "#444444", 20);
    QLabel *labelTip = CreateCustomLabel(tip, "#777777", 12);

    labelIcon->setPixmap(QPixmap(icon));
    labelIcon->setFixedWidth(60);

    QHBoxLayout *layoutTop = new QHBoxLayout();
    layoutTop->addWidget(labelTitle);
    layoutTop->addStretch(1);
    layoutTop->setSpacing(20);

    QVBoxLayout *layoutRight = new QVBoxLayout();
    layoutRight->addStretch(1);
    layoutRight->addLayout(layoutTop);
    layoutRight->addWidget(labelTip);
    layoutRight->addStretch(1);
    layoutRight->setSpacing(2);
    layoutRight->setContentsMargins(10, 0, 0, 0);

    QHBoxLayout *layoutMain = new QHBoxLayout(item);
    layoutMain->addWidget(labelIcon);
    layoutMain->addLayout(layoutRight);
    layoutMain->setContentsMargins(0, 0, 0, 0);
    layoutMain->setSpacing(10);

    return item;
}

TextShow::TextShow(QWidget *parent,QString _info,QString _path
                   ) : BaseChildPane(parent)
{
    m_nStep = 1;
    m_strTitle = _info;
    m_pTimer = new QTimer();
    Textinfo = _info;
    m_pathstyleSheet = _path;
    InitCtrl();

    connect(m_pTimer, &QTimer::timeout, [=]() {
        m_nStep++;

        QList<DynamicBtn *> listChilds = this->findChildren<DynamicBtn *>();
        foreach (DynamicBtn *var, listChilds) {
            var->Stop();
        }

        int nIndex = qMin(m_nStep - 1, listChilds.length() - 1);
        listChilds.at(nIndex)->Start();

        if (m_nStep == listChilds.length())
        {
            m_pTimer->stop();
        }
    });

    m_pTimer->start(10 * 1000);
}
void TextShow::InitCtrl()
{
    QGridLayout *layoutMain = new QGridLayout();
    DynamicBtn *btn1 = new DynamicBtn();
    layoutMain->addWidget(btn1, 0, 0, 1, 1);
    btn1->setFixedWidth(550);
    btn1->setStyleSheet(m_pathstyleSheet);

    // btn1->setStyleSheet(QString("background-image: url(:/img/dnaMain.png)"));

    // QHBoxLayout *layoutCfg = new QHBoxLayout();
    // layoutCfg->addWidget(CreateCheckBox("约束码"));
    // layoutCfg->addWidget(CreateCheckBox("重构码"));
    // layoutCfg->addWidget(CreateCheckBox("纠删码"));


    QTextEdit *txd = new QTextEdit();
    txd->setText(Textinfo);

    layoutMain->addWidget(txd, 0, 1, 1, 1);
    layoutMain->setSpacing(10);


    QVBoxLayout *layoutMain1 = new QVBoxLayout(this);

    layoutMain1->addWidget(MyCreateTop(":/img/dnaIcon.png", "DNA存储的研究背景", "DNA存储一直是近年来热门的研究课题"));

    Progress *pProgress = new Progress();
    pProgress->setFixedHeight(3);

    layoutMain1->addWidget(pProgress);

    layoutMain1->addLayout(layoutMain, 1);
    layoutMain1->setContentsMargins(40, 20, 40, 20);
    layoutMain1->setSpacing(10);
}

void TextShow::Start()
{
    m_nStep = 1;

    QList<DynamicBtn *> listChilds = this->findChildren<DynamicBtn *>();
    foreach (DynamicBtn *var, listChilds) {
        var->Stop();
    }

    listChilds.at(0)->Start();
    m_pTimer->start(10 * 1000);
}

void TextShow::Stop()
{
    m_pTimer->stop();

    QList<DynamicBtn *> listChilds = this->findChildren<DynamicBtn *>();
    foreach (DynamicBtn *var, listChilds) {
        var->Clear();
    }
}

void TextShow::Pause()
{

}

void TextShow::OpenPage()
{
    Start();
}

void TextShow::ClosePage()
{
    Stop();
}
