#ifndef SEQUENCERECONSTRUCTIONDIALOG_H
#define SEQUENCERECONSTRUCTIONDIALOG_H

#include <QDialog>

namespace Ui {
class SequenceReconstructionDialog;
}

class SequenceReconstructionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SequenceReconstructionDialog(QWidget *parent = nullptr);
    ~SequenceReconstructionDialog();

private:
    Ui::SequenceReconstructionDialog *ui;
};

#endif // SEQUENCERECONSTRUCTIONDIALOG_H
