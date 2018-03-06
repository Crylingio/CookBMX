#include "HUD.h"
#include <iostream>

void HUD::draw() const {
    for (int i = 0; i < _value / 5; ++i) {
		std::cout << (char) 0xDB;
	}
}
