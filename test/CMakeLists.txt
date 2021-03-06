find_package(Threads REQUIRED)

if ($ENV{GOOGLETEST_DIR})
    SET(GOOGLETEST_DIR $ENV{GOOGLETEST_DIR})
else ()
    SET(GOOGLETEST_DIR "${PROJECT_SOURCE_DIR}/external/googletest")
    message(STATUS "using google test at ${GOOGLETEST_DIR}")
endif ()
if (EXISTS ${GOOGLETEST_DIR})
    SET(GTestSrc ${GOOGLETEST_DIR}/googletest)
    SET(GMockSrc ${GOOGLETEST_DIR}/googlemock)
else ()
    message( FATAL_ERROR "No googletest src dir found - set GOOGLETEST_DIR to enable!")
endif ()

include_directories(${PROJECT_SOURCE_DIR}/include/nui)
include_directories(${GTestSrc} ${GTestSrc}/include ${GMockSrc} ${GMockSrc}/include)

set(GTEST
    ${GTestSrc}/src/gtest-all.cc
    ${GMockSrc}/src/gmock-all.cc)

cmake_policy(SET CMP0037 OLD)

add_executable(build-tests EXCLUDE_FROM_ALL NuiMainTest.cpp tst_nuiobject.cpp ${GTEST})
target_link_libraries(build-tests nuicore nuiwidgets Threads::Threads)

add_custom_target(test COMMAND ${CMAKE_BINARY_DIR}/test/build-tests)
