#include "ZapSharer.hpp"
#include "plugin_manager.hpp"

// ------------- Tests Follow --------------
BOOST_AUTO_TEST_CASE( plugin_manager_constructors )
{
  zap::sharer::plugin_manager manager;
}

//Name your test cases for what they test
BOOST_AUTO_TEST_CASE( plugin_manager_getPluginByShortName_empty )
{
  zap::sharer::plugin_manager manager;
  zap::sharer::plugin * p = manager.getPluginByShortName("test");
  BOOST_CHECK_MESSAGE(p == NULL, "plugin should be null");
}

//Name your test cases for what they test
BOOST_AUTO_TEST_CASE( plugin_manager_listPluginNames_empty )
{
  zap::sharer::plugin_manager manager;
  auto & names = manager.listPluginNames();
  BOOST_CHECK_MESSAGE(names.empty(), "plugin should be null");
}
