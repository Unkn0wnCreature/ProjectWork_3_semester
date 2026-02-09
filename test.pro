QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Используйте короткие имена без пробелов
INCLUDEPATH += C:/PROGRA~1/PostgreSQL/15/include
LIBS += C:/PROGRA~1/PostgreSQL/15/lib/libpq.lib

# Уберите дублирующиеся строки ниже, они уже есть выше

SOURCES += \
    Contact.cpp \
    ContactBook.cpp \
    ContactWindow.cpp \
    DBStorage.cpp \
    FileStorage.cpp \
    SearchWindow.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Contact.h \
    ContactBook.h \
    ContactWindow.h \
    DBStorage.h \
    FileStorage.h \
    SearchWindow.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
