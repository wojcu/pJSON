#-------------------------------------------------
#
# Project created by QtCreator 2016-09-04T20:10:06
#
#-------------------------------------------------

QT       -= core gui

TARGET = pJSON
TEMPLATE = lib
CONFIG += staticlib

unix {
    target.path = /usr/lib
    INSTALLS += target
}

HEADERS += \
    internal/json_node.h \
    internal/json_node_array.h \
    internal/json_node_bool.h \
    internal/json_node_null.h \
    internal/json_node_number.h \
    internal/json_node_object.h \
    internal/json_node_string.h \
    internal/json_parse.h \
    internal/json_type.h \
    internal/map.h \
    json.h

SOURCES += \
    internal/json.cpp \
    internal/json_node.cpp \
    internal/json_node_array.cpp \
    internal/json_node_bool.cpp \
    internal/json_node_null.cpp \
    internal/json_node_number.cpp \
    internal/json_node_object.cpp \
    internal/json_node_string.cpp \
    internal/json_parse.cpp

