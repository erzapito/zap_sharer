#include "gui/web/plugin_request_handler.hpp"

using namespace zap::sharer::gui::web;
using namespace zap::sharer;

BOOST_AUTO_TEST_CASE( plugin_request_handler__constructor ) {
    
    plugin_manager m;
    
    plugin_request_handler * h;
    h = new plugin_request_handler(m);
    delete h;
}

BOOST_AUTO_TEST_CASE( plugin_request_handler__handle_request__not_match) {
    plugin_manager m;
    plugin_request_handler h (m);
    reply _r;
    bool res;
    request r("GET","HTTP 1.1","","",0);
    res = h.handle_request(r,_r);
    BOOST_CHECK(!res);
    request r2("GET","HTTP 1.1","/test/","",0);
    res = h.handle_request(r2,_r);
    BOOST_CHECK(!res);
}

BOOST_AUTO_TEST_CASE( plugin_request_handler__handle_request__plugin_listing) {
    plugin_manager m;
    plugin_request_handler h (m);
    reply _r;
    bool res;
    request r("GET","HTTP 1.1","/plugins","",0);
    res = h.handle_request(r,_r);
    BOOST_CHECK(res);
    BOOST_CHECK_EQUAL(200,_r.status);
    BOOST_CHECK_EQUAL("[]",_r.content.c_str());
    BOOST_CHECK_EQUAL(2,_r.headers.size());
    BOOST_CHECK_EQUAL("Content-Length",_r.headers[0].name);
    BOOST_CHECK_EQUAL("2",_r.headers[0].value);
    BOOST_CHECK_EQUAL("Content-Type",_r.headers[1].name);
    BOOST_CHECK_EQUAL("application/json",_r.headers[1].value);
}
