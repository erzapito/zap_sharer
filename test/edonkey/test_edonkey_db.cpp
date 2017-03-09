#include "edonkey/edonkey_db.hpp"
#include "db_wrapper_sqlite3.hpp"

#define DISABLE_TEST_LOG
#include "test_commons.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace zap::sharer::edonkey;

BOOST_AUTO_TEST_CASE( edonkey_db__base ) {
  TEST_LOG("::edonkey_db__base");
    std::shared_ptr<zap::sharer::db_wrapper_sqlite3> db(new zap::sharer::db_wrapper_sqlite3 (":memory:"));
    auto * p = new edonkey_db(db);
    delete p;
}

void checkEdonkeyDBTables(const std::shared_ptr<zap::sharer::db_wrapper_sqlite3> & db_w) {
    std::vector<std::string> names = db_w->listTables();

    BOOST_CHECK_EQUAL(3, names.size());
    BOOST_CHECK_EQUAL("edonkey_option", names[0].c_str());
    BOOST_CHECK_EQUAL("edonkey_server", names[2].c_str());
    {
        std::map<std::string, std::string> fields = db_w->listTableFields("edonkey_option");
        BOOST_CHECK_EQUAL(3, fields.size());
        BOOST_CHECK_EQUAL("INTEGER", fields["id"]);
        BOOST_CHECK_EQUAL("VARCHAR(255)", fields["name"]);
        BOOST_CHECK_EQUAL("VARCHAR(255)", fields["value"]);
    }
    {
        std::map<std::string, std::string> fields = db_w->listTableFields("edonkey_server");
        BOOST_CHECK_EQUAL(5, fields.size());
        BOOST_CHECK_EQUAL("INTEGER", fields["id"]);
        BOOST_CHECK_EQUAL("VARCHAR(255)", fields["name"]);
        BOOST_CHECK_EQUAL("VARCHAR(255)", fields["description"]);
        BOOST_CHECK_EQUAL("INT", fields["ip"]);
        BOOST_CHECK_EQUAL("INT", fields["port"]);
    }
}

BOOST_AUTO_TEST_CASE( edonkey_db__init_v1 ) {
    TEST_LOG("::edonkey_db__init_v1");
    std::shared_ptr<zap::sharer::db_wrapper_sqlite3> db_w(new zap::sharer::db_wrapper_sqlite3 (":memory:"));
    edonkey_db db (db_w, 1);
    
    checkEdonkeyDBTables(db_w);
}

BOOST_AUTO_TEST_CASE( edonkey_db__init_v_unknown ) {
    TEST_LOG("::edonkey_db__init_v_unknown");
    std::shared_ptr<zap::sharer::db_wrapper_sqlite3> db_w(new zap::sharer::db_wrapper_sqlite3 (":memory:"));
    try {
      edonkey_db db (db_w, 9999);
      BOOST_FAIL("Should fail on unknown database");
    } catch (std::runtime_error & e) {
	// PASSED
    }
    std::vector<std::string> names = db_w->listTables();
    BOOST_CHECK_EQUAL(0, names.size());
}

BOOST_AUTO_TEST_CASE( edonkey_db__test_delete ) {
    TEST_LOG("::edonkey_db_test_delete");
    std::shared_ptr<zap::sharer::db_wrapper_sqlite3> db_w(new zap::sharer::db_wrapper_sqlite3 (":memory:"));

    std::vector<std::string> names = db_w->listTables();
    BOOST_CHECK_EQUAL(0, names.size());

    edonkey_db db (db_w, 1);
    db.deleteCurrentTables();
    names = db_w->listTables();
    BOOST_CHECK_EQUAL(1, names.size());
}

BOOST_AUTO_TEST_CASE( edonkey_db__get_current_version ) {
    TEST_LOG("::edonkey_db__get_current_version");
    std::shared_ptr<zap::sharer::db_wrapper_sqlite3> db_w(new zap::sharer::db_wrapper_sqlite3 (":memory:"));
    auto * p = new edonkey_db(db_w);
	BOOST_CHECK_EQUAL(1, p->getCurrentVersion());
    delete p;
}

