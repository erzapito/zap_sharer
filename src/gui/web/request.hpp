#pragma once

#include <string>
#include <vector>
#include "header.hpp"

namespace zap {
namespace sharer {
namespace gui {
namespace web {

/// A request received from a client.
struct request
{
  std::string method;
  std::string uri;
  int http_version_major;
  int http_version_minor;
  std::vector<header> headers;
};

} // namespace server
} // namespace http
}
}
