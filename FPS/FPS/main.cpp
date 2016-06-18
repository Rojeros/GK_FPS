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
void mouseWheel(int button, int dir, int x, int y);
void Mouse(int button, int state, int x, int y);
void Timer(int value);
void Idle();
Weapon* createWeapon(vector<unsigned int> anim,int i);
bool isFired=false;
void Grid();

Player player;
std::vector<Enemy> enemyList;

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
	spawn_points.push_back(vector3d(-2, 3, 4));
	spawn_points.push_back(vector3d(3, 3, 4));
	spawn_points.push_back(vector3d(-4, 3, 4));
	spawn_points.push_back(vector3d(4, 3, 4));
	spawn_points.push_back(vector3d(-2, 3, -4));
	spawn_points.push_back(vector3d(3, 3, -4));
	spawn_points.push_back(vector3d(-4, 3, -4));
	spawn_points.push_back(vector3d(4, 3, -4));

	//unsigned int levelId = objectLoader->load("testowa_scena.obj", &level_collision_planes);
	unsigned int levelId = objectLoader->load("Assets/Scenes/scena4.obj", &level_collision_planes);
	cout << "LEVEL ID: " << levelId << endl;
	levels.push_back(
		new Level(levelId, level_collision_planes, "mapa1", spawn_points)
	);

	vector<unsigned int> anim;
	objectLoader->loadAnimation(anim, "Assets/Weapons/weapon_1/weapon_1", 37);
	Weapon* weapon0= createWeapon(anim,0);

	Player player_t(" ", collisionsphere(vector3d(0, 50, 0), 3), weapon0, 50, 3, 3, 3);
	Weapon* weapon1 = createWeapon(anim, 1);
	Weapon* weapon2 = createWeapon(anim, 2);
	player_t.addWeapon(weapon1);
	player_t.addWeapon(weapon2);
	player = player_t;
	glutSetCursor(GLUT_CURSOR_NONE);
	glutIgnoreKeyRepeat(1);

	glutDisplayFunc(Display);
	glutIdleFunc(Display);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMouseWheelFunc(mouseWheel);
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

	if (enemyList.size() <= 4) {
		enemyList.push_back(Enemy(200, 0.003, 5, collisionsphere(levels[0]->getRandomSpawnPoint(), 1), vector3d(0, 0, 0), player.cam.getLocation()));
	}

	vector<Enemy>::iterator it=enemyList.begin();
	while (it != enemyList.end()) {
		it->update(level_collision_planes, player.cam.getLocation(), player.getCollisionSphere());
		if (it->setAttack(player.getCollisionSphere()))
		{
			player.decreaseHealth(it->getStrength());
		}
		if (it->isDead()) {
			it = enemyList.erase(it);
		}
		else {
			it++;
		}
	}


	vector3d camdirection, direction;
	bool isshot = false;
	if (isFired)
	{
		camdirection = player.getCamera()->getDirectionVector();
		isshot = player.getCurrentWeapon()->fire(direction, camdirection);
		direction.normalize();
		if (isshot)
		{
			vector<Enemy>::iterator it;
			for (it = enemyList.begin(); it != enemyList.end(); ++it) {
				if (collision::raysphere(it->getSphere()->center.x, it->getSphere()->center.y, it->getSphere()->center.z, direction.x, direction.y, direction.z, player.cam.getLocation().x, player.cam.getLocation().y, player.cam.getLocation().z, 2.0))
				{
					it->decreaseHealth(player.getCurrentWeapon()->getPower());
					
				
				}
				cout << player.getCurrentWeapon()->getAmmoClip() << "\n";
				cout << player.getCurrentWeapon()->getAllBullets()<<"\n";
			}
			player.getCurrentWeapon()->nofire();
		}
		else {
			player.getCurrentWeapon()->nofire();
		}

	}
}

void Display(void) {
	//
	glClearColor(0.0, 0.0, 0.0, 1.0); //clear the screen to black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, 640.0 / 480.0, 0.1, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//float col[] = { 0.5,0.5,0.5,1.0 };
	//float amb[] = { 0.3,0.3,0.3,1.0 };
	//glLightfv(GL_LIGHT0,GL_DIFFUSE,col);
	glShadeModel(GL_SMOOTH);

	update();
	glColor3f(0, 1, 0);

	
	levels[0]->show();
	vector<Enemy>::iterator it;
	for (it = enemyList.begin(); it != enemyList.end(); ++it) {
		it->show();
	}
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
			isFired = true;
		}
		if (!g_mouse_left_down) {
			isFired = false;
		}
		if (g_mouse_right_down) {
			//g_camera.Fly(g_translation_speed);
		}
		if (g_key['r'] || g_key['R']) {
			player.getCurrentWeapon()->reload();
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
void mouseWheel(int button, int dir, int x, int y)
{
	if (dir > 0)
	{
		player.changeWeapon(false);
	}
	else
	{
		player.changeWeapon(true);
	}

	return;
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

Weapon* createWeapon(std::vector<unsigned int> anim,int i) {
	if (i == 0) {
		Weapon* weapon = new Weapon("pistol", 150, false, 50, 300, 5, 12, 10, 10);

		weapon->setAnimationFrames(anim);
		weapon->setNormalStateAnimation(1);
		weapon->setFireStateAnimation(16);
		weapon->setReloadStateAnimation(20);
		weapon->setPosition(vector3d(-0.06, 0.13, 0.13));
		weapon->setRotation(vector3d(0, 0, 0));
		weapon->setCurrentPosition(vector3d(-0.06, 0.13, 0.13));
		weapon->setCurrentRotation(vector3d(0, 0, 0));
		weapon->setModelId(anim[0]);


		return weapon;
	}
	if (i == 1) {
		Weapon* weapon = new Weapon("minigun", 1, false, 2, 300, 5, 50, 40, 40);

		weapon->setAnimationFrames(anim);
		weapon->setNormalStateAnimation(1);
		weapon->setFireStateAnimation(16);
		weapon->setReloadStateAnimation(20);
		weapon->setPosition(vector3d(-0.06, 0.13, 0.13));
		weapon->setRotation(vector3d(0, 0, 0));
		weapon->setCurrentPosition(vector3d(-0.06, 0.13, 0.13));
		weapon->setCurrentRotation(vector3d(0, 0, 0));
		weapon->setModelId(anim[0]);


		return weapon;
	}
	else {
		Weapon* weapon = new Weapon("shotgun", 300, false, 200, 20, 2, 2, 10, 10);

		weapon->setAnimationFrames(anim);
		weapon->setNormalStateAnimation(1);
		weapon->setFireStateAnimation(16);
		weapon->setReloadStateAnimation(20);
		weapon->setPosition(vector3d(-0.06, 0.13, 0.13));
		weapon->setRotation(vector3d(0, 0, 0));
		weapon->setCurrentPosition(vector3d(-0.06, 0.13, 0.13));
		weapon->setCurrentRotation(vector3d(0, 0, 0));
		weapon->setModelId(anim[0]);


		return weapon;
	}
}
