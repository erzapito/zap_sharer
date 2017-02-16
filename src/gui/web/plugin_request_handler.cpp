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

    static Json::FastWriter jsonWriter;
    const std::vector<std::string> & segments = req.getSegments();
    if (segments.empty()) {
        return false;
    }

    const std::string & controllerName = segments[0];
    if (controllerName.compare("plugins")){
        return false;
    }

    if (segments.size() == 1) {
        const std::vector<std::string> & names = plugin_manager.listPluginNames();
        Json::Value root (Json::arrayValue);
        for (int i = names.size() - 1; i >= 0; i--) {
            root.append(names[i]);
        }
        rep.status = 200;
        rep.content = jsonWriter.write(root);
        rep.headers.resize(2);
        rep.headers[0].name = "Content-Length";
        rep.headers[0].value = std::to_string(rep.content.size());
        rep.headers[1].name = "Content-Type";
        rep.headers[1].value = "application/json";
        return true;
    } else {
        const std::string & pluginName = segments[1];

        zap::sharer::plugin * p = plugin_manager.getPluginByShortName( pluginName );
        if (!p) {
            rep.status = 404;
            return true;
        }
        if (segments.size() == 2) {
            Json::Value root (Json::arrayValue);
            const std::vector<std::string> & actions = p->listActions();
            for (int i = actions.size() - 1; i >= 0; i-- ) {
                root.append(actions[i]);
            }
            rep.status = 200;
            rep.content = jsonWriter.write(root);
            rep.headers.resize(2);
            rep.headers[0].name = "Content-Length";
            rep.headers[0].value = std::to_string(rep.content.size());
            rep.headers[1].name = "Content-Type";
            rep.headers[1].value = "application/json";
            rep.status = 200;
            return true;
        }
        rep.status = 500;
        return true;
    }
}

}
}
}
}
