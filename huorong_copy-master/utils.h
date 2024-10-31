#ifndef UTILS_H
#define UTILS_H

#include <QtWidgets>

QLabel *CreateCustomLabel(QString strText, QString strColor = "#444444", int nSize = 16);
QPushButton *CreateCustomButton(QString strText);
QPushButton *CreateDefaultButton(QString strText);
QCheckBox *CreateCheckBox(QString strText);
QWidget *CreateSeparator(bool bVertical = false);
QWidget *CreateButtonGroup(QStringList btns, QButtonGroup **group);
QAction *CreateAction(const QString &text, QObject* parent, const QString &icon);
#endif // UTILS_H
