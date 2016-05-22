#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>
#include"camera.h"
#include"player.h"
#include "collisionplane.h"
#include "objectloader.h"
#include "level.h"


#define M_PI 1.57079632679489661923

using namespace std;

void Display();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void MouseMotion(int x, int y);
void Mouse(int button, int state, int x, int y);
void Timer(int value);
void Idle();

void Grid();

//player gramy(" ",3,3,3);
Player player(" ", collisionsphere(vector3d(0, 50, 0), 3.0), 50, 3, 3, 3);
bool g_key[256];
bool g_shift_down = false;
int g_viewport_width = 0;
int g_viewport_height = 0;
bool g_mouse_left_down = false;
bool g_mouse_right_down = false;

bool level_start = false;

vector<Level*> levels;
std::vector<collisionplane> level_collision_planes;

// Movement settings
const float g_translation_speed = 0.05;
const float g_rotation_speed = M_PI / 180 * 0.2;

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("FPS");
	ObjectLoader* objectLoader = new ObjectLoader();
	std::vector<vector3d> spawn_points;
	spawn_points.push_back(vector3d(2, 3, 4));
	//unsigned int levelId = objectLoader->load("testowa_scena.obj", &level_collision_planes);
	unsigned int levelId = objectLoader->load("scena2.obj", &level_collision_planes);
	cout << "LEVEL ID: " << levelId << endl;
	levels.push_back(
		new Level(levelId, level_collision_planes, "mapa1", spawn_points)
	);

	glutSetCursor(GLUT_CURSOR_NONE);
	glutIgnoreKeyRepeat(1);

	glutDisplayFunc(Display);
	glutIdleFunc(Display);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MouseMotion);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutIdleFunc(Idle);

	glutTimerFunc(100, Timer, 0);
	glutMainLoop();

	
	

	return 0;
}

void Grid()
{
	glPushMatrix();
	glColor3f(1, 1, 1);

	for (int i = -50; i < 50; i++) {
		glBegin(GL_LINES);
		glVertex3f(i, 0, -50);
		glVertex3f(i, 0, 50);
		glEnd();
	}

	for (int i = -50; i < 50; i++) {
		glBegin(GL_LINES);
		glVertex3f(-50, 0, i);
		glVertex3f(50, 0, i);
		glEnd();
	}

	glPopMatrix();
}

void update(void) {
	player.update(level_collision_planes);

}

void Display(void) {
	//
	glClearColor(0.0, 0.0, 0.0, 1.0); //clear the screen to black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
	glLoadIdentity();
	update();
	glColor3f(0, 1, 0);
	levels[0]->show();
		
		//level_start = true;
	
	Grid();

	glutSwapBuffers(); //swap the buffers
}

void Reshape(int w, int h) {
	g_viewport_width = w;
	g_viewport_height = h;

	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
	glMatrixMode(GL_PROJECTION); //set the matrix to projection

	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 100.0); //set the perspective (angle of sight, width, height, ,depth)
	glMatrixMode(GL_MODELVIEW); //set the matrix back to model
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 27) {
		exit(0);
	}


	glutWarpPointer(g_viewport_width / 2, g_viewport_height / 2);
	
		
	if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
		g_shift_down = true;
	}
	else {
		g_shift_down = false;
	}

	g_key[key] = true;
}

void KeyboardUp(unsigned char key, int x, int y)
{
	g_key[key] = false;
}

void Timer(int value)
{

		if (g_key['w'] || g_key['W']) {
			if(!player.isWallCollision() && player.isGroundCollision())
				player.cam.move(g_translation_speed);
		}
		 if (g_key['s'] || g_key['S']) {
			 if (!player.isWallCollision() && player.isGroundCollision())
				player.cam.move(-g_translation_speed);
		}
		 if (g_key['d'] || g_key['D']) {
			 if (!player.isWallCollision() && player.isGroundCollision())
				player.cam.strafe(g_translation_speed);
		}
		if (g_key['a'] || g_key['A']) {
			if (!player.isWallCollision() && player.isGroundCollision())
				player.cam.strafe(-g_translation_speed);

		}
		if (g_mouse_left_down) {
			//g_camera.Fly(-g_translation_speed);
		}
		if (g_mouse_right_down) {
			//g_camera.Fly(g_translation_speed);
		}

		
	

	glutTimerFunc(5, Timer, 0);
}

void Idle()
{
	Display();
}

void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			g_mouse_left_down = true;
		}
		else if (button == GLUT_RIGHT_BUTTON) {
			g_mouse_right_down = true;
		}
	}
	else if (state == GLUT_UP) {
		if (button == GLUT_LEFT_BUTTON) {
			g_mouse_left_down = false;
		}
		else if (button == GLUT_RIGHT_BUTTON) {
			g_mouse_right_down = false;
		}
	}
}

void MouseMotion(int x, int y)
{
	// This variable is hack to stop glutWarpPointer from triggering an event callback to Mouse(...)
	// This avoids it being called recursively and hanging up the event loop
	static bool just_warped = false;

	if (just_warped) {
		just_warped = false;
		return;
	}


		int dx = x - g_viewport_width / 2;
		int dy = y - g_viewport_height / 2;

		if (dx) {
			player.cam.rotateYaw(g_rotation_speed*dx);
		}

		if (dy) {
			player.cam.rotatePitch(g_rotation_speed*(-dy));
		}

		glutWarpPointer(g_viewport_width / 2, g_viewport_height / 2);

		just_warped = true;
	
}
