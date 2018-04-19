TARGET = dde-introduction
TEMPLATE = app
QT = core gui widgets dbus multimedia multimediawidgets
CONFIG += link_pkgconfig c++11
PKGCONFIG += dtkwidget dframeworkdbus

isEmpty(PREFIX){
    PREFIX = /usr
}

HEADERS += \
    src/basemodulewidget.h \
    src/mainwindow.h \
    src/model.h \
    src/normalwindow.h \
    src/worker.h \
    src/modules/about.h \
    src/modules/desktopmodemodule.h \
    src/modules/iconmodule.h \
    src/modules/moduleinterface.h \
    src/modules/normalmodule.h \
    src/modules/support.h \
    src/modules/videowidget.h \
    src/modules/wmmodemodule.h \
    src/widgets/basewidget.h \
    src/widgets/borderwidget.h \
    src/widgets/bottomnavigation.h \
    src/widgets/navigationbutton.h \
    src/widgets/nextbutton.h

SOURCES += \
    src/basemodulewidget.cc \
    src/main.cc \
    src/mainwindow.cc \
    src/model.cc \
    src/normalwindow.cc \
    src/worker.cc \
    src/modules/about.cc \
    src/modules/desktopmodemodule.cc \
    src/modules/iconmodule.cc \
    src/modules/moduleinterface.cc \
    src/modules/normalmodule.cc \
    src/modules/support.cc \
    src/modules/videowidget.cc \
    src/modules/wmmodemodule.cc \
    src/widgets/basewidget.cc \
    src/widgets/borderwidget.cc \
    src/widgets/bottomnavigation.cc \
    src/widgets/navigationbutton.cc \
    src/widgets/nextbutton.cc

RESOURCES += \
    dde-introduction.qrc

desktop.path = $$PREFIX/share/applications/
desktop.files += $$PWD/dde-introduction.desktop

target.path = $$PREFIX/bin/

TRANSLATIONS = translations/dde-introduction.ts

# Automating generation .qm files from .ts files
CONFIG(release, debug|release) {
    system($$PWD/translate_generation.sh)
}

qm_files.path = $$PREFIX/share/dde-introduction/translations/
qm_files.files = translations/*.qm

INSTALLS += desktop target
