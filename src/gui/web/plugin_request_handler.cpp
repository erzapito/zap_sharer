/*
 * notfound_request_handler.cpp
 *
 *  Created on: 12 de jul. de 2015
 *      Author: zapo
 */



#include "plugin_request_handler.hpp"
#include "reply.hpp"
#include <iostream>
#include <json/json.h>

namespace zap {
namespace sharer {
namespace gui {
namespace web {

plugin_request_handler::plugin_request_handler(zap::sharer::plugin_manager & plugin_manager_)
: plugin_manager (plugin_manager_){
	// nothing to do
}

plugin_request_handler::~plugin_request_handler() {
	// nothing to do
}

bool plugin_request_handler::handle_request(const request& req, reply& rep) {

std::cout << "PLUGIN: start" << std::endl;

	const std::vector<std::string> & segments = req.segments;
    if (segments.empty()) {
		return false;
	}

	const std::string & controllerName = segments[1];

std::cout << "controller: " << controllerName << std::endl;

	if (controllerName.compare("plugins")){
        return false;
    }
	
    Json::Value root;
    root.append("A");
    root.append("B");
    root.append("C");
	
    Json::StreamWriterBuilder wbuilder;
	wbuilder["indentation"] = "\t";
    rep.status = 200;
	rep.content = Json::writeString(wbuilder, root);
  rep.headers.resize(2);
  rep.headers[0].name = "Content-Length";
  rep.headers[0].value = std::to_string(rep.content.size());
  rep.headers[1].name = "Content-Type";
  rep.headers[1].value = "application/json";

    return true;
}

}
}
}
}
