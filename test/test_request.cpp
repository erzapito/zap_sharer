#include "gui/web/request.hpp"

using namespace zap::sharer::gui::web;

BOOST_AUTO_TEST_CASE( request_decodeUri ) {
  request r("GET","HTTP 1.1","/con/act/id?name=st%C3%A5le&car=sa+ab","",0);
  BOOST_CHECK_EQUAL(true,r.isValid());
  BOOST_CHECK_EQUAL(3,r.getSegments().size());
  BOOST_CHECK_EQUAL("/con/act/id?name=ståle&car=sa ab",r.getRequestPath());
  BOOST_CHECK_EQUAL("con",r.getSegments()[0]);
  BOOST_CHECK_EQUAL("act",r.getSegments()[1]);
  BOOST_CHECK_EQUAL("id?name=ståle&car=sa ab",r.getSegments()[2]);

  request r2("GET","HTTP 1.1","/con/act/id?name=st%C31%","",0);
  BOOST_CHECK_EQUAL(false,r2.isValid());
  BOOST_CHECK_EQUAL(0,r2.getSegments().size());
  BOOST_CHECK_EQUAL("",r2.getRequestPath());

  request r3("GET","HTTP 1.1","/con/act/id?name=st%C32%XX","",0);
  BOOST_CHECK_EQUAL(false,r3.isValid());
  BOOST_CHECK_EQUAL(0,r3.getSegments().size());
  BOOST_CHECK_EQUAL("",r3.getRequestPath());
}
