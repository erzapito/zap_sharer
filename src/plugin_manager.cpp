#include "plugin_manager.hpp"

namespace zap {
namespace sharer {

plugin_manager::plugin_manager() {

}

plugin_manager::~plugin_manager() {
	for (auto & p : plugins ) {
      delete p.second;
    }
}

std::vector<std::string> & plugin_manager::listPluginNames() {
	return currentPluginNames;
}

plugin * plugin_manager::getPluginByShortName(const std::string & n) {
	return plugins[n];
}

}
}
