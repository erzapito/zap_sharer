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
  int http_version_major;
  int http_version_minor;
  std::vector<header> headers;
  std::vector<std::string> segments;
  std::string uri;
};

} // namespace server
} // namespace http
}
}
