#include "edonkey_db.hpp"
#include <algorithm>
#include <boost/log/trivial.hpp>
#include <iostream>

using namespace boost::log::trivial;

static boost::log::sources::severity_logger< severity_level > _logger;

namespace zap {
    namespace sharer {
        namespace edonkey {
            
            edonkey_db::edonkey_db(zap::sharer::db_wrapper * _db): db(_db) {
                int version = getCurrentVersion();
                if (version) {
                    update(version, edonkey_db::VERSION);
                } else {
                    init (edonkey_db::VERSION);
                }
            }
            
            edonkey_db::edonkey_db(zap::sharer::db_wrapper * _db, int version): db(_db) {
				
                int currentVersion = getCurrentVersion();
                /*
		 * As there is only version 1, this code is unreachable
		if (currentVersion && currentVersion != version) {
                    deleteCurrentTables();
                    init (version);
                } else */ if (!currentVersion) {
                    init (version);
                }
            }
            
            edonkey_db::~edonkey_db() {
                // nothing to do
            }
            
            int edonkey_db::getCurrentVersion() {
				int v = 0;
			    std::vector<std::string> tables = db->listTables();

				if(std::find(tables.begin(), tables.end(), "edonkey_option") != tables.end()) {
					auto result = db->query("SELECT value FROM edonkey_option WHERE name='db_version';");
					if (result->next()) {
						const char * versionStr = result->getStringColumn(0);
						v = atoi(versionStr);
					}
					delete result;
				}
				return v;
            }
         
			void edonkey_db::init(int v) {
				switch(v){
				case 1:
					initV1();
					break;
				default:
					std::string msg ("Unkwnown db version: ");
					msg += v;
					throw std::runtime_error(msg);
				};
			}

			void edonkey_db::deleteCurrentTables() {
				db->execute("DROP TABLE IF EXISTS edonkey_option");
				db->execute("DROP TABLE IF EXISTS edonkey_server");
			};

			void edonkey_db::initV1() {
				int rc;
				db->execute("CREATE TABLE edonkey_option (id INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR(255), value VARCHAR(255))");
				db->execute("CREATE TABLE edonkey_server (id INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR(255), description VARCHAR(255), ip INT, port INT)");
				auto cursor = db->query("INSERT INTO edonkey_option (name,value) VALUES (?,?)");
				cursor->bind(0,"db_version");
				cursor->bind(1,1);
				rc = cursor->execute();
				if (rc != 1) {
				    BOOST_LOG_SEV(_logger,error) << "Error inserting db_version #" << rc;
				}
			};

			void edonkey_db::update(int from, int to) {
				if (from == 0) {
					init(to);
				} else if (from == to) {
					// nothing to do
 				} else {
					throw std::runtime_error("Should not be updating the db");
				}
			}

	 		void edonkey_db::addServerInfo(const server_info &i) {
				auto cursor = db->query("INSERT INTO edonkey_server(name, description, ip, port) VALUES (?,?,?,?)");
				cursor->bind(0,i.name);
				cursor->bind(1,i.description);
				cursor->bind(2,i.ip);
				cursor->bind(3,i.port);
				cursor->execute();
				delete cursor;
			}

	 		void edonkey_db::updateServerInfo(const server_info &i) {
				auto cursor = db->query("UPDATE edonkey_server SET name=?, description=?, ip=?, port=? WHERE id=?");
				cursor->bind(0,i.name);
				cursor->bind(1,i.description);
				cursor->bind(2,i.ip);
				cursor->bind(3,i.port);
				cursor->bind(4,i.id);
				cursor->execute();
				delete cursor;
			}

	 		void edonkey_db::loadServerList(std::vector<server_info> & l) {
	 			auto cursor = db->query("SELECT id,name,description,ip,port from edonkey_server");
	 			while (cursor->next()) {
	 				int id = cursor->getIntColumn(0);
	 				const char * name = cursor->getStringColumn(1);
	 				const char * description = cursor->getStringColumn(2);
	 				int ip = cursor->getIntColumn(3);
	 				int port = cursor->getIntColumn(4);
	 				l.push_back(server_info(id,name,description,ip,port));
	 			}
	 			delete cursor;
	 		}

        }
    }
}
