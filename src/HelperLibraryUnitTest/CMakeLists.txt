set(PROJECT_NAME HelperLibraryUnitTest)

project(${PROJECT_NAME} VERSION 1.0.0)

set(SOURCES
    TestEnv.h
    lib/Json/TestQtJson.h
    lib/TestConverterFunctions.h
    lib/TestSimpleTextFilter.h
    models/ByteArrayWrapper.h
    models/myclass.h
    models/testobject.h
    testutils.h
    TestEnv.cpp
    lib/Json/TestJsonStreamReader.cpp
    lib/Json/TestQtJson.cpp
    lib/TestConverterFunctions.cpp
    lib/TestSimpleTextFilter.cpp
    main.cpp
    models/ByteArrayWrapper.cpp
    models/myclass.cpp
    models/testobject.cpp
    testutils.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt5::Core
    Qt5::Widgets
    Qt5::Sql
    HelperLibrary
    gtest
)

target_precompile_headers(${PROJECT_NAME} PRIVATE project_pch.h)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ".")

aviaNames()
makeAI()




