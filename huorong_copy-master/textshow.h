#ifndef TEXTSHOW_H
#define TEXTSHOW_H
#include "basechildpane.h"



class TextShow : public BaseChildPane
{
    Q_OBJECT
public:
    explicit TextShow(QWidget *parent = 0,QString _info="",QString _path=QString("background-image: url(:/img/dnaMain.png)"));

private:
    void InitCtrl();

    void Start();
    void Stop();
    void Pause();

    virtual void OpenPage();
    virtual void ClosePage();

private:
    int m_nStep;
    QString Textinfo;
    QString m_pathstyleSheet;
    QTimer *m_pTimer;
};

#endif // TextShow_H
