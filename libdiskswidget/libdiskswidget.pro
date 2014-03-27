######################################################################
# Automatically generated by qmake (2.01a) ?? ?? 9 19:41:54 2008
######################################################################

TEMPLATE = lib
TARGET = diskswidget
DEPENDPATH += .
CONFIG += link_pkgconfig debug

PKGCONFIG += glib-2.0
INCLUDEPATH += . /usr/include/parted++
LIBS += -lparted++ -lparted -linstallengine

# Input
HEADERS += addpartition.h \
           directorytree.h \
           diskswidget.h \
           editpartition.h \
           archinfo.h \
           itembutton.h
FORMS += add.ui edit.ui
SOURCES += addpartition.cpp \
           directorytree.cpp \
           diskswidget.cpp \
           editpartition.cpp \
           archinfo.cpp \
           itembutton.cpp
RESOURCES = diskswidget.qrc

TRANSLATIONS += libdiskswidget_zh_CN.ts

target.path = /usr/lib
sources.files = diskswidget.h
sources.path  = /usr/include

translations.files = libdiskswidget_zh_CN.qm
translations.path = /usr/share/libdiskswidget/translations

INSTALLS += target sources translations
