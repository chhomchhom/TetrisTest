
#ifndef SRC_WORLD_HPP_
#define SRC_WORLD_HPP_

#include <time.h>
#include <iostream>
#include <stdlib.h>
#include "Constant.hpp"
#include "Block.hpp"
#include "Color.hpp"
#include "Next.hpp"
#include <math.h>

using namespace std;
extern int GameStatus, KeyDirection, Score, HighScore;
extern float moved;

class Grid {
public:
	Grid();
	void setActive(Color color);
	void setDeactive();
	bool isActive;
	Color color;
};



class World {
public:
	World();
	void draw();
	void reset();
private:
	int current;
	int movecount;
	Grid grid[GAME_ZONE_ROWS][GAME_ZONE_COLS];
	Block *block[7];
	Next next;
	bool isHit();
	void updateWorld(); // This function will update everything need to be update after The object hit the world
	void drawGrid();
	void drawOutline(int x, int y, int size);
	void deleteGrid();
};




#endif
