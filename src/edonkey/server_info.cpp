#include "server_info.hpp"

namespace zap {
    namespace sharer {
        namespace edonkey {
            
		server_info::server_info() {};
                      
		server_info::server_info(int _id, const std::string & n, const std::string & d, uint32_t _ip, uint16_t _port):
		  id(_id),
		  ip(_ip),
		  port(_port),
		  name(n),
		  description(d)
            {};

            server_info::~server_info() {
                // nothing to do
            }
            
        }
    }
}
