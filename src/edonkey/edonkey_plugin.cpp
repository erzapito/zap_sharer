#include "edonkey_plugin.hpp"
#include <fstream>
#include <boost/algorithm/string/predicate.hpp>
#include <iostream>

const std::string PLUGIN_NAME("edonkey");
const char * CONNECT_ACTION = "connect";
const std::vector<std::string> ACTIONS {
  CONNECT_ACTION
};

namespace zap {
namespace sharer {
namespace edonkey {

    edonkey_plugin::edonkey_plugin(std::shared_ptr<zap::sharer::db_wrapper> _db):
    db(_db)
    {
	db.loadServerList(servers);
    }

    edonkey_plugin::~edonkey_plugin() {
        // nothing to do
    }
    
    const std::string & edonkey_plugin::getName() {
        return PLUGIN_NAME;
    }
    
    const std::vector<std::string> & edonkey_plugin::listActions() {
        return ACTIONS;
    }
    
    const std::vector<server_info> & edonkey_plugin::listServers() const {
        return servers;
    }
    
    void edonkey_plugin::executeAction(const std::string & action) {
	if (action == CONNECT_ACTION) {
	    connect();
	}
    }
    
    void edonkey_plugin::addServer(server_info& info) {
		// check it does not exist
		bool found = false;
		for (std::vector<server_info>::iterator it = servers.begin(); it != servers.end(); it++) {
			server_info & si = *it;
			if (si.name == info.name) {
				found = true;
				info.id = si.id;
				si = info;
				db.updateServerInfo(si);
			}
		}
		if (!found) {
        	servers.push_back(info);
			db.addServerInfo(info);
		}
    }
    
    SPECIAL_TAG readSpecialTag(std::istream & s) {
        static uint16_t ts;
        static uint32_t t;
        s.read((char*)&ts,sizeof(ts));
        if (ts == 1) {
            s.read((char*)&t,ts);
            return static_cast<SPECIAL_TAG>(t);
        } else {
            //char * buffer = new char[ts + 1];
            char buffer[ts + 1];
            buffer[ts] = 0;
            s.read(buffer,ts);
            
            if (strncmp(buffer,"users",ts) == 0) {
                return SPECIAL_TAG_STR_USERS;
            }
            if (strncmp(buffer,"lowusers",ts) == 0) {
                return SPECIAL_TAG_STR_LOWUSERS;
            }
            if (strncmp(buffer,"files",ts) == 0) {
                return SPECIAL_TAG_STR_FILES;
            }
            if (strncmp(buffer,"maxusers",ts) == 0) {
                return SPECIAL_TAG_STR_MAXUSERS;
            }
            if (strncmp(buffer,"refs",ts) == 0) {
                return SPECIAL_TAF_STR_REFS;
            }
            
            printf("Unknown special tag[%d]: %s\n", ts, buffer);   
            return SPECIAL_TAG_UNKNOWN;
        }
        return SPECIAL_TAG_UNKNOWN;
        
        
    }
    
    void edonkey_plugin::connect(){
	
    }
    
    void edonkey_plugin::loadServerMet(const std::string & serverMetUrl) {
        std::istream * serverMetStream = NULL;
        
        if (boost::starts_with(serverMetUrl,"file:")) {
            serverMetStream = new std::ifstream(serverMetUrl.substr(5), std::ios::in|std::ios::binary);
        }
        
        if (serverMetStream) {
            auto readServerMetData = [] (std::istream & s, edonkey_plugin * donkeyPlugin) {
                uint8_t c8;
                s.read((char *)&c8,sizeof(c8));
                if (c8 != 0x0E) return;
                
                uint32_t serverCount;
                s.read((char *)&serverCount,sizeof(serverCount));
                if (!s) return;
                
                while (serverCount-- > 0) {
                    server_info info;
                    
                    s.read((char *)&info.ip, sizeof(info.ip));
                    if (!s) return;
                    s.read((char *)&info.port, sizeof(info.port));
                    if (!s) return;
                    uint32_t numTags;
                    s.read((char *)&numTags, sizeof(numTags));
                    if (!s) return;

                    while (numTags-- > 0) {
                        uint8_t tagType;
                        s.read((char *)&tagType, sizeof(tagType));
                        if (!s) return;
                        
                        SPECIAL_TAG specialTag = readSpecialTag(s);
                        //uint16_t specialTagSize;
                        //int specialTag;
                        char * strData;
                        uint16_t stringLength;
                        uint32_t dword;
                        
                        switch (tagType) {
                            case 0x00: // UNDEFINED ???
                                break;
                            case 0x02: // [SPECIAL TAG] [STRING]
                                s.read((char*)&stringLength, sizeof(stringLength));
                                strData = new char[stringLength + 1];
                                strData[stringLength] = 0;
                                s.read(strData, stringLength);
                                
                                switch (specialTag) {
                                    case SPECIAL_TAG_NAME:
                                        info.name = strData;
                                        //printf("Name: %s\n",strData);
                                        break;
                                    case SPECIAL_TAG_DESCRIPTION:
                                        info.description = strData;
                                        //printf("Description: %s\n",strData);
                                        break;
                                    case SPECIAL_TAG_AUXPORTSLIST:
                                        info.auxportlist = strData;
                                        break;
                                    default:
                                        printf("unknown server.met, tag 2, special tag type:  %X\n", specialTag);
                                        return;
                                }
                                
                                break;
                            case 0x03: // [SPECIAL TAG] [DWORD]
                                s.read((char *)&dword, sizeof(dword));
                                switch (specialTag) {
                                    case SPECIAL_TAG_STR_USERS:
                                        info.str_users = dword;
                                        break;
                                    case SPECIAL_TAG_STR_LOWUSERS:
                                        info.str_lowusers = dword;
                                        break;
                                    case SPECIAL_TAG_PING:
                                        info.ping = dword;
                                        break;
                                    case SPECIAL_TAG_STR_FILES:
                                        info.str_files = dword;
                                        break;
                                    case SPECIAL_TAG_STR_MAXUSERS:
                                        info.str_maxusers = dword;
                                        break;
                                    case SPECIAL_TAG_MAX_USERS:
                                        info.maxusers = dword;
                                        break;
                                    case SPECIAL_TAG_SOFT_FILES:
                                        info.soft_files = dword;
                                        break;
                                    case SPECIAL_TAG_UDPFLAGS:
                                        info.udpflags = dword;
                                        break;
                                    case SPECIAL_TAG_VERSION:
                                        info.version = dword;
                                        break;
                                    case SPECIAL_TAG_HARD_FILES:
                                        info.hard_files = dword;
                                        break;
                                    case SPECIAL_TAG_TCPPORTOBFUSCATION:
                                        info.tcp_port_obfuscation = dword;
                                        break;
                                    case SPECIAL_TAF_STR_REFS:
                                        info.refs = dword;
                                        break;
                                    default:
                                        printf("unknown server.met, tag 3, special tag type:  %X\n", specialTag);
                                        return;
                                }
                                break;
                            default:
                                 printf("unknown server.met tag type:  %X\n", tagType);
                                 return;
                        }
                    }
                    
                    
                    donkeyPlugin->addServer(info);
                    //delete[] name;
                }
            };
            readServerMetData(*serverMetStream, this);
            delete serverMetStream;
        }
    }
    
}
}
}
