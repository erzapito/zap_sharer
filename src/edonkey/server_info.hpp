#pragma once

#include <string>

namespace zap {
    namespace sharer {
        namespace edonkey {
            
            enum SPECIAL_TAG {
                SPECIAL_TAG_UNKNOWN = 0x00,
                SPECIAL_TAG_NAME = 0x01,
                SPECIAL_TAG_DESCRIPTION = 0x0B,
                SPECIAL_TAG_PING = 0x0C,
                SPECIAL_TAG_MAX_USERS = 0x87,
                SPECIAL_TAG_SOFT_FILES = 0x88,
                SPECIAL_TAG_HARD_FILES = 0x89,
                SPECIAL_TAG_LASTPING = 0x90,
                SPECIAL_TAG_VERSION = 0x91,
                SPECIAL_TAG_UDPFLAGS = 0x92,
                SPECIAL_TAG_AUXPORTSLIST = 0x93,
                SPECIAL_TAG_TCPPORTOBFUSCATION = 0x97,
                
                SPECIAL_TAG_STR_USERS = 0x100,
                SPECIAL_TAG_STR_LOWUSERS = 0x101,
                SPECIAL_TAG_STR_FILES = 0x102,
                SPECIAL_TAG_STR_MAXUSERS = 0x103,
                SPECIAL_TAF_STR_REFS = 0x104,
            };
            
            class server_info {
            public:
                server_info();
                server_info(int id, const char * n, const char * d, uint32_t ip, uint16_t port);
                ~server_info();

				int id;
                
                uint32_t ip;
                uint16_t port;
                uint32_t str_users;
                uint32_t str_lowusers;
                uint32_t ping;
                uint32_t str_files;
                uint32_t str_maxusers;
                uint32_t maxusers;
                uint32_t soft_files;
                uint32_t udpflags;
                uint32_t version;
                uint32_t hard_files;
                uint32_t tcp_port_obfuscation;
                uint32_t refs;
                std::string name;
                std::string description;
                std::string auxportlist;
            };
                    
        }
    }
}
