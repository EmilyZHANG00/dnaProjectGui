#include "basechildpane.h"

BaseChildPane::BaseChildPane(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setStyleSheet("BaseChildPane{background: #fff; border-top: 1px solid #f0f0f0; }");
}

QString BaseChildPane::GetTitle()
{
    return m_strTitle;
}

void BaseChildPane::OpenPage()
{

}

void BaseChildPane::ClosePage()
{

}
