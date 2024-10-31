#include "SequenceReconstructionForm.h"
#include "ui_SequenceReconstructionForm.h"

SequenceReconstructionForm::SequenceReconstructionForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SequenceReconstructionForm)
{
    ui->setupUi(this);
    setObjectName("序列重构");
    ui->widget->setStyleSheet("background-image: url(:/img/100/bk_main_normal.png);"
                        "background-repeat: round round");
}

SequenceReconstructionForm::~SequenceReconstructionForm()
{
    delete ui;
}
