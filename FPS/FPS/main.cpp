#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>
#include"camera.h"
#include"player.h"
#include "collisionplane.h"
#include "objectloader.h"
#include "level.h"
#include "enemy.h"

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
Weapon* createWeapon(vector<unsigned int> anim);

void Grid();

Player player;
Enemy enemy(200, 0.01, 5, collisionsphere(vector3d(10, 50, 10), 2), vector3d(0, 0, 0), player.cam.getLocation());

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
const float g_translation_speed = 0.1;
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
	unsigned int levelId = objectLoader->load("Assets/Scenes/scena3.obj", &level_collision_planes);
	cout << "LEVEL ID: " << levelId << endl;
	levels.push_back(
		new Level(levelId, level_collision_planes, "mapa1", spawn_points)
	);

	vector<unsigned int> anim;
	objectLoader->loadAnimation(anim, "Assets/Weapons/weapon_1/weapon_1", 37);
	Weapon* weapon = createWeapon(anim);

	Player player_t(" ", collisionsphere(vector3d(0, 50, 0), 2), weapon, 50, 3, 3, 3);
	player = player_t;
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
	enemy.update(level_collision_planes, player.cam.getLocation());
	
}

void Display(void) {
	//
	glClearColor(0.0, 0.0, 0.0, 1.0); //clear the screen to black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
	glLoadIdentity();
	update();
	glColor3f(0, 1, 0);

	
	levels[0]->show();
	enemy.show();
	player.show();	
		
		//level_start = true;
	
	//Grid();

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
				player.cam.move(g_translation_speed);
		}
		 if (g_key['s'] || g_key['S']) {
				player.cam.move(-g_translation_speed);
		}
		 if (g_key['d'] || g_key['D']) {
				player.cam.strafe(g_translation_speed);
		}
		if (g_key['a'] || g_key['A']) {
				player.cam.strafe(-g_translation_speed);

		}
		if (g_mouse_left_down) {
			//g_camera.Fly(-g_translation_speed);
		}
		if (g_mouse_right_down) {
			//g_camera.Fly(g_translation_speed);
		}

		/*Weapon* weapon = player.getCurrentWeapon();

			if (weapon != NULL) {
				if (g_key['i'] || g_key['I'])
				{

					weapon->test('i');
				}
				else if (g_key['k'] || g_key['K']) {
					weapon->test('k');
				}
				else if (g_key['j'] || g_key['J']) {
					weapon->test('j');
				}
				else if (g_key['l'] || g_key['L']) {
					weapon->test('l');
				}
				else if (g_key['u'] || g_key['U']) {
					weapon->test('u');
				}
				else if (g_key['o'] || g_key['O'])
				{
					weapon->test('o');
				}
		}*/
		

		
	

	glutTimerFunc(10, Timer, 0);
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

Weapon* createWeapon(std::vector<unsigned int> anim) {
	Weapon* weapon = new Weapon();

	weapon->setAnimationFrames(anim);
	weapon->setNormalStateAnimation(1);
	weapon->setFireStateAnimation(16);
	weapon->setReloadStateAnimation(20);
	weapon->setPosition(vector3d(-0.06, 0.13, 0.13));
	weapon->setRotation(vector3d(0, 0, 0));
	weapon->setCurrentPosition(vector3d(-0.06, 0.13, 0.13));
	weapon->setCurrentRotation(vector3d(0, 0, 0));
	weapon->setModelId(anim[0]);
	weapon->setAllBullets(300);
	weapon->setMaxMagazineBullets(30);

	return weapon;

}
