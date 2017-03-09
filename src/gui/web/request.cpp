#include "request.hpp"
#include <sstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <iostream>

namespace zap {
namespace sharer {
namespace gui {
namespace web {

request::request (const std::string & _method,
	const std::string & version,
	const std::string & url,
	const std::string & _content,
    const size_t & content_size)
:
method(_method),
http_version(version),
uri(url),
content(_content,content_size)
{
  valid = decodeUri();
  if (valid) {
    std::vector<std::string> segs;
    boost::split(segs, request_path, boost::is_any_of("/"));
    for (auto & s : segs) {
      if (!s.empty()) {
        segments.push_back(s);
      };
    }
  }
}

bool request::decodeUri()
{
  std::string & in = this->uri;
  std::string out;

  out.clear();
  out.reserve(in.size());
  for (std::size_t i = 0; i < in.size(); ++i)
  {
    if (in[i] == '%')
    {
      if (i + 3 <= in.size())
      {
        int value = 0;
        std::istringstream is(in.substr(i + 1, 2));
        if (is >> std::hex >> value)
        {
          out += static_cast<char>(value);
          i += 2;
        }
        else
        {
          return false;
        }
      }
      else
      {
        return false;
      }
    }
    else if (in[i] == '+')
    {
      out += ' ';
    }
    else
    {
      out += in[i];
    }
  }
  this->request_path = out;
  return true;
}


}
}
}
}
