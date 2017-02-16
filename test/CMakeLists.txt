enable_testing()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories (${Boost_INCLUDE_DIRS} "../src" )
include(CodeCoverage)

file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test*.cpp)

add_executable(ZAP_SHARER_TEST ${TEST_SRCS})
	
target_link_libraries(ZAP_SHARER_TEST
    ZapSharerCore
	gui_web
    edonkey_plugin
	${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    ${Boost_LOG_LIBRARY}
	${Jsoncpp_LIBRARY}
    ${SQLITE3_LIBRARY}
	gcov
    pthread
)

set_target_properties(ZAP_SHARER_TEST PROPERTIES RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/testBin)
add_test(NAME ZAP_SHARER_TEST 
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin 
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/testBin/${testName} )

setup_target_for_coverage(ZAP_SHARER_coverage ZAP_SHARER_TEST coverage)
