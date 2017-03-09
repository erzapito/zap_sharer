#pragma once

//#include "connection_manager.hpp"
//#include <boost/asio.hpp>
//#include <thread>
#include "request_handler.hpp"
#include "../../plugin_manager.hpp"
#include <microhttpd.h>

namespace zap {
namespace sharer {
namespace gui {
namespace web {

/// The top-level class of the HTTP server.
class server
{
public:
  server(zap::sharer::plugin_manager & plugin_manager);
  server(const server&) = delete;
  server& operator=(const server&) = delete;
  ~server();

  /// Construct the server to listen on the specified TCP address and port, and
  /// serve up files from the given directory.
 void configure(
		 const std::string& address,
		 const std::string& port);

  /// Run the server's io_service loop.
 void run();

 void stop();

  int processRequest (struct MHD_Connection *connection,
                      const char *url, const char *method,
                      const char *version, const char *upload_data,
                      size_t *upload_data_size);

private:

  std::string address;
  std::string port;

  /// The handler for all incoming requests.
  std::vector<std::unique_ptr<request_handler>> request_handlers;

  zap::sharer::plugin_manager & plugin_manager;

  struct MHD_Daemon *daemon;
};

// namespace end
}
}
}
}
