#pragma once

#include "request_handler.hpp"
#include <string>

namespace zap {
namespace sharer {
namespace gui {
namespace web {

struct reply;
struct request;

/// The common handler for all incoming requests.
class static_request_handler : public request_handler
{
public:
	static_request_handler(const static_request_handler&) = delete;
  static_request_handler& operator=(const static_request_handler&) = delete;
  virtual ~static_request_handler() ;

  /// Construct with a directory containing files to be served.
  explicit static_request_handler(const std::string& doc_root);

  /// Handle a request and produce a reply.
  bool handle_request(const request& req, reply& rep);

private:
  /// The directory containing the files to be served.
  std::string doc_root_;

};

} // namespace server
} // namespace http
}
}
