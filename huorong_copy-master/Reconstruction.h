#ifndef RECONSTRUCTION_H
#define RECONSTRUCTION_H
#include "basechildpane.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include "utils.h"

class Reconstruction : public BaseChildPane
{
    Q_OBJECT
public:
    explicit Reconstruction(QWidget *parent = 0);
    ~Reconstruction();
private:
    void InitCtrl();
    bool isPositiveDecimal(const std::string& text) ;
    bool isInteger(const std::string& text);
private slots:
    void on_begin_slots();
    void on_flush_slots();
private:
    int m_add = 0;

    QTextEdit *textRode = new QTextEdit();
    QTextEdit *textShow = new QTextEdit();

    QLineEdit *baseLossRate = new QLineEdit();
    QLineEdit *rsNumber = new QLineEdit();
    QLineEdit *clusterRate = new QLineEdit();
    QLineEdit *clusterSize = new QLineEdit();
};

#endif // RECONSTRUCTION_H
