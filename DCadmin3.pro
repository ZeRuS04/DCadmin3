TEMPLATE = app

QT += qml quick widgets network

SOURCES +=    sources/AdminBackend.cpp \
    sources/main.cpp \
    sources/ServerList.cpp \
    sources/Utilites.cpp
#    sources/XThread.cpp \
#    sources/Sessions.cpp \
#    sources/SocketCmd.cpp

RESOURCES += qml.qrc \
    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS +=     sources/AdminBackend.h \
    sources/Common.h \
    sources/Error.h \
    sources/ServerList.h \
    sources/Structs.h
#    sources/XThread.h \
#    sources/Sessions.h \
#    sources/SocketCmd.h

OTHER_FILES +=
