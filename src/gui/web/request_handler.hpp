#pragma once

#include <string>
#include "request.hpp"

namespace zap {
namespace sharer {
namespace gui {
namespace web {

struct reply;
struct request;

/// The common handler for all incoming requests.
class request_handler {
public:
	virtual ~request_handler() {};
	virtual bool handle_request(const request& req, reply& rep) = 0;
};

}
}
}
}
