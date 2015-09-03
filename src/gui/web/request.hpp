#pragma once

#include <string>
#include <vector>
#include "header.hpp"

namespace zap {
namespace sharer {
namespace gui {
namespace web {

/// A request received from a client.
class request
{
public:
  std::string method;
  std::string http_version;
  std::vector<header> headers;
  std::string request_path;
  std::vector<std::string> segments;
  std::string uri;
  std::string content;

  request (const char * method,
	const char * version,
	const char * url,
	const char * content,
    const size_t & content_size);
private:
  bool decodeUri();
};

} // namespace server
} // namespace http
}
}
