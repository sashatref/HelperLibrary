#/********************************************************************
#	created:        19/06/2017
#	filename: 	ZipManager.pro
#	file ext:	qmake project
#	author:		Aleksandr Neborak

#	Copyright (C) Avia Ltd. Ukraine. Kremenchug 2017
#	All Rights Reserved

#	Project:	ZipManager

#*********************************************************************/

win32{
    include(../zlib/zlib.pri)
}


HEADERS += \
    $$PWD/gzipwrapper.h \
    $$PWD/zipreader.h \
    $$PWD/zipwriter.h

SOURCES += \
    $$PWD/gzipwrapper.cpp \
    $$PWD/qzip.cpp
