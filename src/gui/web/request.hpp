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
  request();
  request (const std::string & method,
	const std::string & version,
	const std::string & url,
	const std::string & content,
    const size_t & content_size);

  const std::string & getRequestPath() const {
    return request_path;
  }

  const std::vector<std::string> & getSegments() const {
    return segments;
  }

  bool isValid() const {
    return valid;
  }
 
private:
  bool decodeUri();

  bool valid;
  std::string method;
  std::string http_version;
  std::vector<header> headers;
  std::string request_path;
  std::vector<std::string> segments;
  std::string uri;
  std::string content;
};

} // namespace server
} // namespace http
}
}
