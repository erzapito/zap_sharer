#pragma once

#include "plugin.hpp"
#include <vector>
#include <string>
#include <unordered_map>

namespace zap {
namespace sharer {

class plugin_manager {
public:
    plugin_manager();
    plugin_manager(const plugin_manager&) = delete;
    plugin_manager& operator=(const plugin_manager&) = delete;
    ~plugin_manager();

    const std::vector<std::string> & listPluginNames();
    plugin * getPluginByShortName(const std::string & name);
    
    void addPlugin(plugin * p);
private:
    std::vector<std::string> currentPluginNames;
    std::unordered_map< std::string , plugin * > plugins;
};

}
}
