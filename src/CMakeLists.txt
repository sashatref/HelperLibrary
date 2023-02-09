add_subdirectory(HelperLibrary)
add_subdirectory(LicenseChecker)

if(BUILD_TESTS)
    add_subdirectory(HelperLibraryUnitTest)
endif()
