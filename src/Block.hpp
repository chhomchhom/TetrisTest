#ifndef SRC_BLOCK_HPP_
#define SRC_BLOCK_HPP_

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Constant.hpp"
#include "Color.hpp"



//http://tetris.wikia.com/wiki/Tetrimino
class Position {
public:
	int x, y;
	Position();
	Position(int x, int y);
	void set(int x, int y);

};

class Block {
public:
	Color color;
	virtual ~Block();
	void draw(void);
	void draw(int x, int y, int size);
	void rotation();
	void translate(int direction);
	virtual void reset() = 0;
	Position *plist[4];
	Position start;
protected:
	Color outlineColor;
	int direction;
	void drawOutline(int x, int y, int size, Color color);
	bool isvalid(Position *plist[], Position start, int direction);

};

class Block_I: public Block {
public:
	Block_I();
	void reset();
};

class Block_O: public Block {
public:
	Block_O();
	void reset();

};
class Block_T: public Block {
public:
	Block_T();
	void reset();

};
class Block_S: public Block {
public:
	Block_S();

	void reset();

};
class Block_Z: public Block {
public:
	Block_Z();
	void reset();

};

class Block_J: public Block {
public:
	Block_J();
	void reset();

};

class Block_L: public Block {
public:
	Block_L();
	void reset();

};

#endif /* SRC_BLOCK_HPP_ */
