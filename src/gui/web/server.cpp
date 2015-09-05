#include "server.hpp"
#include "static_request_handler.hpp"
#include "plugin_request_handler.hpp"
#include "notfound_request_handler.hpp"
#include <utility>
#include <memory>
#include <string.h>
#include "reply.hpp"

namespace zap {
namespace sharer {
namespace gui {
namespace web {

static int
answer_to_connection (void *cls, struct MHD_Connection *connection,
                      const char *url, const char *method,
                      const char *version, const char *upload_data,
                      size_t *upload_data_size, void **con_cls)
{
  server * s = static_cast<server *>(cls);
  return s->processRequest(connection, url, method, version, upload_data, upload_data_size);
}


server::server(zap::sharer::plugin_manager & plugin_manager_)
  : plugin_manager(plugin_manager_)
{
  request_handlers.push_back(new static_request_handler("./extra/") );
  request_handlers.push_back(new plugin_request_handler(plugin_manager_) );
  request_handlers.push_back(new notfound_request_handler() );
}

server::~server() {
	stop();
	for (request_handler * h : request_handlers) {
		delete h;
	}
}

void server::configure(const std::string& address, const std::string& port) {
  this->address = address;
  this->port = port;
}

void server::run() {
  daemon = MHD_start_daemon (MHD_USE_SELECT_INTERNALLY, atoi( port.c_str() ), NULL, NULL,
                             &answer_to_connection, this, MHD_OPTION_END);
}

void server::stop() {
  if (daemon) {
    MHD_stop_daemon(daemon);
    daemon = NULL;
  }
}

int server::processRequest (struct MHD_Connection *connection,
                      const char *url, const char *method,
                      const char *version, const char *upload_data,
                      size_t *upload_data_size) {

  request request_ (method, version, url, upload_data, *upload_data_size);
  reply reply_;

  for (request_handler * h : request_handlers) {
	  if (h->handle_request(request_, reply_)) {
		  break;
	  }
  }


  struct MHD_Response *response = 
  MHD_create_response_from_buffer (reply_.content.size(), (void *) reply_.content.c_str(), 
				     MHD_RESPMEM_MUST_COPY);
  for (int i = reply_.headers.size() - 1 ; i >= 0; i--) {
    MHD_add_response_header (response, reply_.headers[i].name.c_str(), reply_.headers[i].value.c_str());
  }  

  int ret = MHD_queue_response (connection, reply_.status, response);
  MHD_destroy_response (response);
  return ret;
}

}
}
}
}
