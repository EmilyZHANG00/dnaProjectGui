#ifndef TOOLS_H
#define TOOLS_H

#include "basechildpane.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QScrollArea>
#include "utils.h"

class Tools : public BaseChildPane
{
    Q_OBJECT
public:
    explicit Tools(QWidget *parent = 0);
    ~Tools();
private:
    void InitCtrl();
    bool isPositiveDecimal(const std::string& text) ;
    bool isInteger(const std::string& text);
private slots:
    void on_begin_slots();
    void on_flush_slots();

private:
    int m_add = 0;
    QLineEdit *lineRode = new QLineEdit();
    QTextEdit *textRode = new QTextEdit();
    // QTextEdit *textShow = new QTextEdit();

    QLabel *SumRunTime = new QLabel();   // 整体时间
    QLineEdit *savePath = new QLineEdit();   // 重构时间

    QLineEdit *baseLossRate = new QLineEdit();
    QLineEdit *rsNumber = new QLineEdit();
};

#endif // TOOLS_H
