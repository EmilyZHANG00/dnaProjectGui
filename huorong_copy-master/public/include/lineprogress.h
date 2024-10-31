#ifndef LINEPROGRESS_H
#define LINEPROGRESS_H

#include <QWidget>

class LineProgress : public QWidget
{
    Q_OBJECT
public:
    explicit LineProgress(QWidget *parent = nullptr);

public:
    void SetValue(int value, int total);

private:
    void paintEvent(QPaintEvent *event);

private:
    int m_nTotal;
    int m_nValue;
};

#endif // LINEPROGRESS_H
