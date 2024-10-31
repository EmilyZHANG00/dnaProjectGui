#include "SequenceReconstructionDialog.h"
#include "ui_SequenceReconstructionDialog.h"

SequenceReconstructionDialog::SequenceReconstructionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SequenceReconstructionDialog)
{
    ui->setupUi(this);
}

SequenceReconstructionDialog::~SequenceReconstructionDialog()
{
    delete ui;
}
