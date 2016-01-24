#pragma once

#include "db_wrapper.hpp"
#include <sqlite3.h>
#include <vector>
#include <string>
#include <map>

namespace zap {
    namespace sharer {

class db_cursor_sqlite3: public db_cursor {
	public:
		db_cursor_sqlite3(sqlite3 * db, sqlite3_stmt *stmt);
		virtual ~db_cursor_sqlite3();

		// query
		virtual bool next();
		virtual const char * getStringColumn(int c);
		virtual int getIntColumn(int c);
		// insert
		virtual int execute();
		virtual void bind(int pos, const char * v);
		virtual void bind(int pos, int v);
	private:
		sqlite3_stmt *stmt;
		sqlite3 * db;
};

class db_wrapper_sqlite3: public db_wrapper {
    public:
        db_wrapper_sqlite3(const char * name);
        db_wrapper_sqlite3(const db_wrapper_sqlite3 & d);
        db_wrapper_sqlite3 & operator= (const db_wrapper_sqlite3 & db);
        ~db_wrapper_sqlite3();
        
        std::vector<std::string> listTables();
        std::map<std::string, std::string> listTableFields(const char * table);
        //void execute (const char * sql);
        db_cursor * query(const char * sql);
private:
    sqlite3 * db;
};

    }
}
