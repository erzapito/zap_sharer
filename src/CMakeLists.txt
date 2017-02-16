cmake_minimum_required (VERSION 3.0)

add_library(gui_web
	gui/web/server.cpp
	gui/web/static_request_handler.cpp
	gui/web/notfound_request_handler.cpp
	gui/web/plugin_request_handler.cpp
	gui/web/request.cpp
	gui/web/mime_types.cpp
)

add_library(edonkey_plugin
    edonkey/edonkey_plugin.cpp
    edonkey/server_info.cpp
    edonkey/edonkey_db.cpp
)

add_library(ZapSharerCore
    ZapSharer.cpp
    plugin_manager.cpp
    db_wrapper_sqlite3.cpp
)

add_executable(ZapSharer 
	main.cpp
)

target_link_libraries(gui_web
    ${Jsoncpp_LIBRARY}
    ${MHD_LIBRARIES}
)

target_link_libraries(ZapSharerCore
    ${SQLITE3_LIBRARY}
)

target_link_libraries(ZapSharer
    ZapSharerCore
    gui_web
    edonkey_plugin
    ${Boost_LIBRARIES}
    ${Boost_LOG_LIBRARY}
    pthread
 )

