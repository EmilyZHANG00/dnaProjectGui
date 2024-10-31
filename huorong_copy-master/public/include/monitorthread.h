
#ifndef MONITORTHREAD_H
#define MONITORTHREAD_H

#include <QObject>
#include <QThread>
#include <QVector>

class CMonitorThread : public QThread
{
    Q_OBJECT

public:
    ~CMonitorThread();

public:
    static CMonitorThread *Instance();

    void SetParam(int nPid);
    void SetInterval(int nInterval);
    void StopTask() { m_bQuitQueryTask = true; }
    void Pause(bool bPause) { m_bPause = bPause; }

protected:
    //QThread的虚函数
    //线程处理函数
    //不能直接调用，通过start()间接调用
    void run();

private:
    explicit CMonitorThread(QObject *parent = 0);

signals:
    void SignalProcState(bool bSuc, double fUsedMem, int nCpu, QString strExeName);          // 处理完成信号

private:
    static CMonitorThread *self;

    bool m_bQuitQueryTask;
    bool m_bMustTimeFrame;
    int m_nPid;
    int m_nInterval;
    bool m_bPause;
};

#define MONITOR CMonitorThread::Instance()
#define MONITOR_START MONITOR->start();
#define MONITOR_QUIT MONITOR->StopTask();MONITOR->quit();MONITOR->wait();

#endif // MONITORTHREAD_H
