QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 thread

INCLUDEPATH += "./include/opencv4"
INCLUDEPATH += "./include"

QMAKE_LFLAGS += -Wl,-rpath,"../WiFi_detector/lib"

SOURCES += \
    accesspointsettings.cpp \
    addnewelementinscene.cpp \
    addnewmap.cpp \
    customscene.cpp \
    form_log.cpp \
    forminteractivemap.cpp \
    infowidgit.cpp \
    listelement.cpp \
    main.cpp \
    settingsarea.cpp \
    settingsperimetr.cpp \
    startsettingenter.cpp

HEADERS += \
    accesspointsettings.h \
    addnewelementinscene.h \
    addnewmap.h \
    customscene.h \
    form_log.h \
    forminteractivemap.h \
    infowidgit.h \
    listelement.h \
    settingsarea.h \
    settingsperimetr.h \
    singleton.hpp \
    startsettingenter.h

FORMS += \
    accesspointsettings.ui \
    addnewelementinscene.ui \
    addnewmap.ui \
    form_log.ui \
    forminteractivemap.ui \
    settingsarea.ui \
    settingsperimetr.ui \
    startsettingenter.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
   dark/style.qrc
#RESOURCES += \
 #  light/style.qrc

#unix:!macx: LIBS += -L$$PWD/lib/ -lhv_static

#INCLUDEPATH += $$PWD/include
#DEPENDPATH += $$PWD/include

#unix:!macx: PRE_TARGETDEPS += $$PWD/lib/libhv_static.a
