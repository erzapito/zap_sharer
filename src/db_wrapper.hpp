#pragma once

#include <string>
#include <map>
#include <vector>
#include <initializer_list>
#include <memory>

namespace zap {
    namespace sharer {
        
        class db_cursor {
public:
			virtual ~db_cursor() {};
			// query
			virtual bool next() = 0;
			virtual std::string getStringColumn(int c) = 0;
			virtual int getIntColumn(int c) = 0;

			// insert
			virtual int execute() = 0;
			virtual void bind(int pos, const std::string & v) = 0;
			virtual void bind(int pos, int v) = 0;
        };
        
        class db_wrapper {
public:
			virtual std::vector<std::string> listTables() = 0;
			virtual std::map<std::string, std::string> listTableFields(const std::string & table) = 0;
			virtual std::unique_ptr<db_cursor> query(const std::string & sql) = 0;
			
			void execute(const std::string & sql){
				auto cursor = query(sql);
				cursor->execute();
			}
};
        
    }
}
