add_library(gui_web
	gui/web/server.cpp
	gui/web/connection_manager.cpp
	gui/web/static_request_handler.cpp
	gui/web/notfound_request_handler.cpp
	gui/web/plugin_request_handler.cpp
	gui/web/request.cpp
	gui/web/request_parser.cpp
	gui/web/connection.cpp
	gui/web/reply.cpp
	gui/web/mime_types.cpp
)

add_library(ZapSharerCore
    ZapSharer.cpp
    plugin_manager.cpp
)

add_executable(ZapSharer 
	main.cpp
)

target_compile_features(gui_web PRIVATE cxx_range_for)
target_compile_features(ZapSharerCore PRIVATE cxx_range_for)
target_compile_features(ZapSharer PRIVATE cxx_range_for)
target_link_libraries(ZapSharer
	ZapSharerCore
	gui_web
	${Boost_SYSTEM_LIBRARY}
	${Jsoncpp_LIBRARY}
	pthread
    gcov
)

