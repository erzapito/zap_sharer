#include "edonkey/edonkey_db.hpp"
#include "db_wrapper_sqlite3.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

//#define TEST_LOG(x)  BOOST_LOG_TRIVIAL(debug)<<(x)<<std::endl
#define TEST_LOG(x)

using namespace zap::sharer::edonkey;

BOOST_AUTO_TEST_CASE( edonkey_db__base ) {
  TEST_LOG("::edonkey_db__base");
    zap::sharer::db_wrapper_sqlite3 db (":memory:");
    auto * p = new edonkey_db(&db);
    delete p;
}

BOOST_AUTO_TEST_CASE( edonkey_db__init_v1 ) {
  TEST_LOG("::edonkey_db__init_v1");
    zap::sharer::db_wrapper_sqlite3 db_w (":memory:");
    edonkey_db db (&db_w, 1);
    
    std::vector<std::string> names = db_w.listTables();
    
    BOOST_CHECK_EQUAL(3, names.size());
	BOOST_CHECK_EQUAL("edonkey_option", names[0].c_str());
	BOOST_CHECK_EQUAL("edonkey_server", names[2].c_str());
    {
        std::map<std::string, std::string> fields = db_w.listTableFields("edonkey_option");
        BOOST_CHECK_EQUAL(3, fields.size());
        BOOST_CHECK_EQUAL("INTEGER", fields["id"]);
        BOOST_CHECK_EQUAL("VARCHAR(255)", fields["name"]);
        BOOST_CHECK_EQUAL("VARCHAR(255)", fields["description"]);
    }
    {
        std::map<std::string, std::string> fields = db_w.listTableFields("edonkey_server");
        BOOST_CHECK_EQUAL(3, fields.size());
        BOOST_CHECK_EQUAL("pk", fields["id"]);
        BOOST_CHECK_EQUAL("VARCHAR(255)", fields["name"]);
        BOOST_CHECK_EQUAL("VARCHAR(255)", fields["description"]);
    }
}

BOOST_AUTO_TEST_CASE( edonkey_db__get_current_version ) {
  TEST_LOG("::edonkey_db__get_current_version");
    BOOST_FAIL("NOT IMPLEMENTED");
}

BOOST_AUTO_TEST_CASE( edonkey_db__update__from_v0 ) {
  TEST_LOG("::edonkey_db__update__from_v0");
    BOOST_FAIL("NOT IMPLEMENTED");
}

BOOST_AUTO_TEST_CASE( edonkey_db__update__from_v1 ) {
  TEST_LOG("::edonkey_db__update__from_v1");
    BOOST_FAIL("NOT IMPLEMENTED");
}
