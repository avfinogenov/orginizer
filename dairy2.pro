QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    activity.cpp \
    activitywindow2.cpp \
    branch.cpp \
    main.cpp \
    mainwindow2.cpp \
    rowbase.cpp

HEADERS += \
    activity.h \
    activitywindow2.h \
    branch.h \
    mainwindow2.h \
    rowbase.h

FORMS += \
    activitywindow2.ui \
    mainwindow2.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
