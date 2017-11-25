#include "World.hpp"

Grid::Grid() {
	color.setColor(0, 0, 0, 1); // Default Color black
	isActive = false;
}

void Grid::setActive(Color color) {
	this->color.setColor(color.red, color.green, color.blue, color.alpha);
	isActive = true;
}

void Grid::setDeactive() {
	color.setColor(0, 0, 0, 1); // Default Color black
	isActive = false;
}

World::World() {
	block[0] = new Block_I();
	block[1] = new Block_O();
	block[2] = new Block_T();
	block[3] = new Block_S();
	block[4] = new Block_Z();
	block[5] = new Block_J();
	block[6] = new Block_L();

	srand(time(NULL)); // Make random actually random
	this->current = rand() % 7;
	movecount = 0;

}

void World::draw() {

	this->next.draw();
	if (GameStatus == GAME_STATUS_RUNNING) {

		if (KeyDirection == GAME_KEY_UP) {
			block[this->current]->rotation();
			KeyDirection = GAME_KEY_NULL;
		} else if (KeyDirection != GAME_KEY_DOWN) {
			block[this->current]->translate(KeyDirection);
			KeyDirection = GAME_KEY_NULL;
		}
		if (movecount < 99) {
			movecount++;
		} else {
			if (isHit()) {
				if (block[this->current]->start.y == GAME_ZONE_ROWS) {
					GameStatus = GAME_STATUS_END;
					this->reset();
				} else {
				deleteGrid();
				block[this->current]->reset();
					current = this->next.getNext();
				}
			} else {
				block[this->current]->translate(GAME_KEY_DOWN);
			}
			movecount = 0;
		}
		block[current]->draw();
		drawGrid();
	}
}

void World::reset() {
	srand(time(NULL)); // Make random actually random
	current = rand() % 7;
	// Reset gridtop
	int i, j;

	for (i = 0; i < GAME_ZONE_ROWS; i++) {
		for (j = 0; j < GAME_ZONE_COLS; j++) {
			grid[i][j].setDeactive();
		}
	}
	for (i = 0; i < 7; i++) {
		block[i]->reset();
	}
}

bool World::isHit() {
	int i, startx, starty, x, y;
	startx = this->block[this->current]->start.x;
	starty = this->block[this->current]->start.y;
	if (starty == 20) {
		if (grid[19][startx].isActive) {
			return true;
		} else {
			return false;
		}
	}
	for (i = 0; i < 4; i++) {
		x = this->block[this->current]->plist[i]->x;
		y = this->block[this->current]->plist[i]->y;
		if (starty + y == 0) {
			updateWorld();
			return true;

		} else if (grid[starty + y - 1][startx + x].isActive) {

			updateWorld();
			return true;
		}
	}
	return false;
}

void World::updateWorld() {
	int i, startx, starty, x, y;
	startx = this->block[this->current]->start.x;
	starty = this->block[this->current]->start.y;
	Color color = this->block[this->current]->color;
	for (i = 0; i < 4; i++) {
		x = this->block[this->current]->plist[i]->x;
		y = this->block[this->current]->plist[i]->y;
		this->grid[starty + y][startx + x].setActive(color);
	}

}

void World::drawGrid() {
	int i, j, x, y, x1, y1;
	for (i = 0; i < GAME_ZONE_ROWS; i++) {
		for (j = 0; j < GAME_ZONE_COLS; j++) {
			if (grid[i][j].isActive) {
				Color colors = grid[i][j].color;
				x = j * GAME_BLOCK_SIZE + GAME_ZONE_X;
				y = i * GAME_BLOCK_SIZE + GAME_ZONE_Y;
				x1 = x + GAME_BLOCK_SIZE;
				y1 = y + GAME_BLOCK_SIZE;
				glColor3f(colors.red, colors.green, colors.blue);
				glRecti(x, y, x1, y1);
				drawOutline(x, y, GAME_BLOCK_SIZE);
			}
		}
	}
}

void World::drawOutline(int x, int y, int size) {
	glColor3f(0, 0, 0);
	glLineWidth(4.0);
	glBegin(GL_LINES);
	glVertex2i(x, y);
	glVertex2i(x + size, y);
	glVertex2i(x + size, y);
	glVertex2i(x + size, y + size);
	glVertex2i(x + size, y + size);
	glVertex2i(x, y + size);
	glVertex2i(x, y + size);
	glVertex2i(x, y);
	glEnd();
}

void World::deleteGrid() {
	bool status = true;
	int i, j;
	while (status) {
		for (i = 0; i < GAME_ZONE_ROWS; i++) {
			bool line = true;
			for (j = 0; j < GAME_ZONE_COLS; j++) {
				if (!grid[i][j].isActive) {
					line = false;
					break;
				}
			}
			if (line) {
				Score += 5;
				int k;
				for (k = i; k < GAME_ZONE_ROWS - 2; k++) {
					line = true;
					for (j = 0; j < GAME_ZONE_COLS; j++) {
						if (grid[k + 1][j].isActive) {
							grid[k][j].setActive(grid[k + 1][j].color);
							line = false;
						} else {
							grid[k][j].setDeactive();

						}
					}
					if (line) {
						break;
					}
				}
				for (k = 0; k < GAME_ZONE_COLS; k++) {
					grid[GAME_ZONE_ROWS - 1][k].setDeactive();
				}
				break;
			} else {
				status = false;
			}
		}
	}
}
