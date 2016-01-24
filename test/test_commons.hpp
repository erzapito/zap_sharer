#pragma once

#include <boost/log/trivial.hpp>

#ifdef DISABLE_TEST_LOG
 #define TEST_LOG(x)
#else
 #define TEST_LOG(x) BOOST_LOG_TRIVIAL(debug)<<(x)<<std::endl
#endif
