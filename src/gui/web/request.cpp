#include "request.hpp"
#include <sstream>
#include <string>

namespace zap {
namespace sharer {
namespace gui {
namespace web {

/*const std::vector<std::string> & request::getSegments(){
    if (segmentsCalculated) return segments;

    boost::split(segments, path, boost::is_any_of("/"));
    segmentsCalculated = true;
    return segments;
}*/

request::request (const char * method,
	const char * version,
	const char * url,
	const char * content,
    const size_t & content_size)
:
method(method),
http_version(version),
uri(url),
content(content,content_size)
{
  decodeUri();

}

bool request::decodeUri()
{
  std::string & in = this->uri;
  std::string & out = this->request_path;

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
  return true;
}


}
}
}
}
