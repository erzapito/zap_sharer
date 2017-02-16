cmake_minimum_required (VERSION 3.0)
project (ZapSharer)

SET(CMAKE_CXX_FLAGS "-g -std=c++11 -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -fprofile-arcs -ftest-coverage")
 
SET(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
 
SET(CMAKE_EXE_LINKER_FLAGS="-fprofile-arcs -ftest-coverage")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

ADD_DEFINITIONS ("${MHD_DEFINITIONS}")
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost 1.32 REQUIRED COMPONENTS system log thread unit_test_framework)
find_package(Jsoncpp REQUIRED)
find_package(LibMicroHTTPD REQUIRED)
find_package(Sqlite3 REQUIRED)
include(CodeCoverage REQUIRED)

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} ${Jsoncpp_INCLUDE_DIR} )

add_subdirectory(src)
add_subdirectory(test)
