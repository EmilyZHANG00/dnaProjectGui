#ifndef DYNAMICBTN_H
#define DYNAMICBTN_H

#include <QWidget>

class QLabel;
class DynamicBtn : public QWidget
{
    Q_OBJECT
public:
    explicit DynamicBtn(QWidget *parent = 0);
    void SetParam(QString icon, QString title, QString tip);

    void Start();
    void Stop();
    void Pause();
    void Clear();

protected:
    void paintEvent(QPaintEvent *ev);
    void timerEvent(QTimerEvent *event);

protected:
    QColor m_colorBg;
    QColor m_colorBorder;

private:
    bool m_bRuning;
    bool m_bStart;
    int m_nTimeId;
    int m_nRotate;

    QString m_icon;

    QLabel *m_labelIcon;
    QLabel *m_labelTitle;
    QLabel *m_labelTip;
};

#endif // DYNAMICBTN_H
