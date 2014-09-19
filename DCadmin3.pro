TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    AdminBackend.cpp \
    ServerList.cpp \
    Utilites.cpp

RESOURCES += qml.qrc \
    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    Error.h \
    Structs.h \
    ServerList.h \
    AdminBackend.h \
    Common.h

OTHER_FILES +=
