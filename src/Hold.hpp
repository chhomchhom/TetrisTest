/*
 * Hold.hpp
 *
 *  Created on: 2017 M11 27
 *      Author: akhma
 */

#ifndef HOLD_HPP_
#define HOLD_HPP_

#include <GL/glut.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include "Constant.hpp"
#include "Block.hpp"

using namespace std;

class Hold {
public:
	Hold();
	void draw();
	int getHold();
	void setHold(int n);
private:
	int nextHold;
	Block *block[7];
	void setPosition();

};




#endif /* HOLD_HPP_ */
