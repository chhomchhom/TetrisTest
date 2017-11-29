#include "Block.hpp"

//================================================================
// Position Class
Position::Position() {
	this->x = 0;
	this->y = 0;
}

Position::Position(int x, int y) {
	this->x = x;
	this->y = y;
}
void Position::set(int x, int y) {
	this->x = x;
	this->y = y;
}

//===============================================================
// Block Class
void Block::drawOutline(int x, int y, int size, Color color) {
	glColor3f(color.red, color.green, color.blue);
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

void Block::draw() {
	int i, x1, y1, x2, y2;

	for (i = 0; i < 4; i++) {
		if (this->start.y + this->plist[i]->y < GAME_ZONE_ROWS) {
			glColor3f(color.red, color.green, color.blue);
			x1 = (this->plist[i]->x + this->start.x) * GAME_BLOCK_SIZE
					+ GAME_ZONE_X;
			y1 = (this->plist[i]->y + this->start.y) * GAME_BLOCK_SIZE
					+ GAME_ZONE_Y;
			x2 = x1 + GAME_BLOCK_SIZE;
			y2 = y1 + GAME_BLOCK_SIZE;

			glRecti(x1, y1, x2, y2);
			this->drawOutline(x1, y1, GAME_BLOCK_SIZE, this->outlineColor);
		}
	}

}

void Block::draw(int x, int y, int size) {
	int i, x1, y1, x2, y2;
	for (i = 0; i < 4; i++) {

		glColor3f(color.red, color.green, color.blue);
		x1 = (this->plist[i]->x * size) + x;
		y1 = (this->plist[i]->y * size) + y;

		x2 = x1 + size;
		y2 = y1 + size;

		glRecti(x1, y1, x2, y2);
		this->drawOutline(x1, y1, size, this->outlineColor);

	}
}

void Block::translate(int direction) {
	int i, valid = true;
	if (direction == GAME_KEY_RIGHT) {
		for (i = 0; i < 4; i++) {
			if (this->plist[i]->x + this->start.x + 1 == GAME_ZONE_COLS) {
				valid = false;
				break;
			}
		}
	} else if (direction == GAME_KEY_LEFT) {
		for (i = 0; i < 4; i++) {
			if (this->plist[i]->x + this->start.x - 1 == -1) {
				valid = false;
				break;
			}
		}
	} else if (direction == GAME_KEY_DOWN) {
		// Reserve for KEY_DOWN
		for (i = 0; i < 4; i++) {
			if (this->plist[i]->y + this->start.y - 1 == -1) {
				valid = false;
				break;
			}
		}
	}

	if (valid) {
		switch (direction) {
		case GAME_KEY_DOWN: {
			this->start.set(this->start.x, this->start.y - 1);
			break;
		}
		case GAME_KEY_LEFT: {
			this->start.set(this->start.x - 1, this->start.y);
			break;
		}
		case GAME_KEY_RIGHT: {
			this->start.set(this->start.x + 1, this->start.y);
			break;
		}
		}
	}
}
void Block::rotation() {
	float angle = 90 * M_PI / 180;
	int i, x, y;
	float tempx, tempy;
	for (i = 0; i < 4; i++) {
		x = this->plist[i]->x;
		y = this->plist[i]->y;
		tempx = x * cos(angle) + y * sin(angle);
		tempy = -x * sin(angle) + y * cos(angle);
		tempx = round(tempx);
		tempy = round(tempy);
		this->plist[i]->set(tempx, tempy);
	}
	this->direction++;
	if (this->direction == 4) {
		this->direction = GAME_BLOCK_UP;
	}
	// if out of the game zone, push the block back
	bool fix = false;
	while (!fix) {
		for (i = 3; i >= 0; i--) {
			if (i == 0) {
				fix = true;
			} else {
				int x = this->start.x + this->plist[i]->x;
				if (x >= GAME_ZONE_COLS) {
					this->start.set(this->start.x - 1, this->start.y);
					break;
				} else if (x < 0) {
					this->start.set(this->start.x + 1, this->start.y);
					break;
				}
			}

		}
	}

}
bool Block::isvalid(Position *plist[], Position start, int direction) {
	switch (direction) {
	case GAME_BLOCK_UP: {
		break;
	}
	case GAME_BLOCK_LEFT: {
		break;
	}
	case GAME_BLOCK_RIGHT: {
		break;
	}
	case GAME_BLOCK_DOWN: {
		break;
	}
	}
	return true;
}

Block::~Block() {

}

//================================================================
// Block_I Class
Block_I::Block_I() {
	this->direction = GAME_BLOCK_RIGHT;
	this->start.set(GAME_ZONE_COLS / 2 - 2, GAME_ZONE_ROWS);
	this->plist[0] = new Position(0, 0);
	this->plist[1] = new Position(1, 0);
	this->plist[2] = new Position(2, 0);
	this->plist[3] = new Position(3, 0);
	this->outlineColor.setColor(0, 0, 0, 1);
	this->color.setColor(0, 1, 1, 1);
}

void Block_I::reset() {
	this->plist[0]->set(0, 0);
	this->plist[1]->set(0, 1);
	this->plist[2]->set(0, 2);
	this->plist[3]->set(0, 3);
	this->direction = GAME_BLOCK_RIGHT;
	this->start.set(GAME_ZONE_COLS / 2 - 2, GAME_ZONE_ROWS);
}

Block_O::Block_O() {
	this->start.set(GAME_ZONE_COLS / 2 - 1, GAME_ZONE_ROWS);
	this->plist[0] = new Position(0, 0);
	this->plist[1] = new Position(1, 0);
	this->plist[2] = new Position(1, 1);
	this->plist[3] = new Position(0, 1);
	this->outlineColor.setColor(0, 0, 0, 1);
	this->color.setColor(1, 1, 0, 1); //Yellow
	this->direction = GAME_BLOCK_UP;
}
void Block_O::reset() {
	this->plist[0]->set(0, 0);
	this->plist[1]->set(1, 0);
	this->plist[2]->set(1, 1);
	this->plist[3]->set(0, 1);
	this->direction = GAME_BLOCK_UP;
	this->start.set(GAME_ZONE_COLS / 2 - 1, GAME_ZONE_ROWS);
}

Block_T::Block_T() {
	this->start.set(GAME_ZONE_COLS / 2 - 1, GAME_ZONE_ROWS);
	this->plist[0] = new Position(0, 0);
	this->plist[1] = new Position(1, 0);
	this->plist[2] = new Position(0, 1);
	this->plist[3] = new Position(-1, 0);
	this->outlineColor.setColor(0, 0, 0, 1);
	this->color.setColor(1, 0, 1, 1); //Purple
	this->direction = GAME_BLOCK_UP;
}
void Block_T::reset() {
	this->plist[0]->set(0, 0);
	this->plist[1]->set(1, 0);
	this->plist[2]->set(0, 1);
	this->plist[3]->set(-1, 0);
	this->direction = GAME_BLOCK_UP;
	this->start.set(GAME_ZONE_COLS / 2 - 1, GAME_ZONE_ROWS);
}

Block_S::Block_S() {
	this->start.set(GAME_ZONE_COLS / 2, GAME_ZONE_ROWS);
	this->plist[0] = new Position(0, 0);
	this->plist[1] = new Position(0, 1);
	this->plist[2] = new Position(1, 1);
	this->plist[3] = new Position(-1, 0);
	this->outlineColor.setColor(0, 0, 0, 1);
	this->color.setColor(0, 1, 0, 1); //Purple
	this->direction = GAME_BLOCK_UP;
}
void Block_S::reset() {
	this->plist[0]->set(0, 0);
	this->plist[1]->set(0, 1);
	this->plist[2]->set(1, 1);
	this->plist[3]->set(-1, 0);
	this->direction = GAME_BLOCK_UP;
	this->start.set(GAME_ZONE_COLS / 2, GAME_ZONE_ROWS);
}

Block_Z::Block_Z() {
	this->start.set(GAME_ZONE_COLS / 2 - 1, GAME_ZONE_ROWS);
	this->plist[0] = new Position(0, 0);
	this->plist[1] = new Position(0, 1);
	this->plist[2] = new Position(-1, 1);
	this->plist[3] = new Position(1, 0);
	this->outlineColor.setColor(0, 0, 0, 1);
	this->color.setColor(1, 0, 0, 1); //Purple
	this->direction = GAME_BLOCK_UP;
}
void Block_Z::reset() {
	this->plist[0]->set(0, 0);
	this->plist[1]->set(0, 1);
	this->plist[2]->set(-1, 1);
	this->plist[3]->set(1, 0);
	this->direction = GAME_BLOCK_UP;
	this->start.set(GAME_ZONE_COLS / 2 - 1, GAME_ZONE_ROWS);
}

Block_J::Block_J() {
	this->start.set(GAME_ZONE_COLS / 2 - 1, GAME_ZONE_ROWS);
	this->plist[0] = new Position(0, 0);
	this->plist[1] = new Position(1, 0);
	this->plist[2] = new Position(2, 0);
	this->plist[3] = new Position(0, 1);
	this->outlineColor.setColor(0, 0, 0, 1);
	this->color.setColor(0, 0, 1, 1); //Blue
	this->direction = GAME_BLOCK_UP;
}
void Block_J::reset() {
	this->plist[0]->set(0, 0);
	this->plist[1]->set(1, 0);
	this->plist[2]->set(2, 0);
	this->plist[3]->set(0, 1);
	this->direction = GAME_BLOCK_UP;
	this->start.set(GAME_ZONE_COLS / 2 - 1, GAME_ZONE_ROWS);
}

Block_L::Block_L() {
	this->start.set(GAME_ZONE_COLS / 2 - 1, GAME_ZONE_ROWS);
	this->plist[0] = new Position(0, 0);
	this->plist[1] = new Position(1, 0);
	this->plist[2] = new Position(2, 0);
	this->plist[3] = new Position(2, 1);
	this->outlineColor.setColor(0, 0, 0, 1);
	this->color.setColor(1, 1, 0, 1);
	this->direction = GAME_BLOCK_UP;
}
void Block_L::reset() {
	this->plist[0]->set(0, 0);
	this->plist[1]->set(1, 0);
	this->plist[2]->set(2, 0);
	this->plist[3]->set(2, 1);
	this->direction = GAME_BLOCK_UP;
	this->start.set(GAME_ZONE_COLS / 2 - 1, GAME_ZONE_ROWS);
}
