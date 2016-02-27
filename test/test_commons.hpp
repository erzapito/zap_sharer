#pragma once
  
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

#ifdef DISABLE_TEST_LOG
 #define TEST_LOG(x)
#else
 #define TEST_LOG(x) BOOST_LOG_TRIVIAL(debug)<<(x)<<std::endl
#endif

