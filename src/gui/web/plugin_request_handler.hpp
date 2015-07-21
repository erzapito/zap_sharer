#pragma once

#include "request_handler.hpp"
#include "../../plugin_manager.hpp"

namespace zap {
namespace sharer {
namespace gui {
namespace web {

class plugin_request_handler : public request_handler {
public:
	plugin_request_handler(zap::sharer::plugin_manager & plugin_manager_);

	plugin_request_handler(const plugin_request_handler&) = delete;
	plugin_request_handler& operator=(const plugin_request_handler&) = delete;
	virtual ~plugin_request_handler() ;

	bool handle_request(const request& req, reply& rep);
private:
	zap::sharer::plugin_manager & plugin_manager;
};

}
}
}
}
