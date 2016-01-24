#include "ZapSharer.hpp"
#include "plugin_manager.hpp"
#define DISABLE_TEST_LOG
#include "test_commons.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

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
    
    virtual std::string & getName() {
        return name;
    }
    virtual std::vector<std::string> & listActions() {
        return actions;
    }
};

BOOST_AUTO_TEST_CASE( plugin_manager__constructors )
{
  TEST_LOG("::plugin_manager__constructors");
  plugin_manager * manager = new plugin_manager();
  delete manager;
}

BOOST_AUTO_TEST_CASE( plugin_manager__getPluginByShortName__empty )
{
  TEST_LOG("::plugin_manager__getPluginByShortName__empty");
  zap::sharer::plugin_manager manager;
  zap::sharer::plugin * p = manager.getPluginByShortName("test");
  BOOST_CHECK_MESSAGE(p == NULL, "plugin should be null");
}

BOOST_AUTO_TEST_CASE( plugin_manager__listPluginNames__empty )
{
  TEST_LOG("::plugin_manager__listPluginNames__empty");
  zap::sharer::plugin_manager manager;
  auto & names = manager.listPluginNames();
  BOOST_CHECK_MESSAGE(names.empty(), "plugin should be null");
}

BOOST_AUTO_TEST_CASE( plugin_manager__listPluginNames__non_empty )
{
  TEST_LOG("::plugin_manager__listPluginNames__non_empty");
    plugin * p1 = new dummy_plugin("p1");
    plugin * p2 = new dummy_plugin("p2");
    
    zap::sharer::plugin_manager manager;
    manager.addPlugin(p1);
    manager.addPlugin(p2);
    auto & names = manager.listPluginNames();
    BOOST_CHECK_EQUAL(2, names.size());
    BOOST_CHECK_EQUAL("p1",names[0]);
    BOOST_CHECK_EQUAL("p2",names[1]);
}

BOOST_AUTO_TEST_CASE( plugin_manager__getPluginByShortName__non_empty )
{
  TEST_LOG("::plugin_manager__getPluginByShortName__non_empty");
    plugin * p1 = new dummy_plugin("p1");
    plugin * p2 = new dummy_plugin("p2");
    
    zap::sharer::plugin_manager manager;
    manager.addPlugin(p1);
    manager.addPlugin(p2);
    
    zap::sharer::plugin * p = manager.getPluginByShortName("test");
    BOOST_CHECK_MESSAGE(p == NULL, "plugin should be null");
    BOOST_CHECK(p1 == manager.getPluginByShortName("p1"));
    BOOST_CHECK(p2 != manager.getPluginByShortName("p1"));
    BOOST_CHECK(p2 == manager.getPluginByShortName("p2"));
    BOOST_CHECK(NULL == manager.getPluginByShortName("p3"));
}
