#pragma once

#include "../plugin.hpp"

namespace zap {
namespace sharer {
namespace edonkey {  


class edonkey_plugin : public zap::sharer::plugin {
public:
    edonkey_plugin();
    edonkey_plugin(const edonkey_plugin & p);
    edonkey_plugin& operator=(const edonkey_plugin&) = delete;
    ~edonkey_plugin();
    
    std::string & getName();
    std::vector<std::string> & listActions();
private:
    std::string name;
    std::vector<std::string> actions;
};

}
}
}
