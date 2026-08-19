QT += widgets serialport printsupport

CONFIG += c++17

# QCustomPlot 太大，MinGW 在 Debug 下汇编会报 "too many sections"，
# 加 -mbig-obj 启用大目标文件格式，让 as.exe 能容纳更多段
QMAKE_CXXFLAGS += -Wa,-mbig-obj

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    qcustomplot.cpp \
    tipdialog.cpp \
    widget.cpp

HEADERS += \
    qcustomplot.h \
    tipdialog.h \
    widget.h

FORMS += \
    tipdialog.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
