#include "httpdownloader.h"
#include <QCryptographicHash>
#include <QStandardPaths>
#include <QFile>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QImage>
#include <QDir>
#include <QNetworkProxy>

CHttpDownloader::CHttpDownloader(QObject *parent)
    :QObject(parent)
{
    m_netAccessManager = new QNetworkAccessManager(this);
    m_netAccessManager->setProxy(QNetworkProxy::NoProxy);
}

CHttpDownloader::~CHttpDownloader()
{
#define SAFE_DELETE(pObj) \
    if (pObj != NULL) { delete pObj; pObj = NULL; }

    SAFE_DELETE(m_netAccessManager);

    if (m_fileDown.isOpen())
        m_fileDown.close();
}

void CHttpDownloader::ClearRp( QNetworkReply *pReply )
{
    if (pReply)
    {
        QString url = pReply->request().url().toString();
        QString postMD5 = pReply->property("postMD5").toString();
        QString postData = pReply->property("data").toByteArray();

        if(postMD5.isEmpty())
            m_mapRq.remove(url);
        else
            m_mapRq.remove(postMD5);

        m_mapRedirect.remove(url);
        m_mapRedirect.remove(postMD5);

        pReply->deleteLater();
    }
}

void CHttpDownloader::OnHttpGetRspProgress( qint64 bytesReceived, qint64 bytesTotal )
{
    if (NULL == sender())
        return;

    QNetworkReply* rp = qobject_cast<QNetworkReply*>(sender());
    if (NULL == rp)
        return;

    if (bytesTotal <= 0)
        return;

    QString strDisposition = rp->rawHeader("Content-Type");
    if (0 != strDisposition.compare("text/html"))  // 重定向 文本不接受
    {
        if (m_fileDown.isOpen())
        {
            m_fileDown.write(rp->readAll());
        }

        emit SignalDownloadProgress(bytesReceived, bytesTotal);
    }
}

void CHttpDownloader::OnHttpGetRspFinished()
{
    if (NULL == sender())
        return;

    QNetworkReply *rp = qobject_cast<QNetworkReply*>(sender());
    if (NULL == rp)
        return;

    QByteArray rpData;
    QString url = rp->url().toString();

    int nCode = rp->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QString strUrl = rp->attribute(QNetworkRequest::RedirectionTargetAttribute).toString();

    switch(nCode)
    {
    case 200:   // ok
        {
            m_fileDown.close();
            emit SignalDownloadDone();
        }
        break;

    case 301:
    case 302:   // redirect
        {
            if (!strUrl.isEmpty())
            {
                QString turl = m_mapRedirect[url];
                if(turl.isEmpty())
                    m_mapRedirect[strUrl] = url;
                else
                    m_mapRedirect[strUrl] = turl;

                Download(strUrl, m_fileDown.fileName());
            }
        }
        break;

    default:    // error
        {
            m_fileDown.close();
            emit SignalHttpError(nCode);
        }
        break;
    }

    ClearRp(rp);
}

void CHttpDownloader::OnError( QNetworkReply::NetworkError error )
{
    QNetworkReply *pReplay = qobject_cast<QNetworkReply*>(sender());
    // 输出错误码及错误信息;
    qDebug("error=%d, error=%s\n", error, pReplay->errorString().toStdString().c_str());
}

bool CHttpDownloader::Download( const QString &strUrl, QString strFullPath )
{
    qDebug("strUrl=%s,strFullPath=%s \n", strUrl.toStdString().c_str(), strFullPath.toStdString().c_str());

    if (m_mapRq.value(strUrl, false))
        return false;

    for (int i = 0; i < m_mapRedirect.values().count(); i++)
    {
        if(m_mapRedirect.values()[i] == strUrl)
            return false;
    }

    m_mapRq.insert(strUrl, true);

    m_fileDown.close();
    m_fileDown.setFileName(strFullPath);
    if (!m_fileDown.open(QIODevice::WriteOnly))
    {
        return false;
    }

    QNetworkRequest rq;
    QSslConfiguration config = rq.sslConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    //config.setProtocol(QSsl::TlsV1SslV3);
    rq.setSslConfiguration(config);

    rq.setUrl(QUrl(strUrl));
    QNetworkReply *pReply = m_netAccessManager->get(rq);
    connect(pReply, SIGNAL(finished()), this, SLOT(OnHttpGetRspFinished()));
    connect(pReply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(OnHttpGetRspProgress(qint64, qint64)));
    connect(pReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(OnError(QNetworkReply::NetworkError)));

    return true;
}
