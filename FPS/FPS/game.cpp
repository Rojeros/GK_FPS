#include "game.h"


game::game(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutCreateWindow("FPS");

	glutSetCursor(GLUT_CURSOR_NONE);
	glutIgnoreKeyRepeat(1);

	glutDisplayFunc(game::display);
	glutIdleFunc(display);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MouseMotion);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutIdleFunc(Idle);

	glutTimerFunc(1, Timer, 0);
}
game::~game() {

}

void game::start() {

}

void game::display() {
	player->cam->refresh();
}

