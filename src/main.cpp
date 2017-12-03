#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <Windows.h>
//#include <thread>
#include "Constant.hpp"
#include "World.hpp"
//#include "Block.hpp"
#include <mmsystem.h>
//using namespace std;


char NEWGAMETEXT[] = "Press \"N\" to start";
char SCORETEXT[] = "Score ";
char GAMEOVERTEXT[] = "GAME OVER";
char GAMEOVERSCORETEXT[] = "Your Score is ";
char GAMEPAUSETEXT[] = "Pause";
char GAMERESUMEHINTTEXT[] = "Press 'Esc' to resume";
char GAMERESTARTTEXT[] = "Press \"R\" to restart";
char GAMEHIGHSCORETEXT[] = "HighScore ";
char GAMENEXTTEXT[] = "Next";
char GAMEHOLDTEXT[] = "Hold";

int winx = 100, winy = 100;
int GameStatus = GAME_STATUS_NEW;
int KeyDirection = GAME_KEY_NULL;
int Score = 0, HighScore = 0;

World GameWorld;
int GameLevel = GAME_LEVEL_NORMAL;
float moved;

static int oldTime, newTime;
void move() {
	GLfloat speed = 0.1;
	oldTime = clock();
	moved = (newTime - oldTime) * speed;
	newTime = clock();
	oldTime = newTime;
	glutPostRedisplay();
}
/**
 * Function will set up all the text for the program
 */
void setText(void) {

	glColor3f(1.0, 1.0, 1.0);
	char scorechar[6];
	int i, size;
	glRasterPos2i(560, 950); //location of where score appears
	for (i = 0; SCORETEXT[i] != '\0'; i++) { //prints out "Score" text
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, SCORETEXT[i]);
	}
	glRasterPos2i(560, 920);
	sprintf(scorechar, "%d", Score);
	for (i = 0; scorechar[i] != '\0'; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scorechar[i]);
	}
	glRasterPos2i(560, 880);

	for (i = 0; GAMEHIGHSCORETEXT[i] != '\0'; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, GAMEHIGHSCORETEXT[i]);
	}
	glRasterPos2i(560, 850);
	sprintf(scorechar, "%d", HighScore);
	for (i = 0; scorechar[i] != '\0'; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scorechar[i]);
	}
	glRasterPos2i(560, 800);
	for (i = 0; GAMENEXTTEXT[i] != '\0'; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, GAMENEXTTEXT[i]);
	}

	glRasterPos2i(560, 600);
	for (i = 0; GAMENEXTTEXT[i] != '\0'; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, GAMEHOLDTEXT[i]);
	}
	if (GameStatus == GAME_STATUS_NEW) {
		size = length(NEWGAMETEXT);
		glRasterPos2f(GAME_ZONE_WIDTH / 2 - GAME_ZONE_X - size,
		GAME_ZONE_HEIGHT / 2);
		for (i = 0; NEWGAMETEXT[i] != '\0'; i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, NEWGAMETEXT[i]);
		}

	} else if (GameStatus == GAME_STATUS_END) {
		size = length(GAMEOVERTEXT);
		glRasterPos2f(GAME_ZONE_WIDTH / 2 - size * 4,
		GAME_ZONE_HEIGHT / 2 + 30);

		for (i = 0; GAMEOVERTEXT[i] != '\0'; i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, GAMEOVERTEXT[i]);
		}
		size = length(GAMEOVERSCORETEXT);
		glRasterPos2f(GAME_ZONE_WIDTH / 2 - 3 * size, GAME_ZONE_HEIGHT / 2);

		for (i = 0; GAMEOVERSCORETEXT[i] != '\0'; i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,
					GAMEOVERSCORETEXT[i]);
		}
		sprintf(scorechar, "%d", Score);
		for (i = 0; scorechar[i] != '\0'; i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scorechar[i]);
		}
		size = length(GAMERESTARTTEXT);
		glRasterPos2f(GAME_ZONE_WIDTH / 2 - size * 3,
		GAME_ZONE_HEIGHT / 2 - 30);

		for (i = 0; GAMERESTARTTEXT[i] != '\0'; i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, GAMERESTARTTEXT[i]);
		}
	} else if (GameStatus == GAME_STATUS_PAUSE) {
		size = length(GAMEPAUSETEXT);
		glRasterPos2f(GAME_ZONE_WIDTH / 2 - size / 2,
		GAME_ZONE_HEIGHT / 2 + 30);

		for (i = 0; GAMEPAUSETEXT[i] != '\0'; i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, GAMEPAUSETEXT[i]);
		}
		size = length(GAMERESUMEHINTTEXT);
		glRasterPos2f(GAME_ZONE_WIDTH / 2 - 3 * size, GAME_ZONE_HEIGHT / 2);

		for (i = 0; GAMERESUMEHINTTEXT[i] != '\0'; i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,
					GAMERESUMEHINTTEXT[i]);
		}
	}
}

/**
 * New Game setting
 */
void newGame(void) {
	GameStatus = GAME_STATUS_NEW;
	GameWorld.reset();
}

/**
 * Function will draw the game zone border. Default color is white
 */
