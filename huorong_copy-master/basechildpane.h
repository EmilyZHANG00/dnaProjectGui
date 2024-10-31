#ifndef BASECHILDPANE_H
#define BASECHILDPANE_H

#include <QWidget>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif


class BaseChildPane : public QWidget
{
    Q_OBJECT
public:
    explicit BaseChildPane(QWidget *parent = 0);

    virtual QString GetTitle();
    virtual void OpenPage();
    virtual void ClosePage();

signals:

public slots:

protected:
    QString m_strTitle;
};

#endif // BASECHILDPANE_H
