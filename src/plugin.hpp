#pragma once

#include <vector>
#include <string>

namespace zap {
namespace sharer {

class plugin {
public:
	virtual ~plugin() {};
    virtual std::string & getName();
	virtual std::vector<std::string> & listActions();
};

}
}
