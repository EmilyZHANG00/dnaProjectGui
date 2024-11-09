#pragma push_macro("slots")
#undef slots
#include <Python.h>
#pragma pop_macro("slots")

#include "Reconstruction.h"

QWidget *CreateCfgItem(QString icon, QString title, QString tip="")
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
        comboXL->addItem("文本",0);
        comboXL->addItem("图片",1);
        comboXL->addItem("视频",2);
        comboXL->setObjectName("cbx_input");
    }
    if(tip == "2") {
        comboXL->addItem("全空间编码",1);
        comboXL->addItem("全空间+分隔符",2);
        comboXL->addItem("VT码+分隔符",3);
        comboXL->setObjectName("cbx_encodeType");
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

QWidget *CreateLineEditBoxItem(QString icon, QString title,QLineEdit *lineobj)
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


Reconstruction::Reconstruction(QWidget *parent) : BaseChildPane(parent)
{
    m_strTitle = "删除重构";
    InitCtrl();
}

void Reconstruction::InitCtrl()
{
    QVBoxLayout *layoutTitle = new QVBoxLayout();
    layoutTitle->addWidget(CreateCustomLabel("序列重构是DNA编码的重要研究方向"));
    layoutTitle->setSpacing(10);



    QHBoxLayout *layoutTop = new QHBoxLayout();
    layoutTop->addLayout(layoutTitle);
    layoutTop->addStretch(1);
    //layoutTop->addLayout(layoutTopBtn);


    QLabel *labelTitle1 = new QLabel("  " + QString("文件导入"));
    labelTitle1->setStyleSheet("border: 3px solid #c0a686; border-top-color: rgba(0,0,0,0); border-right-color: rgba(0,0,0,0); border-bottom-color: rgba(0,0,0,0); font-size: 14px");

    QLabel *labelTitle2 = new QLabel("  " + QString("误差参数"));
    labelTitle2->setStyleSheet("border: 3px solid #c0a686; border-top-color: rgba(0,0,0,0); border-right-color: rgba(0,0,0,0); border-bottom-color: rgba(0,0,0,0); font-size: 14px");

    QLabel *labelTitle3 = new QLabel("  " + QString("算法结果"));
    labelTitle3->setStyleSheet("border: 3px solid #c0a686; border-top-color: rgba(0,0,0,0); border-right-color: rgba(0,0,0,0); border-bottom-color: rgba(0,0,0,0); font-size: 14px");

    /*-----------------------------------------------------------------------*/
    QVBoxLayout *layouttdr = new QVBoxLayout();
    layouttdr->addWidget(CreateCfgItem(":/img/100/sysprotect/virus/file.png", "请选择测试样本类型","1"));
    layouttdr->addWidget(CreateCfgItem(":/img/175/sysprotect/sys/appnetctrl.png", "请选择编码类型","2"));

    QLabel *labelTitle = CreateCustomLabel("输入测试文本/路径", "#444444", 14);

    QVBoxLayout *layoutwbk = new QVBoxLayout();
    layoutwbk->addWidget(labelTitle);
    layoutwbk->addStretch(1);
    layoutwbk->addWidget(textRode);

    QHBoxLayout *layoutdrz = new QHBoxLayout();
    layoutdrz->addLayout(layouttdr);
    layoutdrz->addLayout(layoutwbk);

    QGridLayout *layoutCfg = new QGridLayout();
    layoutCfg->addWidget(CreateLineEditBoxItem(":/img/100/viruscan/icon_scan_completed.png", "碱基丢失率(默认值为0.005)",baseLossRate), 0, 0, 1, 1);
    // layoutCfg->addWidget(CreateLineEditBoxItem(":/img/100/viruscan/icon_scan_completed.png", "簇丢失率", clusterRate), 0, 1, 1, 1);
    layoutCfg->addWidget(CreateLineEditBoxItem(":/img/100/viruscan/icon_scan_completed.png", "平均簇大小(默认大小20)",clusterSize), 0, 1, 1, 1);
    layoutCfg->addWidget(CreateLineEditBoxItem(":/img/100/viruscan/icon_scan_completed.png", "RS冗余列个数(默认大小30)", rsNumber), 1, 0, 1, 1);


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
    //layoutMain->addStretch(1);
    layoutMain->addWidget(labelTitle3);
    layoutMain->addLayout(layoutShow);
    layoutMain->setContentsMargins(40, 10, 40, 10);
    layoutMain->setSpacing(10);
}


bool Reconstruction::isPositiveDecimal(const std::string& text) {
    // 正则表达式：匹配大于0小于1的小数
    QRegularExpression regExp("^(0|[1-9]?\\d*)\\.[1-9]?\\d*$");
    return regExp.match(QString::fromStdString(text)).hasMatch();
}

bool Reconstruction::isInteger(const std::string& text) {
    // 正则表达式：匹配整数
    QRegularExpression regExp("^[1-9]?\\d*$");
    return regExp.match(QString::fromStdString(text)).hasMatch();
}


void Reconstruction::on_begin_slots()
{
    textShow->clear();
    //获取文件类型参数和基类型参数
    QComboBox *cbxInput = this->findChild<QComboBox *>("cbx_input");
    QComboBox *cbxEncodeType = this->findChild<QComboBox *>("cbx_encodeType");
    int fileType = cbxInput->currentIndex();
    int encodeType = cbxEncodeType->currentIndex()+1;
    qDebug()<<"编码方式序号:"<<encodeType;
    std::string path = textRode->toPlainText().toStdString();
    qDebug()<<"文本内容:"<<path;
    QString qPath = textRode->toPlainText();
    QFile file(qPath);

    if(path == ""){
        QMessageBox::information(NULL, "提示", "请输入测试样本/路径");
        return;
    }

    if(fileType !=0 && !file.exists())
    {
        QMessageBox::information(NULL, "提示", "输入的路径不存在文件");
        return;
    }

    /*  依次判断输入参数是否合法  */
    std::string _baselossrate = baseLossRate->text().toStdString();
    if(_baselossrate !="" && !isPositiveDecimal(_baselossrate))
    {
        QMessageBox::information(NULL, "提示", "输入碱基丢失率应该为0-1之间的小数");
        return;
    }

    // std::string _clusterrate = clusterRate->text().toStdString();
    // if(_clusterrate !="" && !isPositiveDecimal(_clusterrate))
    // {
    //     QMessageBox::information(NULL, "提示", "输入簇丢失率应该为0-1之间的小数");
    //     return;
    // }

    std::string _rsnumber = rsNumber->text().toStdString();
    if(_rsnumber !="" && !isInteger(_rsnumber))
    {
        QMessageBox::information(NULL, "提示", "输入冗余序列数目应该整数");
        return;
    }
    std::string _clustersize = clusterSize->text().toStdString();
    if(_clustersize !="" && !isInteger(_clustersize))
    {
        QMessageBox::information(NULL, "提示", "输入平均簇大小应该为一个整数");
        return;
    }

    if (fileType == 1)
    {

        if(!qPath.endsWith(".jpg") && !qPath.endsWith(".png")){
            QMessageBox::information(NULL, "提示", "请检查输入的路径后缀是否为图片");
            return;
        }
        else
        {
            textShow->setText("正在执行图片文件的编解码，请耐心等候");
            textShow->update();
        }
    }

    if (fileType == 2)
    {

        if(!qPath.endsWith(".mp4")){
            QMessageBox::information(NULL, "提示", "请检查输入的路径后缀是否为视频");
            return;
        }
        else
        {
            textShow->setText("正在执行视频文件的编解码，请耐心等候");
            textShow->update();
        }
    }

    //创建模块指针
    PyObject* pModule = PyImport_ImportModule("ReconstructionTest");
    if (!pModule)
        qDebug()<<"获取模块指针失败";


    // 更新函数
    qDebug()<<"执行更新参数"<<_baselossrate<<"   "<<"  " <<_rsnumber<<"  "<<_clustersize;
    PyObject* pFuncText= PyObject_GetAttrString(pModule,"setPara");
    if(!pFuncText)
        qDebug()<<"获取函数指针失败";

    PyObject* pParaText = PyTuple_New(3);        //4个参数

    if(_baselossrate!="")
        PyTuple_SetItem(pParaText, 0, Py_BuildValue("d",std::stod(_baselossrate)));  //参数1为文本内容
    else
        PyTuple_SetItem(pParaText, 0, Py_BuildValue("d",std::stod("0")));  //参数1为文本内容

    // if(_clusterrate!="")
    //     PyTuple_SetItem(pParaText, 1,  Py_BuildValue("d",std::stod(_clusterrate)));  //参数2为int型
    // else
    //     PyTuple_SetItem(pParaText, 1, Py_BuildValue("d",std::stod("0")));  //参数1为文本内容

    if(_rsnumber!="")
        PyTuple_SetItem(pParaText, 1,  Py_BuildValue("i",std::stoi(_rsnumber)));  //参数1为文本内容
    else
        PyTuple_SetItem(pParaText, 1, Py_BuildValue("i",std::stod("0")));  //参数1为文本内容
    if(_clustersize!="")
        PyTuple_SetItem(pParaText, 2,  Py_BuildValue("i",std::stoi(_clustersize))); //参数2为int型
    else
        PyTuple_SetItem(pParaText, 2, Py_BuildValue("i",std::stod("0")));  //参数1为文本内容

    PyObject *TextFuncBack = PyObject_CallObject(pFuncText,pParaText);
    std::string textString = "";
    char *p=NULL;
    PyArg_Parse(TextFuncBack,"s",&p);
    qDebug()<<"返回值: "<<p;

    if (fileType == 0) {
        qDebug()<<"文本数据测试"<<path.c_str();
        //获取python文本函数
        PyObject* pFuncText= PyObject_GetAttrString(pModule,"textTest_Reconstruction");
        if(!pFuncText)
            qDebug()<<"获取函数指针失败";

        PyObject* pParaText = PyTuple_New(2);        // 2个参数
        PyTuple_SetItem(pParaText, 0, Py_BuildValue("s",path.c_str()));  //参数1为文本内容
        PyTuple_SetItem(pParaText, 1, Py_BuildValue("i",encodeType));  //参数2为int型

        PyObject *TextFuncBack = PyObject_CallObject(pFuncText,pParaText);
        std::string textString = "";
        char *p=NULL;
        PyArg_Parse(TextFuncBack,"s",&p);
        //lineRode->setText(QString::number(res));
        qDebug()<<"返回值: "<<p;
        textShow->setText(QString::fromStdString(p));
    }
    else if(fileType == 1)
    {
        qDebug()<<"图片数据测试"<<path.c_str();
        //获取python图片函数
        PyObject* pFuncImage= PyObject_GetAttrString(pModule,"imageTest_Reconstruction");
        if(!pFuncImage)
            qDebug()<<"获取函数指针失败";

        PyObject* pParaImage = PyTuple_New(2);        // 2个参数
        PyTuple_SetItem(pParaImage, 0, Py_BuildValue("s",path.c_str()));  //参数1为QString型
        PyTuple_SetItem(pParaImage, 1, Py_BuildValue("i",encodeType));  //参数1为int型
        PyObject *ImageFuncBack = PyObject_CallObject(pFuncImage,pParaImage);
        char *p=NULL;
        PyArg_Parse(ImageFuncBack,"s",&p);
        //lineRode->setText(QString::number(res));
        qDebug()<<"返回值: "<<p;
        textShow->setText(QString::fromStdString(p));
    }
    else if(fileType == 2)
    {
        //获取python视频函数
        qDebug()<<"视频数据测试";

        PyObject* pFunVcideo= PyObject_GetAttrString(pModule,"videoTest_Reconstruction");
        if(!pFunVcideo)
            qDebug()<<"获取函数指针失败";

        PyObject* pParaVcideo = PyTuple_New(2);        // 2个参数
        PyTuple_SetItem(pParaVcideo, 0, Py_BuildValue("s",path.c_str()));  //参数1为路径
        PyTuple_SetItem(pParaVcideo, 1, Py_BuildValue("i",encodeType));  //参数1为int型

        PyObject *VideoFuncBack = PyObject_CallObject(pFunVcideo,pParaVcideo);
        char *p=NULL;
        PyArg_Parse(VideoFuncBack,"s",&p);
        //lineRode->setText(QString::number(res));
        qDebug()<<"返回值: "<<p;
        textShow->setText(QString::fromStdString(p));
    }
}




void Reconstruction::on_flush_slots()
{
    //刷新界面的所有可编辑文本框
    textRode->setText("");
    textShow->setText("");
    baseLossRate->setText("");
    rsNumber->setText("");
    // clusterRate->setText("");
    clusterSize->setText("");

}


Reconstruction::~Reconstruction()
{
    //调用结束，销毁
    Py_Finalize();
}
