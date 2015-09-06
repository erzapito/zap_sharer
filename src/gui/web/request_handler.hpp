#pragma once

#include <string>
#include "request.hpp"
#include "reply.hpp"

namespace zap {
namespace sharer {
namespace gui {
namespace web {

/// The common handler for all incoming requests.
class request_handler {
public:
	virtual bool handle_request(const request& req, reply& rep) = 0;
};

}
}
}
}
