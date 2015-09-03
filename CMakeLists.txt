cmake_minimum_required (VERSION 3.2)
project (ZapSharer)

SET(CMAKE_CXX_FLAGS="-g -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -fprofile-arcs -ftest-coverage")
 
SET(CMAKE_C_FLAGS="-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
 
#SET(CMAKE_SHARED_LINKER_FLAGS="-fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS="-fprofile-arcs -ftest-coverage")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

ADD_DEFINITIONS ("${MHD_DEFINITIONS}")

find_package(Boost 1.32 REQUIRED COMPONENTS system)
find_package(Jsoncpp REQUIRED)
find_package(LibMicroHTTPD REQUIRED)

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} ${Jsoncpp_INCLUDE_DIR} )

add_subdirectory(src)
add_subdirectory(test)

#add_executable(ZapSharer 
#	src/ZapSharer.cpp
#	src/plugin_manager.cpp
#	src/gui/web/server.cpp
#	src/gui/web/connection_manager.cpp
#	src/gui/web/static_request_handler.cpp
#	src/gui/web/notfound_request_handler.cpp
#	src/gui/web/plugin_request_handler.cpp
#	src/gui/web/request.cpp
#	src/gui/web/request_parser.cpp
#	src/gui/web/connection.cpp
#	src/gui/web/reply.cpp
#	src/gui/web/mime_types.cpp
#)

#target_compile_features(ZapSharer PRIVATE cxx_range_for)
#target_link_libraries(ZapSharer
#	${Boost_SYSTEM_LIBRARY}
#	${Jsoncpp_LIBRARY}
#	pthread
#)

