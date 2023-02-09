#/********************************************************************
#	created:        19/06/2017
#	filename: 	zlib.pro
#	file ext:	qmake project
#	author:		Aleksandr Neborak

#	Copyright (C) Avia Ltd. Ukraine. Kremenchug 2017
#	All Rights Reserved

#	Project:	zlib

#*********************************************************************/

HEADERS += \
    $$PWD/crc32.h \
    $$PWD/deflate.h \
    $$PWD/gzguts.h \
    $$PWD/inffast.h \
    $$PWD/inffixed.h \
    $$PWD/inflate.h \
    $$PWD/inftrees.h \
    $$PWD/trees.h \
    $$PWD/zconf.h \
    $$PWD/zlib.h \
    $$PWD/zutil.h

SOURCES += \
    $$PWD/adler32.c \
    $$PWD/compress.c \
    $$PWD/crc32.c \
    $$PWD/deflate.c \
    $$PWD/gzclose.c \
    $$PWD/gzlib.c \
    $$PWD/gzread.c \
    $$PWD/gzwrite.c \
    $$PWD/infback.c \
    $$PWD/inffast.c \
    $$PWD/inflate.c \
    $$PWD/inftrees.c \
    $$PWD/trees.c \
    $$PWD/uncompr.c \
    $$PWD/zutil.c

