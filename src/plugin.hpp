#pragma once

#include <vector>
#include <string>

namespace zap {
namespace sharer {

class plugin {
public:
    virtual ~plugin() {};
    virtual const std::string & getName() = 0;
    virtual const std::vector<std::string> & listActions() = 0;
};

}
}
