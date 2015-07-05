#pragma once

#include <string>

namespace zap {
namespace sharer {
namespace gui {
namespace web {

namespace mime_types {

/// Convert a file extension into a MIME type.
std::string extension_to_type(const std::string& extension);

} // namespace mime_types

}
}
}
}
