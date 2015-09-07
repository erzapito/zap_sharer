#include "edonkey/edonkey_plugin.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace zap::sharer::edonkey;

BOOST_AUTO_TEST_CASE( edonkey_plugin__base ) {
    auto * p = new edonkey_plugin();
    BOOST_CHECK_EQUAL("edonkey", p->getName());
    std::vector<std::string> & actions = p->listActions();
    BOOST_CHECK_EQUAL(0, actions.size());
    delete p;
}
