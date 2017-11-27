/*
 * Hold.cpp
 *
 *  Created on: 2017 M11 27
 *      Author: akhma
 */

#include "Hold.hpp"


Hold::Hold() {
	block[0] = new Block_I();
	block[1] = new Block_O();
	block[2] = new Block_T();
	block[3] = new Block_S();
	block[4] = new Block_Z();
	block[5] = new Block_J();
	block[6] = new Block_L();
	nextHold = -1;
}

int Hold::getHold() {
	int n = nextHold;
	return n;
}

void Hold::setHold(int n) {
	this->nextHold = n;
}

void Hold::draw() {

	this->block[nextHold]->draw(575, 600, 25);

}
