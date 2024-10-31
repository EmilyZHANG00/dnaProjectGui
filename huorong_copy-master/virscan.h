#ifndef VIRSCAN_H
#define VIRSCAN_H

#include "basechildpane.h"

class Virscan : public BaseChildPane
{
    Q_OBJECT
public:
    explicit Virscan(QWidget *parent = 0);

private:
    void InitCtrl();

    void Start();
    void Stop();
    void Pause();

    virtual void OpenPage();
    virtual void ClosePage();

private:
    int m_nStep;
    QTimer *m_pTimer;
};

#endif // VIRSCAN_H
