#pragma once


#include <string>
#include <vector>
#include <boost/asio.hpp>
#include "header.hpp"

namespace zap {
namespace sharer {
namespace gui {
namespace web {

/// A reply to be sent to a client.
struct reply
{
  /// The status of the reply.
  int status;

  /// The headers to be included in the reply.
  std::vector<header> headers;

  /// The content to be sent in the reply.
  std::string content;
};

} // namespace server
} // namespace http
}
}
