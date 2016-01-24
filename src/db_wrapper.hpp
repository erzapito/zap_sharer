#pragma once

#include <string>
#include <map>
#include <vector>
#include <initializer_list>

namespace zap {
    namespace sharer {
        
        class db_cursor {
public:
			// query
            virtual bool next() = 0;
			virtual const char * getStringColumn(int c) = 0;
			virtual int getIntColumn(int c) = 0;

			// insert
			virtual int execute() = 0;
			virtual void bind(int pos, const char * v) = 0;
			virtual void bind(int pos, int v) = 0;

			void bind(int pos, const std::string & s) {
				bind(pos,s.c_str());
			}
        };
        
        class db_wrapper {
public:
			virtual std::vector<std::string> listTables() = 0;
			virtual std::map<std::string, std::string> listTableFields(const char * table) = 0;
  
			void execute(const char * sql){
				auto cursor = query(sql);
				cursor->execute();
				delete(cursor);
			}
			//virtual db_cursor * exe(const char * sql, const char * p1 = NULL, const char * p2 = NULL) = 0;
			virtual db_cursor * query(const char * sql) = 0;
};
        
    }
}
