#pragma once

namespace zap {
namespace sharer {

class ZapSharer {
public:
  ZapSharer();
  ~ZapSharer();
  ZapSharer(const ZapSharer & zs) = delete;
  ZapSharer& operator=(const ZapSharer&) = delete;

  void run();
};

}
}
