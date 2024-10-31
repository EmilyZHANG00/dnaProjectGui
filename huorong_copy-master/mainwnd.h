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
    void InitDNAINTRO();   // 修改 原名字为KillVirus
    void UpdateCtrlState();

    void ShowVirusKill();
    void HideVirusKill();

    void ShowTools();
    void HideTools();

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
    Tools *m_pTools;
    SysProtect *m_pSysProtect;
    Reconstruction *m_pReconstruction;
    Virscan *m_pVirscan;
    TextShow *m_pTextShowBackGround;
    TextShow *m_pTextShowStatus;
    TextShow *m_pTextShowProgress;
    TextShow *m_pTextShowConstraint;

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
