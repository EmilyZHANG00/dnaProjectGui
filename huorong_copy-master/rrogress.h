#ifndef RROGRESS_H
#define RROGRESS_H

#include <QWidget>

class Progress : public QWidget
{
    Q_OBJECT
public:
    explicit Progress(QWidget *parent = 0);

private:
    void paintEvent(QPaintEvent *event);

private:
    int m_nProgress;
};

#endif // RROGRESS_H
