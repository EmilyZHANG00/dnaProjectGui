/**
 * @file      httpdownloader.h
 * @brief     http文件下载类
 * @author    胡德杰
 * @date      2021-03-05
 * @version   1.0
 * @copyright Copyright(C) 2020 NVR All rights reserved.
 */

#ifndef CHTTPSUPPORT_H
#define CHTTPSUPPORT_H

#include <QNetworkAccessManager>
#include <QFile>
#include <QNetworkReply>

class CHttpDownloader: public QObject
{
    Q_OBJECT

public:
    CHttpDownloader(QObject* parent = NULL);
    ~CHttpDownloader();

public:
    bool Download(const QString& strUrl, QString strFullPath);

private:
    void ClearRp(QNetworkReply* pReply);

private slots:
    void OnHttpGetRspProgress(qint64 bytesReceived, qint64 bytesTotal);     ///< http get 回复进度
    void OnHttpGetRspFinished();                                            ///< http get 处理完毕
    void OnError(QNetworkReply::NetworkError error);

signals:
    void SignalHttpError(int nCode);
    void SignalDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void SignalDownloadDone();

private:
    QNetworkAccessManager *m_netAccessManager;
    QMap<QString, bool> m_mapRq;                        ///< 当前正在处理的请求url 和是否正在处理
    QMap<QString, QString> m_mapRedirect;               ///< 重定向关系
    QFile m_fileDown;
};

#endif // CHTTPSUPPORT_H
