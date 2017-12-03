#ifndef SRC_CONSTANT_HPP_
#define SRC_CONSTANT_HPP_

#define length(a) sizeof(a)/sizeof(a[0])

// Windows Size
#define WIN_WIDTH				700
#define WIN_HEIGHT				1050
#define WIN_TITLE				"Tetris"

// Game Zone Start Position
#define GAME_ZONE_X				25
#define GAME_ZONE_Y				23

// Block Size
#define GAME_BLOCK_SIZE			50

//Game Zone Size
#define GAME_ZONE_WIDTH			500
#define GAME_ZONE_HEIGHT		1000
#define GAME_ZONE_COLS			GAME_ZONE_WIDTH/GAME_BLOCK_SIZE
#define GAME_ZONE_ROWS			GAME_ZONE_HEIGHT/GAME_BLOCK_SIZE

// Game Status
#define GAME_STATUS_NEW			0
#define GAME_STATUS_RUNNING 	1
#define GAME_STATUS_END			2
#define GAME_STATUS_PAUSE		3

// Game Level
#define GAME_LEVEL_EASY			0
#define GAME_LEVEL_NORMAL		1
#define GAME_LEVEL_HARD			2
#define GAME_LEVEL_EXPERT		3

// Game Key
#define GAME_KEY_NULL			0
#define GAME_KEY_UP				1
#define GAME_KEY_LEFT			2
#define GAME_KEY_RIGHT			3
#define GAME_KEY_DOWN			4
#define GAME_KEY_SWITCH			5
#define GAME_KEY_SPACE			6

// Block Direction
#define GAME_BLOCK_UP			0
#define GAME_BLOCK_RIGHT		1
#define GAME_BLOCK_DOWN			2
#define GAME_BLOCK_LEFT			3

#endif /* SRC_CONSTANT_HPP_ */
