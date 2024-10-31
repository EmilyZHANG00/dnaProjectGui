#ifndef SYSPROTECT_H
#define SYSPROTECT_H

#include "basechildpane.h"

class QStackedWidget;
class SysProtect : public BaseChildPane
{
    Q_OBJECT
public:
    explicit SysProtect(QWidget *parent = 0);

private:
    void InitCtrl();
    void InitLeftPane();
    void InitRightPane();

private:
    QWidget *m_pLeftPane;
    QWidget *m_RightPane;
    QStackedWidget *m_pStackedWidget;
};

#endif // SYSPROTECT_H
