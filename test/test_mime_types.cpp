#include "gui/web/mime_types.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace zap::sharer::gui::web;

#define TEST_LOG(x)

BOOST_AUTO_TEST_CASE( mime_types_extension_to_type )
{
  BOOST_CHECK_EQUAL("image/gif",mime_types::extension_to_type("gif"));
  BOOST_CHECK_EQUAL("image/jpeg",mime_types::extension_to_type("jpg"));
  BOOST_CHECK_EQUAL("image/png",mime_types::extension_to_type("png"));
  BOOST_CHECK_EQUAL("text/html",mime_types::extension_to_type("html"));
  BOOST_CHECK_EQUAL("text/html",mime_types::extension_to_type("htm"));
  BOOST_CHECK_EQUAL("text/plain",mime_types::extension_to_type("XXX"));
}
