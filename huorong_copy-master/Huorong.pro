#-------------------------------------------------
#
# Project created by QtCreator 2023-01-18T13:12:41
#
#-------------------------------------------------
QT += core gui widgets
QT       += core gui
QT       += statemachine
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DNAProgram
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
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/ConstraintTest.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/ErrorCorrectionTest.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/ReconstructionTest.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/addfun.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/constraint/division_coding.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/constraint/fixed_length_coding.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/constraint/graph_generate.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/correction/Config.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/correction/DNA_BinaryEncoder.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/correction/DNA_QaryEncoder.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/correction/ImageProccess.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/correction/TextProcess.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/correction/VideoProcess.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/correction/binary_VTCode.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/correction/channel.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/correction/data_transfer.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/correction/diff_VTCode.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/correction/utils.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/recognition/Config.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/recognition/VTCode.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/recognition/channel.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/recognition/data_transfer.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/recognition/del_reconstruction.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYCode/subReconstruction.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/ConstraintTest.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/ErrorCorrectionTest.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/ReconstructionTest.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/constraint/__pycache__/division_coding.cpython-38.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/constraint/__pycache__/division_coding.cpython-39.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/constraint/__pycache__/fixed_length_coding.cpython-38.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/constraint/__pycache__/fixed_length_coding.cpython-39.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/constraint/__pycache__/graph_generate.cpython-38.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/constraint/__pycache__/graph_generate.cpython-39.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/constraint/division_coding.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/constraint/fixed_length_coding.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/constraint/graph_generate.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/Config.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/DNA_BinaryEncoder.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/DNA_QaryEncoder.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/ImageProccess.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/TextProcess.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/VideoProcess.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/__pycache__/Config.cpython-38.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/__pycache__/Config.cpython-39.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/__pycache__/DNA_BinaryEncoder.cpython-38.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/__pycache__/DNA_BinaryEncoder.cpython-39.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/__pycache__/DNA_QaryEncoder.cpython-38.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/__pycache__/DNA_QaryEncoder.cpython-39.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/__pycache__/ImageProccess.cpython-310.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/__pycache__/ImageProccess.cpython-38.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/__pycache__/ImageProccess.cpython-39.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/__pycache__/TextProcess.cpython-38.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/__pycache__/TextProcess.cpython-39.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/__pycache__/VideoProcess.cpython-38.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/__pycache__/VideoProcess.cpython-39.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/__pycache__/binary_VTCode.cpython-38.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/__pycache__/binary_VTCode.cpython-39.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/__pycache__/channel.cpython-38.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/__pycache__/channel.cpython-39.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/__pycache__/diff_VTCode.cpython-38.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/__pycache__/diff_VTCode.cpython-39.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/__pycache__/utils.cpython-38.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/__pycache__/utils.cpython-39.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/binary_VTCode.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/channel.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/data_transfer.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/diff_VTCode.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/correction/utils.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/recognition/Config.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/recognition/VTCode.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/recognition/__pycache__/Config.cpython-38.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/recognition/__pycache__/Config.cpython-39.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/recognition/__pycache__/VTCode.cpython-38.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/recognition/__pycache__/VTCode.cpython-39.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/recognition/__pycache__/channel.cpython-38.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/recognition/__pycache__/channel.cpython-39.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/recognition/__pycache__/data_transfer.cpython-38.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/recognition/__pycache__/data_transfer.cpython-39.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/recognition/__pycache__/del_reconstruction.cpython-38.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/recognition/__pycache__/del_reconstruction.cpython-39.pyc \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/recognition/channel.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/recognition/data_transfer.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/recognition/del_reconstruction.py \
    ../build-Huorong-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/bin/PYModule/subReconstruction.py \
    dnaEncodeIcon.ico \


# INCLUDEPATH += C:\Users\fairysc\AppData\Local\Programs\Python\Python313\include
# LIBS += -LC:\Users\fairysc\AppData\Local\Programs\Python\Python313\libs\


# # INCLUDEPATH += D:\Anaconda\include
# LIBS += -LD:\Anaconda\libs\
# -l_tkinter\
# -lpython3\
# -lpython39\


INCLUDEPATH += D:\Desktop\zzzz\DNAQTEXE\PY38ENV\include
LIBS += -LD:\Desktop\zzzz\DNAQTEXE\PY38ENV\libs\  -lpython38


#exe文件的输出位置
# DESTDIR = D:\Desktop\DNAQTEXE
#注意：-L 和 PATH 之间不能有空格

