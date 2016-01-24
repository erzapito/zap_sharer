#include "db_wrapper_sqlite3.hpp"

#include <stdio.h>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <sstream>

using namespace boost::log::trivial;

static boost::log::sources::severity_logger< severity_level > _logger;

namespace zap {
    namespace sharer {

        db_wrapper_sqlite3::db_wrapper_sqlite3(const char* name) {
            char *zErrMsg = 0;
            int rc;

            rc = sqlite3_open(name, &db);
            if( rc ){
            	BOOST_LOG_SEV(_logger ,error) << "db_wrapper_sqlite3 open error: " << rc;
            }
        }
        
        db_wrapper_sqlite3::~db_wrapper_sqlite3() {
            sqlite3_close(db);
        }
        
        std::vector<std::string> db_wrapper_sqlite3::listTables() {
            std::vector<std::string> result;
            
            int rc;
            sqlite3_stmt *stmt;
            rc = sqlite3_prepare_v2(db, "SELECT name FROM sqlite_master WHERE type='table'", -1, &stmt, NULL);
            if (rc != SQLITE_OK) {
                BOOST_LOG_SEV(_logger,error) << "db_wrapper_sqlite3::listTables error: " << sqlite3_errmsg(db);
            } else {
                while (sqlite3_step(stmt) == SQLITE_ROW) {
                    const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                    result.push_back(name);
                }
            }
            sqlite3_finalize(stmt);
            
            return result;
        }
        
        std::map<std::string,std::string> db_wrapper_sqlite3::listTableFields(const char* table) {
            std::map<std::string, std::string> result;
            
            int rc;
            sqlite3_stmt *stmt;

			std::string sql ("PRAGMA table_info(");
			sql += table;
			sql += ")";

            rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
            if (rc != SQLITE_OK) {
				std::stringstream msg;
				msg << "db_wrapper_sqlite3::listTableFields error: " << sqlite3_errmsg(db);
                BOOST_LOG_SEV(_logger,error) << msg.str();
				throw std::runtime_error(msg.str());
            } else {
                //sqlite3_bind_text(stmt, 1, table, -1, SQLITE_STATIC);
                while (sqlite3_step(stmt) == SQLITE_ROW) {
                    const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                    const char* type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
                    result[name] = type;
                }
            }
            sqlite3_finalize(stmt);
            return result;
        }

		db_cursor * db_wrapper_sqlite3::query(const char* sql) {
            int rc;
            sqlite3_stmt *stmt;
            rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
            if (rc != SQLITE_OK) {
				std::stringstream msg;
				msg << "db_wrapper_sqlite3::queryScalarInt prep error: " << sqlite3_errmsg(db);
                BOOST_LOG_SEV(_logger,error) << msg.str();
				throw std::runtime_error(msg.str());
            }
			return new db_cursor_sqlite3(db, stmt);
        }
        
		db_cursor_sqlite3::db_cursor_sqlite3 (sqlite3 * db, sqlite3_stmt * stmt): db(db), stmt(stmt) {};

		db_cursor_sqlite3::~db_cursor_sqlite3() {
			sqlite3_finalize (stmt);
		};

		bool db_cursor_sqlite3::next() {
			int rc = sqlite3_step(stmt);
			if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
				std::stringstream msg;
				msg << "db_cursor_sqlite3::next error:" << rc << ": " << sqlite3_errmsg(db);
				BOOST_LOG_SEV(_logger,error) << msg.str();
				throw std::runtime_error(msg.str());
			}
			return rc == SQLITE_ROW;
		}

		const char * db_cursor_sqlite3::getStringColumn(int c) {
			return reinterpret_cast<const char*>(sqlite3_column_text(stmt,c));
		}

		int db_cursor_sqlite3::getIntColumn(int c) {
			return sqlite3_column_int(stmt,c);
		}

		int db_cursor_sqlite3::execute() {
			sqlite3_step(stmt);
			return sqlite3_changes(db);
		};

		void db_cursor_sqlite3::bind(int pos, const char * v) {
			sqlite3_bind_text(stmt, pos + 1, v, -1, SQLITE_STATIC);
		};

		void db_cursor_sqlite3::bind(int pos, int v) {
			sqlite3_bind_int(stmt, pos + 1, v);
		};

    }
}
