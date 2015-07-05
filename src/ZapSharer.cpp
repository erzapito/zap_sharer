/*
 ============================================================================
 Name        : ZapSharer.cpp
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C++,
 ============================================================================
 */

#include "gui/web/server.hpp"

#include <iostream>

using namespace std;

int main(void) {

	zap::sharer::gui::web::server s;
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
	return 0;
}
