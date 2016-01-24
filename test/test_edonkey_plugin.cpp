#include "edonkey/edonkey_plugin.hpp"
#include "db_wrapper_sqlite3.hpp"
#include "test_commons.hpp"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace zap::sharer::edonkey;



BOOST_AUTO_TEST_CASE( edonkey_plugin__base ) {

	boost::log::core::get()->set_filter (
	    boost::log::trivial::severity >= boost::log::trivial::fatal
	);

  TEST_LOG("::edonkey_plugin__base");
    zap::sharer::db_wrapper_sqlite3 db (":memory:");
    auto * p = new edonkey_plugin(&db);
    BOOST_CHECK_EQUAL("edonkey", p->getName());
    std::vector<std::string> & actions = p->listActions();
    BOOST_CHECK_EQUAL(0, actions.size());
    delete p;


	boost::log::core::get()->set_filter (
	    boost::log::trivial::severity >= boost::log::trivial::trace
	);

}

BOOST_AUTO_TEST_CASE( edonkey_plugin__load_servers_met ) {
	TEST_LOG("::edonkey_plugin__load_servers_met");
    zap::sharer::db_wrapper_sqlite3 db (":memory:");
	TEST_LOG("-> first load");
    auto * p = new edonkey_plugin(&db);
    p->loadServerMet("file:resources/server.met");
    {
        const std::vector<server_info> & servers = p->listServers();
        BOOST_CHECK_EQUAL(10, servers.size());
        BOOST_CHECK_EQUAL(1999292507, servers[0].ip);
        BOOST_CHECK_EQUAL(9939, servers[0].port);
        BOOST_CHECK_EQUAL("eMule Security No3", servers[0].name);
        BOOST_CHECK_EQUAL(607152048, servers[9].ip);
        BOOST_CHECK_EQUAL(4184, servers[9].port);
        BOOST_CHECK_EQUAL("TV Underground", servers[9].name);
    }
    delete p;
    
    // check servers are kept
	TEST_LOG("-> second load");
    p = new edonkey_plugin(&db);
    {
        const std::vector<server_info> & servers = p->listServers();
        BOOST_CHECK_EQUAL(10, servers.size());
        BOOST_CHECK_EQUAL(1999292507, servers[0].ip);
        BOOST_CHECK_EQUAL(9939, servers[0].port);
        BOOST_CHECK_EQUAL("eMule Security No3", servers[0].name);
        BOOST_CHECK_EQUAL(607152048, servers[9].ip);
        BOOST_CHECK_EQUAL(4184, servers[9].port);
        BOOST_CHECK_EQUAL("TV Underground", servers[9].name);
    }
    delete p;
}

BOOST_AUTO_TEST_CASE( edonkey_plugin__load_servers_met__duplicate_server ) {
  TEST_LOG("::edonkey_plugin__load_servers_met__duplicate_server");
    BOOST_FAIL("NOT IMPLEMENTED");
}

BOOST_AUTO_TEST_CASE( edonkey_plugin__load_servers_met__update_server ) {
  TEST_LOG("::edonkey_plugin__load_servers_met__update_server");
    BOOST_FAIL("NOT IMPLEMENTED");
}

BOOST_AUTO_TEST_CASE( edonkey_plugin__load_servers_met__not_existing ) {
  TEST_LOG("::edonkey_plugin__load_servers_met__not_existing");
    zap::sharer::db_wrapper_sqlite3 db (":memory:");
    auto * p = new edonkey_plugin(&db);
    p->loadServerMet("file://resources/server.met2");
    const std::vector<server_info> & servers = p->listServers();
    BOOST_CHECK_EQUAL(0, servers.size());
    delete p;
}

BOOST_AUTO_TEST_CASE( edonkey_plugin__load_servers_met__not_valid ) {
  TEST_LOG("::edonkey_plugin__load_servers_met__not_valid");
    zap::sharer::db_wrapper_sqlite3 db (":memory:");
    auto * p = new edonkey_plugin(&db);
    p->loadServerMet("file://resources/server.met.bad");
    const std::vector<server_info> & servers = p->listServers();
    BOOST_CHECK_EQUAL(0, servers.size());
    delete p;
}
