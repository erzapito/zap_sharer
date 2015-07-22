#include "ZapSharer.hpp"
#include "gui/web/server.hpp"
#include "plugin_manager.hpp"

namespace zap {
namespace sharer {

ZapSharer::ZapSharer() {
}

ZapSharer::~ZapSharer() {
}

void ZapSharer::run() {
	zap::sharer::plugin_manager plugin_manager;

	zap::sharer::gui::web::server s (plugin_manager);
	s.configure("0.0.0.0","9999");

	s.run();

	std::thread main ([](){
		while (true) {
			char c = getchar();
			if (c == 's') {
				break;
			}
		}
	});
	main.join();

	s.stop();
}

}
}
