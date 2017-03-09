#include "plugin_manager.hpp"

namespace zap {
namespace sharer {

plugin_manager::plugin_manager() {

}

plugin_manager::~plugin_manager() {

}

const std::vector<std::string> & plugin_manager::listPluginNames() {
	return currentPluginNames;
}

plugin * plugin_manager::getPluginByShortName(const std::string & n) {
	return plugins[n].get();
}

void plugin_manager::addPlugin(std::unique_ptr<plugin> p) {
    std::string name = p->getName();
    currentPluginNames.push_back(name);
    plugins[name] = std::move(p);
}

}
}
