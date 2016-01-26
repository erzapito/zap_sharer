#include "gui/web/static_request_handler.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

//#define TEST_LOG(x)  BOOST_LOG_TRIVIAL(debug)<<(x)<<std::endl
#define TEST_LOG(x)

using namespace zap::sharer::gui::web;

BOOST_AUTO_TEST_CASE( static_request_handler__constructor ) {
  TEST_LOG("::static_request_handler__constructor");
 static_request_handler * h;
 h = new static_request_handler("extra_test");
 delete h;
}

BOOST_AUTO_TEST_CASE( static_request_handler__handle_request__security__empty ) {
  TEST_LOG("::static_request_handler__handle_request__security__empty");
  static_request_handler h ("extra_test");
  request r("GET","HTTP 1.1","","",0);
  reply _r;
  bool result = h.handle_request(r,_r);
  BOOST_CHECK(result);
  BOOST_CHECK_EQUAL(404,_r.status);
  BOOST_CHECK(_r.content.empty());
}

BOOST_AUTO_TEST_CASE( static_request_handler__handle_request__security__dots ) {
  TEST_LOG("::static_request_handler__handle_request__security__dots");
  static_request_handler h ("extra_test");
  request r("GET","HTTP 1.1","/../","",0);
  reply _r;
  bool result = h.handle_request(r,_r);
  BOOST_CHECK(result);
  BOOST_CHECK_EQUAL(404,_r.status);
  BOOST_CHECK(_r.content.empty());
}

BOOST_AUTO_TEST_CASE( static_request_handler__handle_request__not_found ) {
  TEST_LOG("::static_request_handler__handle_request__not_found");
  static_request_handler h ("extra_test");
  request r("GET","HTTP 1.1","/file.png","",0);
  reply _r;
  bool result = h.handle_request(r,_r);
  BOOST_CHECK(!result);
}

BOOST_AUTO_TEST_CASE( static_request_handler__handle_request__index ) {
  TEST_LOG("::static_request_handler__handle_request__index");
  static_request_handler h ("extra_test");
  request r("GET","HTTP 1.1","/","",0);
  reply _r;
  bool result = h.handle_request(r,_r);
  BOOST_CHECK(result);
  BOOST_CHECK_EQUAL(200,_r.status);
  BOOST_CHECK_EQUAL("hello\n",_r.content);
}
