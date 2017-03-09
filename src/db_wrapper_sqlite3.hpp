#pragma once

#include "db_wrapper.hpp"
#include <sqlite3.h>
#include <vector>
#include <string>
#include <map>
#include <memory>

namespace zap {
namespace sharer {

class db_cursor_sqlite3: public db_cursor {

public:
    db_cursor_sqlite3(sqlite3 * db, sqlite3_stmt *stmt);
    virtual ~db_cursor_sqlite3();

    // query
    virtual bool next() override;
    virtual std::string getStringColumn(int c) override;
    virtual int getIntColumn(int c) override;
    // insert
    virtual int execute() override;
    virtual void bind(int pos, const std::string & v) override;
    virtual void bind(int pos, int v) override;

private:
    sqlite3 * db;
    sqlite3_stmt * stmt;
};

class db_wrapper_sqlite3: public db_wrapper {

public:
    db_wrapper_sqlite3(const std::string & name);
    db_wrapper_sqlite3(const db_wrapper_sqlite3 & d);
    db_wrapper_sqlite3 & operator= (const db_wrapper_sqlite3 & db);
    virtual ~db_wrapper_sqlite3();
        
    std::vector<std::string> listTables() override;
    std::map<std::string, std::string> listTableFields(const std::string & table) override;
    std::unique_ptr<db_cursor> query(const std::string & sql) override;

private:
    sqlite3 * db;

  
};

}
}
