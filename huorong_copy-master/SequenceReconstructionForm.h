#ifndef SEQUENCERECONSTRUCTIONFORM_H
#define SEQUENCERECONSTRUCTIONFORM_H

#include <QWidget>

namespace Ui {
class SequenceReconstructionForm;
}

class SequenceReconstructionForm : public QWidget
{
    Q_OBJECT

public:
    explicit SequenceReconstructionForm(QWidget *parent = nullptr);
    ~SequenceReconstructionForm();

private:
    Ui::SequenceReconstructionForm *ui;
};

#endif // SEQUENCERECONSTRUCTIONFORM_H
