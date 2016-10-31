ACLOCAL_AMFLAGS = -I m4

AM_LDFLAGS = \
	-no-undefined

lib_LIBRARIES = libpjson.a

libpjson_a_SOURCES = \
    internal/json_parse.cpp \
    internal/json_node_object.cpp \
    internal/json_node_null.cpp \
    internal/json_node_bool.cpp \
    internal/json.cpp \
    internal/json_node_array.cpp \
    internal/json_node_string.cpp \
    internal/json_node_number.cpp \
    internal/json_node.cpp

pkginclude_HEADERS = \
    json.h

noinst_HEADERS = \
    internal/json_parse.h \
    internal/json_type.h \
    internal/json_node_string.h \
    internal/json_node_null.h \
    internal/map.h \
    internal/json_node_number.h \
    internal/json_node_object.h \
    internal/json_node.h \
    internal/json_node_array.h \
    internal/json_node_bool.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = pjson.pc
