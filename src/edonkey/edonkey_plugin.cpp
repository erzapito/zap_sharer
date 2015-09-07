#include "edonkey_plugin.hpp"

namespace zap {
namespace sharer {
namespace edonkey {

    edonkey_plugin::edonkey_plugin():
    name("edonkey")
    {}
    
    edonkey_plugin::~edonkey_plugin() {
        // nothing to do
    }
    
    std::string & edonkey_plugin::getName() {
        return name;
    }
    
    std::vector<std::string> & edonkey_plugin::listActions() {
        return actions;
    }
    
}
}
}
