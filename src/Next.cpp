
#include "Next.hpp"

Next::Next() {
	block[0] = new Block_I();
	block[1] = new Block_O();
	block[2] = new Block_T();
	block[3] = new Block_S();
	block[4] = new Block_Z();
	block[5] = new Block_J();
	block[6] = new Block_L();
	srand(time(NULL)); // Make random actually random
	this->next = rand() % 7;
}

int Next::getNext() {
	int n = next;
	srand(time(NULL)); // Make random actually random
	this->next = rand() % 7;
	return n;
}

void Next::setNext(int n) {
	this->next = n;
}

void Next::draw() {

	this->block[next]->draw(575, 700, 25);

}
