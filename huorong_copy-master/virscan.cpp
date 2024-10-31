#include "virscan.h"
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


QWidget *CreateTop(QString icon, QString title, QString tip)
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

Virscan::Virscan(QWidget *parent) : BaseChildPane(parent)
{
    m_nStep = 1;
    m_strTitle = "Virscan";
    m_pTimer = new QTimer();
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
void Virscan::InitCtrl()
{
    QGridLayout *layoutMain = new QGridLayout();
    DynamicBtn *btn1 = new DynamicBtn();
    layoutMain->addWidget(btn1, 0, 0, 1, 1);
    btn1->setFixedWidth(550);
    btn1->setStyleSheet(QString("background-image: url(:/img/dnaMain.png)"));

    QHBoxLayout *layoutCfg = new QHBoxLayout();
    layoutCfg->addWidget(CreateCheckBox("约束码"));
    layoutCfg->addWidget(CreateCheckBox("重构码"));
    layoutCfg->addWidget(CreateCheckBox("纠删码"));


    QTextEdit *txd = new QTextEdit();
    txd->setText("人类社会的文明史，是一部信息存储方式和传播方式变革的历史。以存储介质为例，经历了从远古时代的结绳记事，到甲骨、金属、竹简、纸，直至当今时代的硅基存储。而信息技术与经济社会的交汇 融合则使数据信息成为了国家基础性战略资源。以爆发式增长为特点 的海量数据正日益对全球生产、流通、分配以及国家经济运行机制、 社会生活方式和国家治理能力产生重要影响。据统计，全球数据信息总量2020年为44 ZB（万亿亿字节），预期到2025年将达到175 ZB（约需>1750亿个1 TB硬盘）。因而，研发存储寿命长、空间和能源消耗小、环境稳定性和安全性好的新一代数据存储介质，突破海量数据存储的瓶颈，体现了世界各主要国家的重大战略。"
                 "脱氧核糖核酸（DNA）作为亿万年自然进化选择出来的碳基生命遗传密码的天然存储介质，具有极高的存储密度和稳健性。DNA本身所具有的可编码性和高效复制能力，有可能为数据高密度存储和高性能运算提供一种全新策略。DNA存储具有物理稳定性高的优点，不像电子介质会随读取次数而衰退，为数据的长期存储提供了一种根本性解决方案。另外，DNA分子兼具了信息处理和计算能力，为发展新型的存算一体架构和系统提供了新的思路。因此，将核酸作为一种新兴的分子信息材料来发展展，体现了信息技术（IT）与生物技术（BT）的融合，有可能在信息存储、智能计算、纳米机器人等方向成为信息科技发展的重要突破口。");

    layoutMain->addWidget(txd, 0, 1, 1, 1);
    layoutMain->setSpacing(10);


    QVBoxLayout *layoutMain1 = new QVBoxLayout(this);

    layoutMain1->addWidget(CreateTop(":/img/dnaIcon.png", "DNA存储的研究背景", "DNA存储一直是近年来热门的研究课题"));

    Progress *pProgress = new Progress();
    pProgress->setFixedHeight(3);

    layoutMain1->addWidget(pProgress);

    layoutMain1->addLayout(layoutMain, 1);
    layoutMain1->setContentsMargins(40, 20, 40, 20);
    layoutMain1->setSpacing(10);
}

void Virscan::Start()
{
    m_nStep = 1;

    QList<DynamicBtn *> listChilds = this->findChildren<DynamicBtn *>();
    foreach (DynamicBtn *var, listChilds) {
        var->Stop();
    }

    listChilds.at(0)->Start();
    m_pTimer->start(10 * 1000);
}

void Virscan::Stop()
{
    m_pTimer->stop();

    QList<DynamicBtn *> listChilds = this->findChildren<DynamicBtn *>();
    foreach (DynamicBtn *var, listChilds) {
        var->Clear();
    }
}

void Virscan::Pause()
{

}

void Virscan::OpenPage()
{
    Start();
}

void Virscan::ClosePage()
{
    Stop();
}
