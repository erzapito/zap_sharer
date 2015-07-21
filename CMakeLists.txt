cmake_minimum_required (VERSION 3.2)
project (ZapSharer)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Boost 1.32 REQUIRED COMPONENTS system)
find_package(Jsoncpp)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} ${Jsoncpp_INCLUDE_DIR} )

add_executable(ZapSharer 
	src/ZapSharer.cpp
	src/plugin_manager.cpp
	src/gui/web/server.cpp
	src/gui/web/connection_manager.cpp
	src/gui/web/static_request_handler.cpp
	src/gui/web/notfound_request_handler.cpp
	src/gui/web/plugin_request_handler.cpp
	src/gui/web/request.cpp
	src/gui/web/request_parser.cpp
	src/gui/web/connection.cpp
	src/gui/web/reply.cpp
	src/gui/web/mime_types.cpp
)

target_compile_features(ZapSharer PRIVATE cxx_range_for)
target_link_libraries(ZapSharer
	${Boost_SYSTEM_LIBRARY}
	${Jsoncpp_LIBRARY}
	pthread
)

