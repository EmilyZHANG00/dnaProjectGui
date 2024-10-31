
QT       += network

INCLUDEPATH += $$PWD/include

SOURCES +=  $$PWD/source/boderpane.cpp \
    $$PWD/source/log4z.cpp \
    $$PWD/source/rolltitles.cpp \
    $$PWD/source/lineprogress.cpp \
    $$PWD/source/slider.cpp \
     $$PWD/source/appinit.cpp \
     $$PWD/source/iconhelper.cpp \
     $$PWD/source/liquidplot.cpp \
     $$PWD/source/perfectclock.cpp \
    $$PWD/source/moviepicwidget.cpp \
    $$PWD/source/notificationpane.cpp \
    $$PWD/source/monitorthread.cpp \
    $$PWD/source/splitline.cpp \
    $$PWD/source/basedlg.cpp

HEADERS  +=  $$PWD/include/boderpane.h \
    $$PWD/include/appinit.h \
    $$PWD/include/iconhelper.h \
    $$PWD/include/liquidplot.h \
    $$PWD/include/log4z.h \
    $$PWD/include/perfectclock.h \
    $$PWD/include/moviepicwidget.h \
    $$PWD/include/notificationpane.h \
    $$PWD/include/slider.h \
    $$PWD/include/lineprogress.h \
    $$PWD/include/rolltitles.h \
    $$PWD/include/monitorthread.h \
    $$PWD/include/splitline.h \
    $$PWD/include/dumpcatch.h \
    $$PWD/include/basedlg.h


win32 {
    SOURCES += $$PWD/source/LimeCom_ShadowHelper.cpp
    HEADERS  += $$PWD/include/LimeCom_ShadowHelper.h
}

# 无边框辅助类，power by 雨田�
INCLUDEPATH += $$PWD/FramelessHelper
SOURCES += $$PWD/FramelessHelper/WidgetData.cpp \
    $$PWD/FramelessHelper/CursorPosCalculator.cpp \
    $$PWD/FramelessHelper/FramelessHelper.cpp
HEADERS  += $$PWD/FramelessHelper/WidgetData.h \
    $$PWD/FramelessHelper/CursorPosCalculator.h \
    $$PWD/FramelessHelper/FramelessHelperPrivate.h \
    $$PWD/FramelessHelper/FramelessHelper.h
	
# 托盘类，power by 飞杨青云
INCLUDEPATH += $$PWD/TrayIcon
SOURCES += $$PWD/TrayIcon/trayicon.cpp
HEADERS  += $$PWD/TrayIcon/trayicon.h
	
# 注册码类
INCLUDEPATH += $$PWD/KeyHelper
SOURCES += $$PWD/KeyHelper/keyhelper.cpp
HEADERS  += $$PWD/KeyHelper/keyhelper.h

# http下载
INCLUDEPATH += $$PWD/HttpDownloader
SOURCES += $$PWD/HttpDownloader/httpdownloader.cpp
HEADERS  += $$PWD/HttpDownloader/httpdownloader.h

include($$PWD/qtBreakpad/qt-breakpad.pri)


INCLUDEPATH += $$PWD/3rd_qxtglobalshortcut
include($$PWD/3rd_qxtglobalshortcut/3rd_qxtglobalshortcut.pri)
