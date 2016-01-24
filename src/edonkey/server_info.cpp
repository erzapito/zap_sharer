#include "server_info.hpp"

namespace zap {
    namespace sharer {
        namespace edonkey {
            
            server_info::server_info() {};
                      
            server_info::server_info(int id, const char * n, const char * d, uint32_t ip, uint16_t port):
            id(id),
            name(n),
			description(d),
			ip(ip),
            port(port)
            {};

            server_info::~server_info() {
                // nothing to do
            }
            
        }
    }
}
