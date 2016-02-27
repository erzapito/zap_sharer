#include "gui/web/notfound_request_handler.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace zap::sharer::gui::web;

#define DISABLE_TEST_LOG
#include "test_commons.hpp"

BOOST_AUTO_TEST_CASE( notfound_request_handler_constructor ) {
 TEST_LOG("::notfound_request_handler_constructor");
 notfound_request_handler * h;
 h = new notfound_request_handler();
 delete h;
}

BOOST_AUTO_TEST_CASE( notfound_request_handler_handle_request ) {
  TEST_LOG("::notfound_request_handler_handle_request");
  notfound_request_handler h;
  request r("GET","HTTP 1.1","/con/act/id?name=st%C3%A5le&car=sa+ab","",0);
  reply _r;
  h.handle_request(r,_r);
  BOOST_CHECK_EQUAL(404,_r.status);
  BOOST_CHECK(_r.content.empty());
}
