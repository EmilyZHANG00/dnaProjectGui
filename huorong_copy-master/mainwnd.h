#ifndef MAINWND_H
#define MAINWND_H

#include <QDialog>
#include "basechildpane.h"

#include <functional>
typedef std::function<void()> Function;

class Tools;
class SysProtect;
class Reconstruction;
class Virscan;
class TextShow;
class subReconstruction;
class ConstraintCode;
class MainPane : public QWidget
{
    Q_OBJECT

public:
    MainPane(QWidget *parent = 0);
    ~MainPane();

private:
    void InitCtrl();
    void InitTop();
    void InitCenter();
    void InitBottom();
    void UpdateCtrlState();

    // void InitDNAINTRO();   // 修改 原名字为KillVirus
    // void ShowVirusKill();
    // void HideVirusKill();

    // void ShowTools();
    // void HideTools();

    void ShowChild(QWidget *child);
    void HideChild();

    BaseChildPane *GetChild();
    QString GetTitle();

    void paintEvent(QPaintEvent *event);

private:
    QWidget *m_pTopTools;
    QWidget *m_pCenter;
    QWidget *m_pBottom;

    QPushButton *m_btnBack;
    QWidget *m_pVirusKill;
    SysProtect *m_pSysProtect;


    Tools *m_pTools;                       /* 纠删码 */
    Reconstruction *m_pReconstruction;    /* 删除重构 */
    subReconstruction  *m_pSubReconstruction;  /* 替换重构  */
    //subReconstruction    *m_pConstraintCode;      /* 约束编码 */
    ConstraintCode    *m_pConstraintCode;      /* 约束编码 */

    // TextShow *m_pTextShowBackGround;
    // TextShow *m_pTextShowStatus;
    // TextShow *m_pTextShowProgress;
    // TextShow *m_pTextShowConstraint;

    QPixmap *m_pixFlash;
    bool m_bShowChild;
};

class MainWnd : public QDialog
{
    Q_OBJECT

public:
    MainWnd(QWidget *parent = 0);
    ~MainWnd();

private:
    void paintEvent(QPaintEvent *event);

private:
    MainPane *m_pMianPane;
};

QPushButton *CreateBtn(QString title, QString img);
QPushButton *CreateMiniBtn(QString title, QString img, QSize size = QSize(36, 24), Function&& fn = nullptr);

#endif // MAINWND_H
