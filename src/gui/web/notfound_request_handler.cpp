/*
 * notfound_request_handler.cpp
 *
 *  Created on: 12 de jul. de 2015
 *      Author: zapo
 */



#include "notfound_request_handler.hpp"
#include "reply.hpp"
#include <iostream>

namespace zap {
namespace sharer {
namespace gui {
namespace web {

notfound_request_handler::notfound_request_handler() {
	// nothing to do
}

notfound_request_handler::~notfound_request_handler() {
	// nothing to do
}

bool notfound_request_handler::handle_request(const request& req, reply& rep) {
  std::cout << "File not found" << std::endl;
  rep = reply::stock_reply(reply::not_found);
  return true;
}

}
}
}
}
