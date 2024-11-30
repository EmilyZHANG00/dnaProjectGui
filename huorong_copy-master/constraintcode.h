#ifndef CONSTRAINTCODE_H
#define CONSTRAINTCODE_H

#include "basechildpane.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include "utils.h"

class ConstraintCode : public BaseChildPane
{
public:
    ConstraintCode(QWidget *parent = 0);
    ~ConstraintCode();

private:
    void InitCtrl();
    bool isPositiveDecimal(const std::string& text) ;
    bool isInteger(const std::string& text);
    bool isBinStr(const std::string& text);
    bool checkInputPara();


private slots:
    void on_GraphGen_slots();
    void on_flush_GraphGen_slots();
    void on_flush_multi_slots();
    void on_run_multi_slots();
    void on_flush_one_slots();
    void on_run_one_slots();

private:
    int m_add = 0;

    QTextEdit *textRode = new QTextEdit();
    QTextEdit *textShow = new QTextEdit();

    /* --参数部分-- */
    QLineEdit *SSA = new QLineEdit();     // SSA长度约束
    QLineEdit *RLL = new QLineEdit();     // RLL长度约束
    QLineEdit *GC_LEN = new QLineEdit();   // GC长度约束
    QLineEdit *GC_AT = new QLineEdit();   // GC和AT的约束个数
    QLineEdit *M_CNT = new QLineEdit();   // 人工碱基个数

    QLabel *GraphSize = new QLabel();   //图的规模大小
    QLabel *PRadius = new QLabel();   // 谱半径


    /* -- 原信息 编码信息  解码信息--*/
    QLineEdit *SourceSeq = new QLineEdit();     // 原信息
    QLabel *EncodeSeq = new QLabel();     // 编码信息
    QLabel *DecodeSeq = new QLabel();   // 解码信息

    QLabel *Pq = new QLabel();     // 编码信息
    QLabel *LogPq = new QLabel();   // 解码信息

    /* --  存储密度  --*/
    QLabel *Density = new QLabel();   // 存储密度
    QLabel *RunTime = new QLabel();   // 运行时间
    QLineEdit *IterateCnt = new QLineEdit();   // 迭代次数
};

#endif // CONSTRAINTCODE_H
