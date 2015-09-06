#pragma once

#include <vector>
#include <string>

namespace zap {
namespace sharer {

class plugin {
public:
    virtual std::string & getName() = 0;
    virtual std::vector<std::string> & listActions() = 0;
};

}
}
