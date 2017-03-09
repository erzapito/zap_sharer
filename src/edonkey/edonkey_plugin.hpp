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
    edonkey_plugin(std::shared_ptr<zap::sharer::db_wrapper> _db);
    edonkey_plugin(const edonkey_plugin & p);
    edonkey_plugin& operator=(const edonkey_plugin&) = delete;
    virtual ~edonkey_plugin();
    
    const std::string & getName() override;
    const std::vector<std::string> & listActions() override;
    void executeAction(const std::string & action) override;
    
    void loadServerMet(const std::string & serverMetUrl);
    const std::vector<server_info> & listServers() const;
    
    void addServer(server_info & info);
    
private:
    void connect();

    std::vector<server_info> servers;
    
    edonkey_db db;

};

}
}
}
