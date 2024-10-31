#ifndef SPLITLINE_H
#define SPLITLINE_H

#include <QWidget>

class Splitline : public QWidget
{
    Q_OBJECT
public:
    explicit Splitline(QWidget *parent = nullptr);

public:
    void SetHorizontalDirection(bool bHorizontal);
    void SetColor(QColor color);
    void SetMargin(int nMargin);

private:
    void paintEvent(QPaintEvent *event);

private:
    bool m_bHorizontal;
    QColor m_color;
    int m_nMargin;
};

#endif // SPLITLINE_H