void drawGameZoneBorder(void) {
	GLint x = GAME_ZONE_X, y = GAME_ZONE_Y;
	glColor3f(1.0, 1.0, 1.0); //Border Color
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex2i(x, y);
	glVertex2i(x + GAME_ZONE_WIDTH, y);
	glVertex2i(x + GAME_ZONE_WIDTH, y);
	glVertex2i(x + GAME_ZONE_WIDTH, y + GAME_ZONE_HEIGHT);
	glVertex2i(x + GAME_ZONE_WIDTH, y + GAME_ZONE_HEIGHT);
	glVertex2i(x, y + GAME_ZONE_HEIGHT);
	glVertex2i(x, y + GAME_ZONE_HEIGHT);
	glVertex2i(x, y);
	glEnd();
}

/**
 * Function will set the windows to the center of the screen according screen resolution
 * if screen_height or screen_width means the resolution cannot get correctly, then the
 * function will not change the default value for window create position
 * @param screen_height
 * 			the height of the current screen, 0 means resolution unavailable
 * @param screen_width
 * 			the width of the current screen, 0 means resolution unavailable
 */
void centerwindow(int screen_height, int screen_width) {
	if (screen_height != 0 && screen_width != 0) {
		winx = screen_width / 2 - WIN_WIDTH / 2;
		winy = screen_height / 2 - WIN_HEIGHT / 2;
	}
}


/**
 * Function will called by glutKeyboardFunc, react for key input (ASCII key)
 * @param key
 * 			the key that the user pressed
 * @param x
 * 			position x of mouse while the key press
 * @param y
 * 			position y of mouse while the key press
 */
void keyFunc(unsigned char key, int x, int y) {
	if (GameStatus == GAME_STATUS_NEW) {
		if (key == 'n' || key == 'N') {
			GameStatus = GAME_STATUS_RUNNING;
		}
	} else if (GameStatus == GAME_STATUS_RUNNING) { //this one pauses
		if (key == 27) { //esc
			GameStatus = GAME_STATUS_PAUSE;
		}
		else if (key == 'S' || key == 's') {
			KeyDirection = GAME_KEY_SWITCH;
		} else if (key == 32) {
			KeyDirection = GAME_KEY_SPACE;
		}
	} else if (GameStatus == GAME_STATUS_PAUSE) { //this one resumes
		if (key == 27) { //escape key
			GameStatus = GAME_STATUS_RUNNING;
		}
	} else if (GameStatus == GAME_STATUS_END) {
		if (key == 'r' || key == 'R') { //restart
			GameStatus = GAME_STATUS_NEW;
		}
	}
}
/**
 * Function will called by glutSpecialFunc, react for special key input (Non-ASCII)
 * @param key
 * 			the key that the user pressed
 * @param x
 * 			position x of mouse while the key press
 * @param y
 * 			position y of mouse while the key press
 */
void specialFunc(int key, int x, int y) {
	if (GameStatus == GAME_STATUS_NEW) {

	} else if (GameStatus == GAME_STATUS_RUNNING) {
		if (key == GLUT_KEY_LEFT) {
			KeyDirection = GAME_KEY_LEFT;
		} else if (key == GLUT_KEY_RIGHT) {
			KeyDirection = GAME_KEY_RIGHT;
		} else if (key == GLUT_KEY_UP) {
			KeyDirection = GAME_KEY_UP;
		} else if (key == GLUT_KEY_DOWN) {
			KeyDirection = GAME_KEY_DOWN;
		}
	} else if (GameStatus == GAME_STATUS_PAUSE) {

	} else if (GameStatus == GAME_STATUS_END) {

	}
}

/**
 * Function for main menu
 * @param option
 */
void mainMenu(GLint option) {
	switch (option) {
	case 1: {
		newGame();
		break;
	}
	case 2: {
		exit(0);
	}
	case 3: {
		printf("Jokes");
	}
	}
}

/**
 * Set up menu
 */
void Menu(void) {

	glutCreateMenu(mainMenu);
	glutAddMenuEntry(" New Game", 1);
	glutAddMenuEntry(" Exit Game", 2);
	glutAddMenuEntry("Your beautiful", 3);
}
/**
 * Display function
 */
void display(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	GameWorld.draw();
	setText();
	drawGameZoneBorder();
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}
void play_music() {
	PlaySound((LPCSTR) "Tetris.wav", NULL,
			SND_FILENAME | SND_ASYNC | SND_LOOP);
//	int test = 0;
//	cin >> test;

	//code from jerry
//	PlaySound((LPCSTR) "Background.wav", NULL,
//		SND_FILENAME | SND_ASYNC | SND_LOOP);

}
int main(int argc, char** argv) {
	play_music();
	setvbuf(stdout, NULL, _IONBF, 0);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	centerwindow(glutGet(GLUT_SCREEN_HEIGHT), glutGet(GLUT_SCREEN_WIDTH));
	glutInitWindowPosition(winx, winy);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutCreateWindow(WIN_TITLE);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, WIN_WIDTH, 0.0, WIN_HEIGHT);
	Menu();
	glutKeyboardFunc(keyFunc);
	glutSpecialFunc(specialFunc);
	glutDisplayFunc(display);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutMainLoop();

	return 0;
}
