#-------------------------------------------------
#
# Project created by QtCreator 2023-01-18T13:12:41
#
#-------------------------------------------------
QT += core gui widgets
QT       += core gui
QT       += statemachine
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DNAPragram
TEMPLATE = app
# add by 阿木大叔
unix {
    MOC_DIR = tmp/unix/moc
    OBJECTS_DIR = tmp/unix/obj
    UI_DIR = tmp/unix/ui
}

win32 {
    MOC_DIR = tmp/win32/moc
    OBJECTS_DIR = tmp/win32/obj
    UI_DIR = tmp/win32/ui
}
DESTDIR = bin

SOURCES += main.cpp\
    Reconstruction.cpp \
    SequenceReconstructionDialog.cpp \
    SequenceReconstructionForm.cpp \
    configlist.cpp \
    constraintcode.cpp \
        mainwnd.cpp \
    subreconstruction.cpp \
    textshow.cpp \
    tools.cpp \
    basechildpane.cpp \
    sysprotect.cpp \
    virscan.cpp \
    dynamicbtn.cpp \
    rrogress.cpp \
    utils.cpp

HEADERS  += mainwnd.h \
    Reconstruction.h \
    SequenceReconstructionDialog.h \
    SequenceReconstructionForm.h \
    configlist.h \
    constraintcode.h \
    subreconstruction.h \
    textshow.h \
    tools.h \
    basechildpane.h \
    sysprotect.h \
    virscan.h \
    dynamicbtn.h \
    rrogress.h \
    utils.h

include ($$PWD/public/public.pri)

RESOURCES += \
    huorong.qrc

RC_ICONS += $$PWD/dnaEncodeIcon.ico
RC_FILE += Huorong_resource.rc

FORMS += \
    SequenceReconstructionDialog.ui \
    SequenceReconstructionForm.ui

DISTFILES += \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/ErrorCorrectionTest.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/ReconstructionTest.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/addfun.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/correction/Config.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/correction/DNA_BinaryEncoder.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/correction/DNA_QaryEncoder.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/correction/ImageProccess.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/correction/TextProcess.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/correction/VideoProcess.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/correction/binary_VTCode.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/correction/channel.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/correction/data_transfer.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/correction/diff_VTCode.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/correction/utils.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/recognition/Config.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/recognition/VTCode.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/recognition/channel.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/recognition/data_transfer.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/recognition/del_reconstruction.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/subReconstruction.py \
    dnaEncodeIcon.ico \
    build/qt_6_5_3-Release/bin/ErrorCorrectionTest.py \


# INCLUDEPATH += C:\Users\fairysc\AppData\Local\Programs\Python\Python313\include
# LIBS += -LC:\Users\fairysc\AppData\Local\Programs\Python\Python313\libs\
INCLUDEPATH += D:\Anaconda\include
LIBS += -LD:\Anaconda\libs\
-l_tkinter\
-lpython3\
-lpython39\

#注意：-L 和 PATH 之间不能有空格

