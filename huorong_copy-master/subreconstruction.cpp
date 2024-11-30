#pragma push_macro("slots")
#undef slots
#include <Python.h>
#pragma pop_macro("slots")

#include "subReconstruction.h"


QWidget *CreateFileItem(QString icon, QString title)
{
    QPushButton *item = new QPushButton();
    item->setStyleSheet("QPushButton{border-style:none;background: #fff; border: 0; }"
                        "QPushButton:hover {background: #fffcf8; border: 1px solid #ffe7c1; }");
    item->setFixedHeight(70);

    QLabel *labelIcon = new QLabel();
    QLabel *labelTitle = CreateCustomLabel(title, "#444444", 14);
    QCheckBox *checkBox = new QCheckBox();

    QComboBox *comboXL = new QComboBox();
    comboXL->addItem("文本",0);
    comboXL->addItem("图片",1);
    comboXL->setObjectName("cbx_file_type");

    checkBox->setStyleSheet("QCheckBox::indicator{width: 32px; height: 32px; }"
                            "QCheckBox::indicator:checked {border-image:url(:/img/100/switch-ON.png);}"
                            "QCheckBox::indicator:unchecked {border-image:url(:/img/100/switch-OFF.png);}");
    checkBox->setCursor(Qt::PointingHandCursor);

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

    layoutRight->addWidget(comboXL);
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

QWidget *SubCreateLineEditBoxItem(QString icon, QString title,QLineEdit *lineobj)
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


QWidget *SubCreateLabelBoxItem(QString icon, QString title,QLabel *lineobj)
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

subReconstruction::subReconstruction(QWidget *parent) : BaseChildPane(parent)
{
    m_strTitle = "替换重构";
    InitCtrl();
}

void subReconstruction::InitCtrl()
{
    QVBoxLayout *layoutTitle = new QVBoxLayout();
    // layoutTitle->addWidget(CreateCustomLabel("序列重构是DNA编码的重要研究方向"));
    // layoutTitle->setSpacing(10);



    QHBoxLayout *layoutTop = new QHBoxLayout();
    layoutTop->addLayout(layoutTitle);
    // layoutTop->addStretch(1);
    //layoutTop->addLayout(layoutTopBtn);


    QLabel *labelTitle1 = new QLabel("  " + QString("文件导入"));
    labelTitle1->setStyleSheet("border: 3px solid #c0a686; border-top-color: rgba(0,0,0,0); border-right-color: rgba(0,0,0,0); border-bottom-color: rgba(0,0,0,0); font-size: 14px");

    QLabel *labelTitle2 = new QLabel("  " + QString("参数"));
    labelTitle2->setStyleSheet("border: 3px solid #c0a686; border-top-color: rgba(0,0,0,0); border-right-color: rgba(0,0,0,0); border-bottom-color: rgba(0,0,0,0); font-size: 14px");

    QLabel *labelTitle3 = new QLabel("  " + QString("结果"));
    labelTitle3->setStyleSheet("border: 3px solid #c0a686; border-top-color: rgba(0,0,0,0); border-right-color: rgba(0,0,0,0); border-bottom-color: rgba(0,0,0,0); font-size: 14px");

    /*-----------------------------------------------------------------------*/
    // QVBoxLayout *layoutBox1L = new QVBoxLayout();
    // layoutBox1L->addWidget(CreateFileItem(":/img/175/sysprotect/sys/appnetctrl.png", "请选择编码类型"));

    // QVBoxLayout *layoutBox1R = new QVBoxLayout();
    // QLabel *labelTitle = CreateCustomLabel("输入文本路径/图片路径", "#444444", 14);
    // layoutBox1R->addWidget(labelTitle);
    // // layoutBox1R->addStretch(1);
    // layoutBox1R->addWidget(textRode);

    // QHBoxLayout *layoutBox1 = new QHBoxLayout();
    // layoutBox1->addLayout(layoutBox1L);
    // layoutBox1->addLayout(layoutBox1R);

    QHBoxLayout *layoutBox1 = new QHBoxLayout();
    layoutBox1->addWidget(CreateFileItem(":/img/175/sysprotect/sys/appnetctrl.png", "请选择编码类型"),1);
    layoutBox1->addWidget(SubCreateLineEditBoxItem(":/img/100/viruscan/icon_scan_completed.png", "文本路径/图片路径",textRode),4);

    QGridLayout *layoutCfg = new QGridLayout();
    layoutCfg->addWidget(SubCreateLineEditBoxItem(":/img/100/viruscan/icon_scan_completed.png", "码的最小距离",minDistance), 0, 0, 1, 1);
    layoutCfg->addWidget(SubCreateLineEditBoxItem(":/img/100/viruscan/icon_scan_completed.png", "错误球半径", errRadius), 0, 1, 1, 1);
    layoutCfg->addWidget(SubCreateLineEditBoxItem(":/img/100/viruscan/icon_scan_completed.png", "读取数目",clusterSize), 0, 2, 1, 1);


    QPushButton *btn_begin = new QPushButton();
    btn_begin->setText("开始");
    connect(btn_begin,SIGNAL(clicked()),this,SLOT(on_begin_slots()));

    QPushButton *btn_flush = new QPushButton();
    btn_flush->setText("刷新");
    connect(btn_flush,SIGNAL(clicked()),this,SLOT(on_flush_slots()));




    QHBoxLayout *layoutShow = new QHBoxLayout();

    QGridLayout *layoutShowGrid = new QGridLayout();
    layoutShowGrid->addWidget(SubCreateLabelBoxItem(":/img/100/viruscan/icon_scan_time.png", "总耗时",SumRunTime), 0, 0, 1, 1);
    layoutShowGrid->addWidget(SubCreateLineEditBoxItem(":/img/100/viruscan/icon_scan_time.png", "文件保存路径", savePath),1, 0, 1, 1);

    QVBoxLayout *layoutbtn = new QVBoxLayout();
    layoutbtn->addWidget(btn_begin);
    // layoutbtn->addSpacerItem(new QSpacerItem(0,160,QSizePolicy::Fixed,QSizePolicy::Fixed));
    layoutbtn->addWidget(btn_flush);

    layoutShow->addLayout(layoutShowGrid,4);
    layoutShow->addLayout(layoutbtn,1);


    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    QLabel *placeholder1 = new QLabel();
    QLabel *placeholder2 = new QLabel();

    layoutMain->addLayout(layoutTop);
    layoutMain->addWidget(CreateSeparator());
    layoutMain->addWidget(placeholder1);

    layoutMain->addWidget(labelTitle1); 
    layoutMain->addLayout(layoutBox1);

    layoutMain->addWidget(labelTitle2);
    layoutMain->addLayout(layoutCfg);

    layoutMain->addWidget(labelTitle3);
    layoutMain->addLayout(layoutShow);
    layoutMain->addWidget(placeholder2);
    layoutMain->setContentsMargins(40, 10, 40, 10);
}


bool subReconstruction::isPositiveDecimal(const std::string& text) {
    // 正则表达式：匹配大于0小于1的小数
    QRegularExpression regExp("^(0|[1-9]?\\d*)\\.[1-9]?\\d*$");
    return regExp.match(QString::fromStdString(text)).hasMatch();
}

bool subReconstruction::isInteger(const std::string& text) {
    // 正则表达式：匹配整数
    QRegularExpression regExp("^[1-9]?\\d*$");
    return regExp.match(QString::fromStdString(text)).hasMatch();
}


void subReconstruction::on_begin_slots()
{
    //获取文件类型参数和基类型参数
    std::string path = textRode->text().toStdString();
    qDebug()<<"文本内容:"<<path;
    QString qPath = textRode->text();
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
    // PyObject* pFuncText= PyObject_GetAttrString(pModule,"substitution_reconstruction");

    PyObject* pFuncText=nullptr;
    QComboBox *cbxEncodeType = this->findChild<QComboBox *>("cbx_file_type");
    int EncodeType = cbxEncodeType->currentIndex();
    if(EncodeType==0)
    {
        if(!qPath.endsWith(".txt")){
            QMessageBox::information(NULL, "提示", "请检查输入的路径后缀是否为txt");
            return;
        }
        pFuncText = PyObject_GetAttrString(pModule,"text_reconstruction");
    }
    else
    {
        if(!qPath.endsWith(".jpg")){
            QMessageBox::information(NULL, "提示", "请检查输入的路径后缀是否为jpg");
            return;
        }
        pFuncText= PyObject_GetAttrString(pModule,"image_reconstruction");
    }


    if(!pFuncText)
        qDebug()<<"获取函数指针失败";

    PyObject* pParaText = PyTuple_New(4);        //4个参数
    PyTuple_SetItem(pParaText, 0, Py_BuildValue("s",path.c_str()));
    PyTuple_SetItem(pParaText, 1, Py_BuildValue("i",std::stoi(_minDis)));
    PyTuple_SetItem(pParaText, 2, Py_BuildValue("i",std::stoi(_errRadius)));
    PyTuple_SetItem(pParaText, 3, Py_BuildValue("i",std::stoi(_clustersize)));
    PyObject *    TextFuncBack =  PyObject_CallObject(pFuncText,pParaText);
    if (TextFuncBack == NULL) {
        PyObject *exc_type, *exc_value, *exc_traceback;
        PyErr_Fetch(&exc_type, &exc_value, &exc_traceback);
        PyErr_NormalizeException(&exc_type, &exc_value, &exc_traceback);
        PyObject *exc_str = PyObject_Str(exc_value);
        const char *exc_msg = PyUnicode_AsUTF8(exc_str);
        fprintf(stderr, "[error]: %s\n", exc_msg);
        Py_XDECREF(exc_type);
        Py_XDECREF(exc_value);
        Py_XDECREF(exc_traceback);
        Py_XDECREF(exc_str);
        return ;
    }


    /* 返回值类型为5长的字符串元组 */
    if (PyTuple_Check(TextFuncBack) && PyTuple_Size(TextFuncBack) == 2) {
        PyObject *ResstrObj = PyTuple_GetItem(TextFuncBack, 0);
        if (PyUnicode_Check(ResstrObj)) {
            QString _Resstr = QString::fromUtf8(PyUnicode_AsUTF8(ResstrObj));
            SumRunTime->setText(_Resstr);
            qDebug() << "编码结果为：" << _Resstr;
        } else {
            qDebug() << "返回值不是字符串类型";
        }

        ResstrObj = PyTuple_GetItem(TextFuncBack, 1);
        if (PyUnicode_Check(ResstrObj)) {
           QString _Resstr = QString::fromUtf8(PyUnicode_AsUTF8(ResstrObj));
            savePath->setText(_Resstr);
            qDebug() << "编码结果为：" << _Resstr;
        } else {
            qDebug() << "返回值不是字符串类型";
        }
    } else {
        qDebug() << "返回值不是包含2个元素的元组";
    }

    // 清理Python对象
    Py_DECREF(TextFuncBack);
}

void subReconstruction::on_flush_slots()
{
    //刷新界面的所有可编辑文本框
    textRode->setText("");
    errRadius->setText("");
    minDistance->setText("");
    clusterSize->setText("");

    SumRunTime->setText("");
    savePath->setText("");
}


subReconstruction::~subReconstruction()
{
    // //调用结束，销毁
    // Py_Finalize();
}
