#include "constraintcode.h"
#pragma push_macro("slots")
#undef slots
#include <Python.h>
#pragma pop_macro("slots")

QWidget *ConsCreateLineEditBoxItem(QString icon, QString title,QLineEdit *lineobj)
{
    QPushButton *item = new QPushButton();
    item->setStyleSheet("QPushButton{border-style:none;background: #fff; border: 0; }"
                        "QPushButton:hover {background: #fffcf8; border: 1px solid #ffe7c1; }");
    item->setFixedHeight(70);

    QLabel *labelIcon = new QLabel();
    QLabel *labelTitle = CreateCustomLabel(title, "#444444", 14);
    labelIcon->setPixmap(QPixmap(icon));
    //labelIcon->setFixedWidth(36);
    labelIcon->setScaledContents(true);
    labelIcon->setMinimumSize(36,36);
    labelIcon->setMaximumSize(36,36);

    QHBoxLayout *layoutTop = new QHBoxLayout();
    layoutTop->addWidget(labelTitle);
    layoutTop->addStretch(1);
    //layoutTop->addWidget(checkBox);

    QVBoxLayout *layoutRight = new QVBoxLayout();
    layoutRight->addStretch(1);
    layoutRight->addLayout(layoutTop);
    layoutRight->addWidget(lineobj);

    layoutRight->addStretch(1);
    layoutRight->setSpacing(2);
    layoutRight->setContentsMargins(10, 0, 0, 0);

    QHBoxLayout *layoutMain = new QHBoxLayout(item);
    layoutMain->addWidget(labelIcon);
    layoutMain->addWidget(CreateSeparator(true));
    layoutMain->addLayout(layoutRight);
    layoutMain->setContentsMargins(10, 10, 10, 10);
    layoutMain->setSpacing(10);

    return item;
}


ConstraintCode::ConstraintCode(QWidget *parent) : BaseChildPane(parent)
{
    m_strTitle = "约束编码";
    InitCtrl();
}

void ConstraintCode::InitCtrl()
{
    QVBoxLayout *layoutTitle = new QVBoxLayout();
    layoutTitle->addWidget(CreateCustomLabel("[约束编码介绍:]"));
    layoutTitle->setSpacing(10);



    QHBoxLayout *layoutTop = new QHBoxLayout();
    layoutTop->addLayout(layoutTitle);
    layoutTop->addStretch(1);
    //layoutTop->addLayout(layoutTopBtn);


    QLabel *labelTitle1 = new QLabel("  " + QString("文件导入"));
    labelTitle1->setStyleSheet("border: 3px solid #c0a686; border-top-color: rgba(0,0,0,0); border-right-color: rgba(0,0,0,0); border-bottom-color: rgba(0,0,0,0); font-size: 14px");

    QLabel *labelTitle2 = new QLabel("  " + QString("参数"));
    labelTitle2->setStyleSheet("border: 3px solid #c0a686; border-top-color: rgba(0,0,0,0); border-right-color: rgba(0,0,0,0); border-bottom-color: rgba(0,0,0,0); font-size: 14px");

    QLabel *labelTitle3 = new QLabel("  " + QString("结果"));
    labelTitle3->setStyleSheet("border: 3px solid #c0a686; border-top-color: rgba(0,0,0,0); border-right-color: rgba(0,0,0,0); border-bottom-color: rgba(0,0,0,0); font-size: 14px");

    /*-----------------------------------------------------------------------*/
    QVBoxLayout *layouttdr = new QVBoxLayout();
    QLabel *labelTitle = CreateCustomLabel("输入测试文本/路径", "#444444", 14);

    QVBoxLayout *layoutwbk = new QVBoxLayout();
    layoutwbk->addWidget(labelTitle);
    layoutwbk->addStretch(1);
    layoutwbk->addWidget(textRode);

    QHBoxLayout *layoutdrz = new QHBoxLayout();
    layoutdrz->addLayout(layouttdr);
    layoutdrz->addLayout(layoutwbk);

    QGridLayout *layoutCfg = new QGridLayout();
    layoutCfg->addWidget(ConsCreateLineEditBoxItem(":/img/100/viruscan/icon_scan_completed.png", "码的最小距离",minDistance), 0, 0, 1, 1);
    layoutCfg->addWidget(ConsCreateLineEditBoxItem(":/img/100/viruscan/icon_scan_completed.png", "错误球半径", errRadius), 0, 1, 1, 1);
    layoutCfg->addWidget(ConsCreateLineEditBoxItem(":/img/100/viruscan/icon_scan_completed.png", "读取数目",clusterSize), 0, 2, 1, 1);


    QPushButton *btn_begin = new QPushButton();
    btn_begin->setText("开始");
    connect(btn_begin,SIGNAL(clicked()),this,SLOT(on_begin_slots()));

    QPushButton *btn_flush = new QPushButton();
    btn_flush->setText("刷新");
    connect(btn_flush,SIGNAL(clicked()),this,SLOT(on_flush_slots()));



    QHBoxLayout *layoutShow = new QHBoxLayout();
    layoutShow->addWidget(textShow);

    QVBoxLayout *layoutbtn = new QVBoxLayout();
    layoutbtn->addWidget(btn_begin);
    layoutbtn->addSpacerItem(new QSpacerItem(0,160,QSizePolicy::Fixed,QSizePolicy::Fixed));
    layoutbtn->addWidget(btn_flush);

    layoutShow->addLayout(layoutbtn);

    //layoutBegin->addSpacerItem(new QSpacerItem(0,160,QSizePolicy::Expanding,QSizePolicy::Fixed));
    layoutShow->setContentsMargins(10, 0, 0, 0);


    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    layoutMain->addLayout(layoutTop);
    layoutMain->addWidget(CreateSeparator());
    layoutMain->addWidget(labelTitle1);
    layoutMain->addLayout(layoutdrz);
    layoutMain->addWidget(labelTitle2);
    layoutMain->addLayout(layoutCfg);
    layoutMain->addWidget(labelTitle3);
    layoutMain->addLayout(layoutShow);
    layoutMain->setContentsMargins(40, 10, 40, 10);
    layoutMain->setSpacing(10);
}


