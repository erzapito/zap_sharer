#include "reply.hpp"
#include "request.hpp"
#include "mime_types.hpp"
#include <fstream>
#include <iostream>
#include "static_request_handler.hpp"

namespace zap {
namespace sharer {
namespace gui {
namespace web {

static_request_handler::static_request_handler(const std::string& doc_root)
  : doc_root_(doc_root)
{
}

static_request_handler::~static_request_handler() {
}

bool static_request_handler::handle_request(const request& req, reply& rep)
{
  // Decode url to path.
  std::string request_path (req.getRequestPath());
  /*if (!url_decode(req.uri, request_path))
  {
    rep = reply::stock_reply(reply::bad_request);
    return true;
  }*/

  // Request path must be absolute and not contain "..".
  if (request_path.empty() || request_path[0] != '/'
      || request_path.find("..") != std::string::npos)
  {
	rep.status = 404;
    return true;
  }

  // If path ends in slash (i.e. is a directory) then add "index.html".
  if (request_path[request_path.size() - 1] == '/')
  {
    request_path += "index.html";
  }

  // Determine the file extension.
  std::size_t last_slash_pos = request_path.find_last_of("/");
  std::size_t last_dot_pos = request_path.find_last_of(".");
  std::string extension;
  if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos)
  {
    extension = request_path.substr(last_dot_pos + 1);
  }

  // Open the file to send back.
  std::string full_path = doc_root_ + request_path;
  std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
  if (!is)
  {
    return false;
  }

  // Fill out the reply to be sent to the client.
  rep.status = 200;
  char buf[512];
  while (is.read(buf, sizeof(buf)).gcount() > 0)
    rep.content.append(buf, is.gcount());
  rep.headers.resize(2);
  rep.headers[0].name = "Content-Length";
  rep.headers[0].value = std::to_string(rep.content.size());
  rep.headers[1].name = "Content-Type";
  rep.headers[1].value = mime_types::extension_to_type(extension);
  return true;
}

}
}
}
}
