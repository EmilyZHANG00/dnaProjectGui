#ifndef SUBRECONSTRUCTION_H
#define SUBRECONSTRUCTION_H

#include "basechildpane.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include "utils.h"

class subReconstruction : public BaseChildPane
{
    Q_OBJECT
public:
    explicit subReconstruction(QWidget *parent = 0);
    ~subReconstruction();
private:
    void InitCtrl();
    bool isPositiveDecimal(const std::string& text) ;
    bool isInteger(const std::string& text);
private slots:
    void on_begin_slots();
    void on_flush_slots();
private:
    int m_add = 0;

    QLineEdit *textRode = new QLineEdit();
    // QTextEdit *textShow = new QTextEdit();
    QLabel *SumRunTime = new QLabel();   // 整体时间
    QLineEdit *savePath = new QLineEdit();   // 重构时间

    QLineEdit *errRadius = new QLineEdit();     // 半径
    QLineEdit *minDistance = new QLineEdit();   // 最小距离
    QLineEdit *clusterSize = new QLineEdit();   // 输入序列个数
};

#endif // SUBRECONSTRUCTION_H
