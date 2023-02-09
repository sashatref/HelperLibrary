set(PROJECT_NAME zlib)

project(${PROJECT_NAME})

set(SOURCES
    crc32.h 
    deflate.h 
    gzguts.h 
    inffast.h 
    inffixed.h 
    inflate.h 
    inftrees.h 
    trees.h 
    zconf.h 
    zlib.h 
    zutil.h
    adler32.c 
    compress.c 
    crc32.c 
    deflate.c 
    gzclose.c 
    gzlib.c 
    gzread.c 
    gzwrite.c 
    infback.c 
    inffast.c 
    inflate.c 
    inftrees.c 
    trees.c 
    uncompr.c 
    zutil.c
)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
