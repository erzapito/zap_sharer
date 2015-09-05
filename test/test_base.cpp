//Link to Boost
 #define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
 #define BOOST_TEST_MODULE "BaseClassModule"

//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

#include "test_plugin_manager.cpp"
#include "test_mime_types.cpp"
#include "test_request.cpp"
