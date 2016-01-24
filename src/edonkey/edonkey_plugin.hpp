#pragma once

#include "../plugin.hpp"
#include "../db_wrapper.hpp"
#include "server_info.hpp"
#include "edonkey_db.hpp"

namespace zap {
namespace sharer {
namespace edonkey {  


class edonkey_plugin : public zap::sharer::plugin {
public:
    edonkey_plugin(zap::sharer::db_wrapper * _db);
    edonkey_plugin(const edonkey_plugin & p);
    edonkey_plugin& operator=(const edonkey_plugin&) = delete;
    virtual ~edonkey_plugin();
    
    std::string & getName();
    std::vector<std::string> & listActions();
    
    void loadServerMet(const char * serverMetUrl);
    const std::vector<server_info> & listServers() const;
    
    void addServer(server_info & info);
    
private:
    std::string name;
    std::vector<std::string> actions;
    std::vector<server_info> servers;
    
    edonkey_db db;

};

}
}
}
