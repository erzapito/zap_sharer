#include "db_wrapper_sqlite3.hpp"
#define DISABLE_TEST_LOG
#include "test_commons.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


using namespace zap::sharer;

BOOST_AUTO_TEST_CASE( db_wrapper_sqlite3__base ) {
	TEST_LOG("::db_wrapper_sqlite3__base");
    db_wrapper_sqlite3 * db = new db_wrapper_sqlite3(":memory:");
    delete db;
}

BOOST_AUTO_TEST_CASE( db_wrapper_sqlite3__01 ) {
	TEST_LOG("::db_wrapper_sqlite3__01");
    db_wrapper_sqlite3 * db = new db_wrapper_sqlite3(":memory:");
    db->execute("CREATE TABLE t1( id INTEGER PRIMARY KEY, field1 VARCHAR(55))");    
    delete db;
}

BOOST_AUTO_TEST_CASE( db_wrapper_sqlite3__1 ) {
	TEST_LOG("::db_wrapper_sqlite3__1");
    db_wrapper_sqlite3 * db = new db_wrapper_sqlite3(":memory:");
    db->execute("CREATE TABLE t1( id INTEGER PRIMARY KEY, field1 VARCHAR(55))");
    db->execute("CREATE TABLE t2( id INTEGER PRIMARY KEY, field2 VARCHAR(65))");
    
    std::vector<std::string> tables = db->listTables();
    BOOST_CHECK_EQUAL(2,tables.size());
    BOOST_CHECK_EQUAL("t1",tables[0].c_str());
    BOOST_CHECK_EQUAL("t2",tables[1].c_str());
    std::map<std::string,std::string> fields = db->listTableFields("t1");
    BOOST_CHECK_EQUAL(2, fields.size());
    BOOST_CHECK_EQUAL("INTEGER", fields["id"]);
    BOOST_CHECK_EQUAL("VARCHAR(55)", fields["field1"]);
    
    
    delete db;
}
