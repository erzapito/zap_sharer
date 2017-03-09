#pragma once

#include "request_handler.hpp"

namespace zap {
namespace sharer {
namespace gui {
namespace web {

class notfound_request_handler : public request_handler {
public:
	notfound_request_handler();
	virtual ~notfound_request_handler() ;

	bool handle_request(const request& req, reply& rep) override;
};

}
}
}
}
