#include "constraintcode.h"
#pragma push_macro("slots")
#undef slots
#include <Python.h>
#include<iostream>
#pragma pop_macro("slots")


QWidget *CreateMultiItem(QString icon, QString title, QString tip="")
{
    QPushButton *item = new QPushButton();
    item->setStyleSheet("QPushButton{border-style:none;background: #fff; border: 0; }"
                        "QPushButton:hover {background: #fffcf8; border: 1px solid #ffe7c1; }");
    item->setFixedHeight(70);

    QLabel *labelIcon = new QLabel();
    QLabel *labelTitle = CreateCustomLabel(title, "#444444", 14);
    QLabel *labelTip = CreateCustomLabel(tip, "#777777", 12);
    QCheckBox *checkBox = new QCheckBox();

    QLineEdit *lineText = new QLineEdit();
    lineText->setReadOnly(true);

    QComboBox *comboXL = new QComboBox();
    if(tip == "1") {
        comboXL->addItem("定长编码",0);
        comboXL->addItem("变长编码",1);
        comboXL->setObjectName("cbx_one");
    }
    if(tip == "2") {
        comboXL->addItem("定长编码",0);
        comboXL->addItem("变长编码",1);
        comboXL->setObjectName("cbx_multi");
    }

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
    //layoutRight->addWidget(labelTip);
    if(tip == "")
        layoutRight->addWidget(lineText);
    else
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


QWidget *ConsCreateLabelBoxItem(QString icon, QString title,QLabel *lineobj)
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
    // layoutTitle->addWidget(CreateCustomLabel(" "));
    // layoutTitle->setSpacing(10);



    QHBoxLayout *layoutTop = new QHBoxLayout();
    layoutTop->addLayout(layoutTitle);
    layoutTop->addStretch(1);
    //layoutTop->addLayout(layoutTopBtn);


    QLabel *labelTitle1 = new QLabel("  " + QString("德布罗因图生成"));
    labelTitle1->setStyleSheet("border: 3px solid #c0a686; border-top-color: rgba(0,0,0,0); border-right-color: rgba(0,0,0,0); border-bottom-color: rgba(0,0,0,0); font-size: 14px");

    QLabel *labelTitle2 = new QLabel("  " + QString("单次编解码测试"));
    labelTitle2->setStyleSheet("border: 3px solid #c0a686; border-top-color: rgba(0,0,0,0); border-right-color: rgba(0,0,0,0); border-bottom-color: rgba(0,0,0,0); font-size: 14px");

    QLabel *labelTitle3 = new QLabel("  " + QString("变长编码平均存储密度测试"));
    labelTitle3->setStyleSheet("border: 3px solid #c0a686; border-top-color: rgba(0,0,0,0); border-right-color: rgba(0,0,0,0); border-bottom-color: rgba(0,0,0,0); font-size: 14px");

    /*-----------------------------------------------------------------------*/
    /* Box1 生成德布罗因图部分 输入+按钮 + 输出部分 */
    QVBoxLayout *layoutBox1 = new QVBoxLayout();
    QLabel *labelTitle = CreateCustomLabel("输入相关参数", "#444444", 14);

    QGridLayout *layoutGraphPara = new QGridLayout();   /* 参数 */
    layoutGraphPara->addWidget(ConsCreateLineEditBoxItem(":/img/100/viruscan/icon_scan_completed.png", "SSA约束长度",SSA), 0, 0, 1, 1);
    layoutGraphPara->addWidget(ConsCreateLineEditBoxItem(":/img/100/viruscan/icon_scan_completed.png", "RLL约束长度", RLL), 0, 1, 1, 1);
    layoutGraphPara->addWidget(ConsCreateLineEditBoxItem(":/img/100/viruscan/icon_scan_completed.png", "GC约束长度",GC_LEN), 0, 2, 1, 1);
    layoutGraphPara->addWidget(ConsCreateLineEditBoxItem(":/img/100/viruscan/icon_scan_completed.png", "GC含量误差范围", GC_AT), 0, 3, 1, 1);
    layoutGraphPara->addWidget(ConsCreateLineEditBoxItem(":/img/100/viruscan/icon_scan_completed.png", "人工碱基个数",M_CNT), 0, 4, 1, 1);


    QPushButton *btn_GraphGen = new QPushButton();  /* 按钮 */
    btn_GraphGen->setText("生成图");
    // connect(btn_GraphGen,SIGNAL(clicked()),this,SLOT(on_GraphGen_slots()));
    connect(btn_GraphGen, &QPushButton::clicked, this, &ConstraintCode::on_GraphGen_slots);

    QPushButton *btn_GraphGenflush = new QPushButton();  /* 按钮 */
    btn_GraphGenflush->setText("刷新");
    connect(btn_GraphGenflush, &QPushButton::clicked, this, &ConstraintCode::on_flush_GraphGen_slots);

    QVBoxLayout *layoutGraphbtn = new QVBoxLayout();
    layoutGraphbtn->addWidget(btn_GraphGen);
    layoutGraphbtn->addWidget(btn_GraphGenflush);


    QGridLayout *layoutGraphRes = new QGridLayout();   /* 结果 */
    layoutGraphRes->addWidget(ConsCreateLabelBoxItem(":/img/100/viruscan/icon_scan_time.png", "德布罗因图规模",GraphSize), 0, 0, 1, 1);
    layoutGraphRes->addWidget(ConsCreateLabelBoxItem(":/img/100/viruscan/icon_scan_time.png", "谱半径", PRadius), 0, 1, 1, 1);


    QHBoxLayout *layoutBox1H = new QHBoxLayout();
    layoutBox1H->addLayout(layoutGraphRes);
    layoutBox1H->addLayout(layoutGraphbtn);

    layoutBox1->addLayout(layoutGraphPara);
    layoutBox1->addLayout(layoutBox1H);


    /* Box2 单次编码部分 左：输入信息 编码后信息 解码后信息    右边:下拉框+按钮*/
    QHBoxLayout *layoutBox2 = new QHBoxLayout();
    QGridLayout *layoutEncodeData = new QGridLayout();   /* 参数 */
    layoutEncodeData->addWidget(CreateMultiItem(":/img/175/sysprotect/sys/appnetctrl.png", "请选择编码类型","1"),0,0,1,1);
    layoutEncodeData->addWidget(ConsCreateLineEditBoxItem(":/img/100/viruscan/icon_scan_completed.png", "输入信息",SourceSeq), 0, 1, 1, 1);
    layoutEncodeData->addWidget(ConsCreateLabelBoxItem(":/img/100/viruscan/icon_scan_time.png", "解码后数据",DecodeSeq), 0, 2, 1, 1);

    layoutEncodeData->addWidget(ConsCreateLabelBoxItem(":/img/100/viruscan/icon_scan_time.png", "编码后数据", EncodeSeq), 1, 0, 1, 4);

    QVBoxLayout *layoutFixedLabel = new QVBoxLayout();
    layoutFixedLabel->addWidget(ConsCreateLabelBoxItem(":/img/100/viruscan/icon_scan_time.png", "p:q",Pq));
    layoutFixedLabel->addWidget(ConsCreateLabelBoxItem(":/img/100/viruscan/icon_scan_time.png", "码率",LogPq));


    QPushButton *btn_run_one = new QPushButton();
    btn_run_one->setText("运行");
    // connect(btn_run_one,SIGNAL(clicked()),this,SLOT(on_run_one_slots()));
    connect(btn_run_one, &QPushButton::clicked, this, &ConstraintCode::on_run_one_slots);
    QPushButton *btn_flush_one = new QPushButton();
    btn_flush_one->setText("刷新");
    // connect(btn_flush_one,SIGNAL(clicked()),this,SLOT(on_flush_one_slots()));
    connect(btn_flush_one, &QPushButton::clicked, this, &ConstraintCode::on_flush_one_slots);


    QVBoxLayout *layoutEncodebtn = new QVBoxLayout();
    layoutEncodebtn->addWidget(btn_run_one);
    layoutEncodebtn->addWidget(btn_flush_one);


    layoutBox2->addLayout(layoutEncodeData,5);
    layoutBox2->addLayout(layoutFixedLabel,1);
    layoutBox2->addLayout(layoutEncodebtn,1);



    /* Box3 多次运行求平均值 左：选择框  中：循环次数  执行用时  右：按钮 */
    QHBoxLayout *layoutBox3 = new QHBoxLayout();
    QGridLayout *layoutMutiEncodeData= new QGridLayout();   /* 参数 */
    // layoutMutiEncodeData->addWidget(CreateMultiItem(":/img/175/sysprotect/sys/appnetctrl.png", "请选择编码类型","2"),0,0,1,1);
    layoutMutiEncodeData->addWidget(ConsCreateLineEditBoxItem(":/img/100/viruscan/icon_scan_completed.png", "迭代次数",IterateCnt), 0, 0, 1, 1);
    layoutMutiEncodeData->addWidget(ConsCreateLabelBoxItem(":/img/100/viruscan/icon_scan_time.png", "运行时间", RunTime), 0, 1, 1, 1);
    layoutMutiEncodeData->addWidget(ConsCreateLabelBoxItem(":/img/100/viruscan/icon_scan_time.png", "存储密度",Density), 0, 2, 1, 1);


    QPushButton *btn_run_Multi = new QPushButton();
    btn_run_Multi->setText("运行");
    // connect(btn_run_Multi,SIGNAL(clicked()),this,SLOT(on_run_multi_slots()));
    connect(btn_run_Multi, &QPushButton::clicked, this, &ConstraintCode::on_run_multi_slots);

    QPushButton *btn_flush_multi = new QPushButton();
    btn_flush_multi->setText("刷新");
    // connect(btn_flush_multi,SIGNAL(clicked()),this,SLOT(on_flush_multi_slots()));
    connect(btn_flush_multi, &QPushButton::clicked, this, &ConstraintCode::on_flush_multi_slots);


    QVBoxLayout *layoutMultiEncodebtn = new QVBoxLayout();
    layoutMultiEncodebtn->addWidget(btn_run_Multi);
    layoutMultiEncodebtn->addWidget(btn_flush_multi);

    layoutBox3->addLayout(layoutMutiEncodeData,5);
    layoutBox3->addLayout(layoutMultiEncodebtn,1);


    /*   组装界面显示信息   */
    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    layoutMain->addLayout(layoutTop);
    layoutMain->addWidget(CreateSeparator());
    layoutMain->addWidget(labelTitle1);     /* 第一部分 输入参数 求德布罗因图 */
    layoutMain->addLayout(layoutBox1);
    layoutMain->addWidget(labelTitle2);     /* 第二部分 单次运行 */
    layoutMain->addLayout(layoutBox2);
    layoutMain->addWidget(labelTitle3);      /* 第三部分 多次运行求平均存储密度 */
    layoutMain->addLayout(layoutBox3);
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

bool ConstraintCode::isBinStr(const std::string& text) {
    // 正则表达式：匹配整数
    for(auto e:text)
    {
        if(e=='0' || e=='1')
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool ConstraintCode::checkInputPara()
{
    std::string _ssa = SSA->text().toStdString();
    if(_ssa == "" || (_ssa !="" && !isInteger(_ssa)))
    {
        QMessageBox::information(NULL, "提示", "ssa约束应该为一个整数");
        return false;
    }
    std::string _rll = RLL->text().toStdString();
    if(_rll == "" || (_rll !="" && !isInteger(_rll)))
    {
        QMessageBox::information(NULL, "提示", "rll约束应该为一个整数");
        return false;
    }
    std::string _gclen = GC_LEN->text().toStdString();
    if(_gclen == "" || (_gclen !="" && !isInteger(_gclen)))
    {
        QMessageBox::information(NULL, "提示", "GC长度约束应该为一个整数");
        return false;
    }
    std::string _gcat = GC_AT->text().toStdString();
    if(_gcat == "" || (_gcat !="" && !isInteger(_gcat)))
    {
        QMessageBox::information(NULL, "提示", "GC&AT差阈值应该为一个整数");
        return false;
    }
    std::string _mcnt = M_CNT->text().toStdString();
    if(_mcnt == "" || (_mcnt !="" && !isInteger(_mcnt)))
    {
        QMessageBox::information(NULL, "提示", "人工碱基个数应该为一个整数");
        return false;
    }
    return true;
}

void ConstraintCode::on_GraphGen_slots()
{
        /*  判断输入参数是否合法预期 */
        if(!checkInputPara())
            return ;

        std::string _ssa = SSA->text().toStdString();
        std::string _rll = RLL->text().toStdString();
        std::string _gclen = GC_LEN->text().toStdString();
        std::string _gcat = GC_AT->text().toStdString();
        std::string _mcnt = M_CNT->text().toStdString();


        //创建模块指针
        PyObject* pModule = PyImport_ImportModule("ConstraintTest");
        if (!pModule)
        {    qDebug()<<"获取模块指针失败";
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


        //判断输入是否符合要求
        PyObject* pFuncCheck= PyObject_GetAttrString(pModule,"checkPara");
        if(!pFuncCheck)
            qDebug()<<"获取函数指针失败";
        PyObject* pParaCheck = PyTuple_New(5);        //3个参数
        PyTuple_SetItem(pParaCheck, 0, Py_BuildValue("i",std::stoi(_ssa)));
        PyTuple_SetItem(pParaCheck, 1, Py_BuildValue("i",std::stoi(_rll)));
        PyTuple_SetItem(pParaCheck, 2, Py_BuildValue("i",std::stoi(_gclen)));
        PyTuple_SetItem(pParaCheck, 3, Py_BuildValue("i",std::stoi(_gcat)));
        PyTuple_SetItem(pParaCheck, 4, Py_BuildValue("i",std::stoi(_mcnt)));
        PyObject *CheckFuncBack = PyObject_CallObject(pFuncCheck,pParaCheck);
        char *pCheck = NULL;
        PyArg_Parse(CheckFuncBack,"s",&pCheck);
        if(CheckFuncBack)
        {
           qDebug()<<"返回值: "<<pCheck;
        }
        else
        {
            qDebug()<<"checkPara Failed!"<<pCheck;
            return;
        }
        if(QString::fromStdString(pCheck)!="pass")
        {
            QMessageBox::information(NULL, "提示", QString::fromStdString(pCheck));
            return;
        }

        //执行函数
        PyObject* pFuncText= PyObject_GetAttrString(pModule,"graph_generate_QT");
        if(!pFuncText)
            qDebug()<<"获取函数指针失败";

        if (pFuncText == NULL) {
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

        PyObject* pParaText = PyTuple_New(5);        //4个参数

        PyTuple_SetItem(pParaText, 0, Py_BuildValue("i",std::stoi(_ssa)));
        PyTuple_SetItem(pParaText, 1, Py_BuildValue("i",std::stoi(_rll)));
        PyTuple_SetItem(pParaText, 2, Py_BuildValue("i",std::stoi(_gclen)));
        PyTuple_SetItem(pParaText, 3, Py_BuildValue("i",std::stoi(_gcat)));
        PyTuple_SetItem(pParaText, 4, Py_BuildValue("i",std::stoi(_mcnt)));
        PyObject *TextFuncBack = PyObject_CallObject(pFuncText,pParaText);



        // 检查调用是否成功
        if (!TextFuncBack) {
            PyErr_Print();
            // 处理错误情况
            return;
        }

        // 确保返回值是一个包含三个元素的元组
        if (PyTuple_Check(TextFuncBack) && PyTuple_Size(TextFuncBack) == 3) {
            // 解析第一个返回值：整数
            std::string  GraphSizestr="",eigenvaluestr="";
            PyObject *lenVertexSetObj = PyTuple_GetItem(TextFuncBack, 0);
            if (PyLong_Check(lenVertexSetObj)) {
                long lenVertexSet = PyLong_AsLong(lenVertexSetObj);
                GraphSizestr += std::to_string(lenVertexSet);
                qDebug() << "顶点集的大小: " << lenVertexSet;
            } else {
                qDebug() << "第一个返回值不是整数类型";
            }

            // 解析第二个返回值：整数
            PyObject *lenVertexSet0Obj = PyTuple_GetItem(TextFuncBack, 1);
            if (PyLong_Check(lenVertexSet0Obj)) {
                long lenVertexSet0 = PyLong_AsLong(lenVertexSet0Obj);
                GraphSizestr += "*" ;
                GraphSizestr+= std::to_string(lenVertexSet0);
                qDebug() << "顶点集第一个元素的大小: " << lenVertexSet0;
            } else {
                qDebug() << "第二个返回值不是整数类型";
            }

            GraphSize->setText(QString::fromStdString(GraphSizestr));

            // 解析第三个返回值：可能是浮点数或复数
            PyObject *eigenvalueObj = PyTuple_GetItem(TextFuncBack, 2);
            if (PyFloat_Check(eigenvalueObj)) {
                double eigenvalue = PyFloat_AsDouble(eigenvalueObj);
                eigenvaluestr = std::to_string(eigenvalue);
                qDebug() << "特征值（浮点数）: " << eigenvalue;
            } else if (PyComplex_Check(eigenvalueObj)) {
                Py_complex eigenvalue = PyComplex_AsCComplex(eigenvalueObj);
                qDebug() << "特征值（复数）: " << eigenvalue.real << " + " << eigenvalue.imag << "i";
            } else {
                qDebug() << "第三个返回值不是浮点数或复数类型";
            }
            PRadius->setText(QString::fromStdString(eigenvaluestr));
        } else {
            qDebug() << "返回值不是包含三个元素的元组";
        }
        // 清理Python对象
        Py_DECREF(TextFuncBack);
        return ;
}
void ConstraintCode::on_flush_GraphGen_slots()
{
    //刷新界面的所有可编辑文本框
    SSA->setText("");
    RLL->setText("");
    GC_LEN->setText("");
    GC_AT->setText("");
    M_CNT->setText("");
}

void ConstraintCode::on_run_multi_slots()
{
    qDebug()<<"on_run_multi_slots";
    /*  判断输入参数是否合法  */
    if(!checkInputPara())
        return ;

    std::string _ssa = SSA->text().toStdString();
    std::string _rll = RLL->text().toStdString();
    std::string _gclen = GC_LEN->text().toStdString();
    std::string _gcat = GC_AT->text().toStdString();
    std::string _mcnt = M_CNT->text().toStdString();
    std::string _iteratecnt= IterateCnt->text().toStdString();
    if(_iteratecnt == "" || (_iteratecnt !="" && !isInteger(_iteratecnt)))
    {
        QMessageBox::information(NULL, "提示", "迭代次数应该是一个整数");
        return ;
    }

    on_GraphGen_slots();
    //创建模块指针
    PyObject* pModule = PyImport_ImportModule("ConstraintTest");
    if (!pModule)
        qDebug()<<"获取模块指针失败";

    //执行函数
    PyObject* pParaText = PyTuple_New(6);        //6个参数
    PyTuple_SetItem(pParaText, 0, Py_BuildValue("i",std::stoi(_ssa)));
    PyTuple_SetItem(pParaText, 1, Py_BuildValue("i",std::stoi(_rll)));
    PyTuple_SetItem(pParaText, 2, Py_BuildValue("i",std::stoi(_gclen)));
    PyTuple_SetItem(pParaText, 3, Py_BuildValue("i",std::stoi(_gcat)));
    PyTuple_SetItem(pParaText, 4, Py_BuildValue("i",std::stoi(_mcnt)));
    PyTuple_SetItem(pParaText, 5, Py_BuildValue("i",std::stoi(_iteratecnt)));

    PyObject* pFuncText=nullptr;
    // QComboBox *cbxEncodeType = this->findChild<QComboBox *>("cbx_multi");
    // int EncodeType = cbxEncodeType->currentIndex();
    // qDebug()<<"编码类型index："<<EncodeType <<" 迭代次数:" <<_iteratecnt ;
    // qDebug()<<"执行on_run_one_slots11";
    // qDebug()<<"参数："<<_ssa ;
    // qDebug()<< "  "<<_rll;
    // qDebug()<<"  "<<_gclen ;
    // qDebug()<< "  "<<_gcat;
    // qDebug()<<"  "<<_mcnt ;


    // if(EncodeType==0)
    // {
    //     pFuncText = PyObject_GetAttrString(pModule,"fixed_length_coding_QT");
    // }
    // else
    // {
    //    pFuncText= PyObject_GetAttrString(pModule,"division_coding_QT");
    // }

    pFuncText= PyObject_GetAttrString(pModule,"division_coding_QT");
    if(!pFuncText)
        qDebug()<<"获取函数指针失败";
    PyObject *TextFuncBack = PyObject_CallObject(pFuncText,pParaText);
    qDebug()<<"成功返回，开始解析返回值";

    // 确保返回值是一个包含一个元素的元组
    if (PyTuple_Check(TextFuncBack) && PyTuple_Size(TextFuncBack) == 2) {
        // 解析第一个返回值：字符串
        PyObject *codingResObj = PyTuple_GetItem(TextFuncBack,0);
        if (PyFloat_Check(codingResObj)) {
            QString densityStr = QString::fromStdString(std::to_string(PyFloat_AsDouble(codingResObj)));
            qDebug() << "存储密度：" << densityStr;
            Density->setText(densityStr);
        } else {
            qDebug() << "第一个返回值类型：" << Py_TYPE(codingResObj)->tp_name;
            qDebug() << "第一个返回值不是Float类型";
        }


        // 解析第二个返回值：字符串
        PyObject *binNumObj = PyTuple_GetItem(TextFuncBack, 1);
        if (PyUnicode_Check(binNumObj)) {
            QString binNum = QString::fromUtf8(PyUnicode_AsUTF8(binNumObj));
            RunTime->setText(binNum);
            qDebug() << "用时：" << binNum;
        } else {
            qDebug() << "第二个返回值不是字符串类型";
        }
    } else {
        qDebug() << "返回值未达到预期";
    }
    // 清理Python对象
    Py_DECREF(TextFuncBack);

}

void ConstraintCode::on_flush_multi_slots()
{
    //刷新界面的所有可编辑文本框
    // SSA->setText("");
    // RLL->setText("");
    // GC_LEN->setText("");
    // GC_AT->setText("");
    // M_CNT->setText("");

    Density->setText("");
    RunTime->setText("");
    IterateCnt->setText("");
}


void ConstraintCode::on_run_one_slots()
{
    qDebug()<<"执行on_run_one_slots";
    /*  判断输入参数是否合法  */
    if(!checkInputPara())
        return ;

    std::string _ssa = SSA->text().toStdString();
    std::string _rll = RLL->text().toStdString();
    std::string _gclen = GC_LEN->text().toStdString();
    std::string _gcat = GC_AT->text().toStdString();
    std::string _mcnt = M_CNT->text().toStdString();
    std::string _sourceseq = SourceSeq->text().toStdString();

    if(_sourceseq == "" || (_sourceseq !="" && !isBinStr(_sourceseq)))
    {
        QMessageBox::information(NULL, "提示", "输入序列应该为01序列");
        return ;
    }

    on_GraphGen_slots();
    //创建模块指针
    PyObject* pModule = PyImport_ImportModule("ConstraintTest");
    if (!pModule)
        qDebug()<<"获取模块指针失败";

    //执行函数
    PyObject* pParaText = PyTuple_New(6);        //6个参数
    PyTuple_SetItem(pParaText, 0, Py_BuildValue("i",std::stoi(_ssa)));
    PyTuple_SetItem(pParaText, 1, Py_BuildValue("i",std::stoi(_rll)));
    PyTuple_SetItem(pParaText, 2, Py_BuildValue("i",std::stoi(_gclen)));
    PyTuple_SetItem(pParaText, 3, Py_BuildValue("i",std::stoi(_gcat)));
    PyTuple_SetItem(pParaText, 4, Py_BuildValue("i",std::stoi(_mcnt)));
    PyTuple_SetItem(pParaText, 5, Py_BuildValue("s",_sourceseq.c_str()));


    PyObject* pFuncText=nullptr;
    QComboBox *cbxEncodeType = this->findChild<QComboBox *>("cbx_one");
    int EncodeType = cbxEncodeType->currentIndex();
    // qDebug()<<"编码类型index："<<EncodeType <<" 编码数据：" <<_sourceseq ;
    // qDebug()<<"执行on_run_one_slots11";
    // qDebug()<<" 编码数据：" <<_sourceseq ;
    // qDebug()<<"参数："<<_ssa ;
    // qDebug()<< "  "<<_rll;
    // qDebug()<<"  "<<_gclen ;
    // qDebug()<< "  "<<_gcat;
    // qDebug()<<"  "<<_mcnt ;
    // qDebug()<< "  "<<_sourceseq ;

    if(EncodeType==0)
    {
        pFuncText = PyObject_GetAttrString(pModule,"fixed_length_coding_one_QT");
    }
    else
    {
        pFuncText= PyObject_GetAttrString(pModule,"division_coding_one_QT");
    }

    if(!pFuncText)
        qDebug()<<"获取函数指针失败";
    PyObject *TextFuncBack = PyObject_CallObject(pFuncText,pParaText);
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
    else
    {
        qDebug()<<"成功返回，开始解析返回值";
    }

    // 确保返回值是一个包含两个元素的元组
    if (PyTuple_Check(TextFuncBack) && PyTuple_Size(TextFuncBack) == 4) {
        //
        QLabel * ArraypLabel[4]={EncodeSeq,DecodeSeq,Pq,LogPq};
        for(int i=0;i<4;i++)
        {
            PyObject *codingResObj = PyTuple_GetItem(TextFuncBack, i);
            if (PyUnicode_Check(codingResObj)) {
                QString codingRes = QString::fromUtf8(PyUnicode_AsUTF8(codingResObj));
                ArraypLabel[i]->setText(codingRes);
                qDebug() << "返回值为:" << codingRes;
            }
        }
    } else {
        qDebug() << "返回值不是包含4个元素的元组";
    }

    // 清理Python对象
    Py_DECREF(TextFuncBack);
}

void ConstraintCode::on_flush_one_slots()
{
    // //刷新界面的所有可编辑文本框
    // SSA->setText("");
    // RLL->setText("");
    // GC_LEN->setText("");
    // GC_AT->setText("");
    // M_CNT->setText("");

    SourceSeq->setText("");
    EncodeSeq->setText("");
    DecodeSeq->setText("");
    Pq->setText("");
    LogPq->setText("");
}

ConstraintCode::~ConstraintCode()
{
    //调用结束，销毁
    // Py_Finalize();
}
