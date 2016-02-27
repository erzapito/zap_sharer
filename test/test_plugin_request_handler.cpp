#include "gui/web/plugin_request_handler.hpp"

#define DISABLE_TEST_LOG
#include "test_commons.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace zap::sharer::gui::web;
using namespace zap::sharer;

class dummy_plugin: public plugin {
public:
    std::string name;
    std::vector<std::string> actions;
    dummy_plugin(const char * n, const char * a1 = NULL, const char * a2 = NULL):name(n) {
        if (a1)
            actions.push_back(a1);
        if (a2)
            actions.push_back(a2);
    }
    
    std::string & getName() {
        return name;
    }
    std::vector<std::string> & listActions() {
        return actions;
    }
};

BOOST_AUTO_TEST_CASE( plugin_request_handler__constructor ) {
  TEST_LOG("::plugin_request_handler__constructor");
    zap::sharer::plugin_manager m;
    
    plugin_request_handler * h;
    h = new plugin_request_handler(m);
    delete h;
}

BOOST_AUTO_TEST_CASE( plugin_request_handler__handle_request__not_match) {
  TEST_LOG("::plugin_request_handler__handle_request__not_match");
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

BOOST_AUTO_TEST_CASE( plugin_request_handler__handle_request__plugin_listing__empty) {
  TEST_LOG("::plugin_request_handler__handle_request__plugin_listing__empty");
    zap::sharer::plugin_manager m;
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

BOOST_AUTO_TEST_CASE( plugin_request_handler__handle_request__plugin_listing__non_empty) {
TEST_LOG("::plugin_request_handler__handle_request__plugin_listing__non_empty");
    plugin * p1 = new dummy_plugin("p1");
    plugin * p2 = new dummy_plugin("p2");
    
    zap::sharer::plugin_manager m;
    m.addPlugin(p1);
    m.addPlugin(p2);
    plugin_request_handler h (m);
    reply _r;
    bool res;
    request r("GET","HTTP 1.1","/plugins","",0);
    res = h.handle_request(r,_r);
    BOOST_CHECK(res);
    BOOST_CHECK_EQUAL(200,_r.status);
    BOOST_CHECK_EQUAL("[\"p2\",\"p1\"]",_r.content.c_str());
    BOOST_CHECK_EQUAL(2,_r.headers.size());
    BOOST_CHECK_EQUAL("Content-Length",_r.headers[0].name);
    BOOST_CHECK_EQUAL("11",_r.headers[0].value);
    BOOST_CHECK_EQUAL("Content-Type",_r.headers[1].name);
    BOOST_CHECK_EQUAL("application/json",_r.headers[1].value);
}

BOOST_AUTO_TEST_CASE( plugin_request_handler__handle_request__plugin_actions__not_found) {
TEST_LOG("::plugin_request_handler__handle_request__plugin_actions__not_found");
    plugin * p1 = new dummy_plugin("p1");
    plugin * p2 = new dummy_plugin("p2");
    
    zap::sharer::plugin_manager m;
    m.addPlugin(p1);
    m.addPlugin(p2);
    
    plugin_request_handler h (m);
    reply _r;
    bool res;
    request r("GET","HTTP 1.1","/plugins/p3","",0);
    res = h.handle_request(r,_r);
    BOOST_CHECK(res);
    BOOST_CHECK_EQUAL(404,_r.status);
}

BOOST_AUTO_TEST_CASE( plugin_request_handler__handle_request__plugin_actions__empty) {
TEST_LOG("::plugin_request_handler__handle_request__plugin_actions__empty");
    plugin * p1 = new dummy_plugin("p1");
    plugin * p2 = new dummy_plugin("p2");
    
    zap::sharer::plugin_manager m;
    m.addPlugin(p1);
    m.addPlugin(p2);
    
    plugin_request_handler h (m);
    reply _r;
    bool res;
    request r("GET","HTTP 1.1","/plugins/p1","",0);
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

BOOST_AUTO_TEST_CASE( plugin_request_handler__handle_request__plugin_actions__non_empty) {
TEST_LOG("::plugin_request_handler__handle_request__plugin_actions__non_empty");
    plugin * p1 = new dummy_plugin("p1","act1","act2");
    plugin * p2 = new dummy_plugin("p2");
    
    zap::sharer::plugin_manager m;
    m.addPlugin(p1);
    m.addPlugin(p2);
    
    plugin_request_handler h (m);
    reply _r;
    bool res;
    request r("GET","HTTP 1.1","/plugins/p1","",0);
    res = h.handle_request(r,_r);
    BOOST_CHECK(res);
    BOOST_CHECK_EQUAL(200,_r.status);
    BOOST_CHECK_EQUAL("[\"act2\",\"act1\"]",_r.content.c_str());
    BOOST_CHECK_EQUAL(2,_r.headers.size());
    BOOST_CHECK_EQUAL("Content-Length",_r.headers[0].name);
    BOOST_CHECK_EQUAL("15",_r.headers[0].value);
    BOOST_CHECK_EQUAL("Content-Type",_r.headers[1].name);
    BOOST_CHECK_EQUAL("application/json",_r.headers[1].value);
}

BOOST_AUTO_TEST_CASE( plugin_request_handler__handle_request__wrong_request) {
TEST_LOG("::plugin_request_handler__handle_request__wrong_request");
    plugin * p1 = new dummy_plugin("p1","act1","act2");
    plugin * p2 = new dummy_plugin("p2");
    
    zap::sharer::plugin_manager m;
    m.addPlugin(p1);
    m.addPlugin(p2);
    
    plugin_request_handler h (m);
    reply _r;
    bool res;
    request r("GET","HTTP 1.1","/plugins/p1/p","",0);
    res = h.handle_request(r,_r);
    BOOST_CHECK(res);
    BOOST_CHECK_EQUAL(500,_r.status);
}
