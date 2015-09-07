#Setup CMake to run tests
enable_testing()

#Prep ourselves for compiling boost
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories (${Boost_INCLUDE_DIRS} "../src" )
include(CodeCoverage)

#I like to keep test files in a separate source directory called test
file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test*.cpp)

#Run through each source
#foreach(testSrc ${TEST_SRCS})
        #Extract the filename without an extension (NAME_WE)
        #get_filename_component(testName ${testSrc} NAME_WE)

        #Add compile target
        add_executable(ZAP_SHARER_TEST ${TEST_SRCS})
		target_compile_features(ZAP_SHARER_TEST PRIVATE cxx_range_for)

        #link to Boost libraries AND your targets and dependencies
        target_link_libraries(ZAP_SHARER_TEST
			ZapSharerCore
			gui_web
                        edonkey_plugin
			${Boost_LIBRARIES}
			${Boost_SYSTEM_LIBRARY}
			${Jsoncpp_LIBRARY}
			pthread
			gcov
		)

        #I like to move testing binaries into a testBin directory
        set_target_properties(ZAP_SHARER_TEST PROPERTIES 
            RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/testBin)

        #Finally add it to test execution - 
        #Notice the WORKING_DIRECTORY and COMMAND
        add_test(NAME ZAP_SHARER_TEST 
                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin 
                 COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/testBin/${testName} )

		setup_target_for_coverage(ZAP_SHARER_coverage ZAP_SHARER_TEST coverage)

#endforeach(testSrc)
