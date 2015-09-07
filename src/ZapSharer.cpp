#include "ZapSharer.hpp"
#include "gui/web/server.hpp"
#include "plugin_manager.hpp"
#include "edonkey/edonkey_plugin.hpp"

#include <thread>

namespace zap {
namespace sharer {

ZapSharer::ZapSharer() {
}

ZapSharer::~ZapSharer() {
}

void ZapSharer::run() {
	zap::sharer::plugin_manager plugin_manager;
        zap::sharer::edonkey::edonkey_plugin * donkey_plugin = new zap::sharer::edonkey::edonkey_plugin();
        plugin_manager.addPlugin(donkey_plugin);

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