bool ConstraintCode::isPositiveDecimal(const std::string& text) {
    // 正则表达式：匹配大于0小于1的小数
    QRegularExpression regExp("^(0|[1-9]?\\d*)\\.[1-9]?\\d*$");
    return regExp.match(QString::fromStdString(text)).hasMatch();
}

bool ConstraintCode::isInteger(const std::string& text) {
    // 正则表达式：匹配整数
    QRegularExpression regExp("^[1-9]?\\d*$");
    return regExp.match(QString::fromStdString(text)).hasMatch();
}


void ConstraintCode::on_begin_slots()
{
    textShow->clear();
    //获取文件类型参数和基类型参数
    std::string path = textRode->toPlainText().toStdString();
    qDebug()<<"文本内容:"<<path;
    QString qPath = textRode->toPlainText();
    QFile file(qPath);

    if(path == ""){
        QMessageBox::information(NULL, "提示", "请输入测试样本/路径");
        return;
    }

    if(!file.exists())
    {
        QMessageBox::information(NULL, "提示", "输入的路径不存在文件");
        return;
    }

    /*  依次判断输入参数是否合法  */
    std::string _minDis = minDistance->text().toStdString();
    if(_minDis == "" || (_minDis !="" && !isInteger(_minDis)))
    {
        QMessageBox::information(NULL, "提示", "最小距离应该为一个整数");
        return;
    }
    std::string _errRadius = errRadius->text().toStdString();
    if(_errRadius == "" ||(_errRadius !="" && !isInteger(_errRadius)))
    {
        QMessageBox::information(NULL, "提示", "错误球半径应该为一个整数");
        return;
    }
    std::string _clustersize = clusterSize->text().toStdString();
    if(_clustersize=="" ||(_clustersize !="" && !isInteger(_clustersize)))
    {
        QMessageBox::information(NULL, "提示", "读取数目应该为一个整数");
        return;
    }

    //创建模块指针
    PyObject* pModule = PyImport_ImportModule("subReconstruction");
    if (!pModule)
        qDebug()<<"获取模块指针失败";


    // 判断参数是否合法
    qDebug()<<"执行更新参数"<<_minDis <<"  " <<_errRadius<<"  "<<_clustersize;
    PyObject* pFuncCheck= PyObject_GetAttrString(pModule,"check");
    if(!pFuncCheck)
        qDebug()<<"获取函数指针失败";
    PyObject* pParaCheck = PyTuple_New(3);        //3个参数
    PyTuple_SetItem(pParaCheck, 0, Py_BuildValue("i",std::stoi(_clustersize)));
    PyTuple_SetItem(pParaCheck, 1, Py_BuildValue("i",std::stoi(_errRadius)));
    PyTuple_SetItem(pParaCheck, 2, Py_BuildValue("i",std::stoi(_minDis)));
    PyObject *CheckFuncBack = PyObject_CallObject(pFuncCheck,pParaCheck);
    char *pCheck = NULL;
    PyArg_Parse(CheckFuncBack,"s",&pCheck);
    qDebug()<<"返回值: "<<pCheck;
    if(QString::fromStdString(pCheck)!="pass")
    {
        QMessageBox::information(NULL, "提示", QString::fromStdString(pCheck));
        return;
    }


    //执行函数
    PyObject* pFuncText= PyObject_GetAttrString(pModule,"substitution_reconstruction");
    if(!pFuncText)
        qDebug()<<"获取函数指针失败";

    PyObject* pParaText = PyTuple_New(4);        //4个参数

    PyTuple_SetItem(pParaText, 0, Py_BuildValue("s",path.c_str()));
    PyTuple_SetItem(pParaText, 1, Py_BuildValue("i",std::stoi(_minDis)));
    PyTuple_SetItem(pParaText, 2, Py_BuildValue("i",std::stoi(_errRadius)));
    PyTuple_SetItem(pParaText, 3, Py_BuildValue("i",std::stoi(_clustersize)));
    PyObject *TextFuncBack = PyObject_CallObject(pFuncText,pParaText);
    char *p=NULL;
    PyArg_Parse(TextFuncBack,"s",&p);
    qDebug()<<"返回值: "<<p;
    textShow->setText(QString::fromStdString(p));
}

void ConstraintCode::on_flush_slots()
{
    //刷新界面的所有可编辑文本框
    textRode->setText("");
    textShow->setText("");
    errRadius->setText("");
    minDistance->setText("");
    clusterSize->setText("");
}


ConstraintCode::~ConstraintCode()
{
    //调用结束，销毁
    Py_Finalize();
}
