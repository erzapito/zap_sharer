#pragma once

#include "../db_wrapper.hpp"
#include "server_info.hpp"

namespace zap {
    namespace sharer {
        namespace edonkey {
	
	    class edonkey_db {
	    public:
	        static const int VERSION = 1;
		edonkey_db(std::shared_ptr<zap::sharer::db_wrapper> db);
		edonkey_db(std::shared_ptr<zap::sharer::db_wrapper> db, const int version);
		edonkey_db(const edonkey_db & d);
		edonkey_db & operator= (const edonkey_db & d);
		~edonkey_db();
		
		void deleteCurrentTables();

		void addServerInfo(const server_info &i);
		void updateServerInfo(const server_info &i);
		void loadServerList(std::vector<server_info> & l);
		int getCurrentVersion();
		
	    private:
		std::shared_ptr<zap::sharer::db_wrapper> db;
			
		void init(int v);
		void initV1();
		void update(int from, int to);
	    };           
        }
    }
}
