#pragma once

namespace zap {
namespace sharer {

class plugin_manager {
public:
	plugin_manager();
	plugin_manager(const plugin_manager&) = delete;
	plugin_manager& operator=(const plugin_manager&) = delete;
	~plugin_manager();
};

}
}
