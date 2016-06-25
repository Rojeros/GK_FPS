#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>
#include"camera.h"
#include"player.h"
#include "collisionplane.h"
#include "objectloader.h"
#include "level.h"
#include "enemy.h"
#include "text.h"
#include "item.h"

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
void calculateFPS();
Weapon* createWeapon(vector<unsigned int> anim, int i);
bool isFired = false;
void Grid();
Player player;
std::vector<Enemy> enemyList;
text informations;

bool g_key[256];
bool g_shift_down = false;
int g_viewport_width = 0;
int g_viewport_height = 0;
bool g_mouse_left_down = false;
bool g_mouse_right_down = false;

bool level_start = false;

vector<Level*> levels;
int currentLevel = 0;
std::vector<collisionplane> level1_collision_planes;
std::vector<collisionplane> level2_collision_planes;


// Movement settings
const float g_translation_speed = 0.2;
const float g_rotation_speed = M_PI / 180 * 0.2;

//  The number of frames
int frameCount = 0;

//  Number of frames per second
float fpsCount = 0;

//  currentTime - previousTime is the time elapsed
//  between every call of the Idle function
int currentTime = 0, previousTime = 0;

//vector3d a(0, 0, 0);
//vector3d b(0, 0, 0);
item bonuses;

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
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
	unsigned int levelId = objectLoader->load("Assets/Scenes/level_1/level1.obj", &level1_collision_planes);
	unsigned int levelId2 = objectLoader->load("Assets/Scenes/scena4.obj", &level2_collision_planes);

	//level adding
	cout << "LEVEL ID: " << levelId << endl;
	levels.push_back(
		new Level(levelId, level1_collision_planes, "mapa1", spawn_points, vector3d(-3, 5, -4), vector3d(-9, 1, -4)));
	levels.push_back(
		new Level(levelId2, level2_collision_planes, "mapa2", spawn_points, vector3d(3, 5, 4), vector3d(9, 1, 4))
		);

	vector<unsigned int> anim;
	objectLoader->loadAnimation(anim, "Assets/Weapons/pistol/pistol", 47);
	Weapon* weapon0 = createWeapon(anim, 0);

	Player player_t(" ", collisionsphere(vector3d(0, 5, 0), 3), weapon0, 1500, 3, 3, 3);

	//weapons for player
	vector<unsigned int> anim2;
	objectLoader->loadAnimation(anim2, "Assets/Weapons/minigun/minigun", 37);
	Weapon* weapon1 = createWeapon(anim2, 1);

	vector<unsigned int> anim3;
	objectLoader->loadAnimation(anim3, "Assets/Weapons/shotgun/shotgun", 37);
	Weapon* weapon2 = createWeapon(anim3, 2);
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

	//ending platform for first level
	bonuses.add(kind::finish, collisionsphere(levels[currentLevel]->getEndPoint(), 0.1), vector3d(0, 0, 0), vector3d(0, 0, 0), vector3d(1, 0.1, 1));




	glutTimerFunc(100, Timer, 0);
	//sglutTimerFunc(1000/60, Display);
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

	//check player status
	if (player.isDead()) {
	//	informations.displayDiffrentText("GAME OVER", g_viewport_width, g_viewport_height, 1.2, CENTER, 1, vector3d(1, 0, 0));
		if (isFired)
			player.resetPlayer();
	}
	else if (levels[currentLevel]->isEnd()) {		//player end level?
		//display information
		informations.displayDiffrentText("LEVEL SUCCES", g_viewport_width, g_viewport_height, 1.2, CENTER, 1, vector3d(0, 0, 1));
		//wait for fire buttion
		if (isFired) {
			levels[currentLevel]->setEnd(false);
			if (levels.size() > currentLevel + 1) {		//next level
				currentLevel++;
			}
			else {
				currentLevel = 0;
			}
				
			player.setStartPosition(levels[currentLevel]->getPlayerSpawnPoint());	//new position for player on next level
			int p = player.getPoints();	//save results
			player.resetPlayer();
			player.addPoints(p);
			bonuses.clear();		//clear current level
			enemyList.clear();
			//new end platform on next level
			bonuses.add(kind::finish, collisionsphere(levels[currentLevel]->getEndPoint(), 0.5), vector3d(0, 0, 0), vector3d(0, 0, 0), vector3d(1, 0.1, 1));
		
		}
	}
	else {		//normal update for everything
		player.update(levels[currentLevel]->getCollisionPlanes());

		if (enemyList.size() <= 4) {
			enemyList.push_back(Enemy(200, 0.03, 5,100, collisionsphere(levels[currentLevel]->getRandomSpawnPoint(), 1), vector3d(0, 0, 0), player.cam.getLocation()));
		}

		vector<Enemy>::iterator it = enemyList.begin();
		while (it != enemyList.end()) {
			it->update(levels[currentLevel]->getCollisionPlanes(), player.cam.getLocation(), player.getCollisionSphere());
			if (it->setAttack(player.getCollisionSphere()))
			{
				player.decreaseHealth(it->getStrength());
			}
			if (it->isDead()) {
				player.addPoints(5);

				//add ammo or  health bonus 
				int g = rand() % 10;
				if (g == 1)
					bonuses.add(kind::ammo, collisionsphere(it->getSphere()->center, 1.0));
				else if (g == 2)
					bonuses.add(kind::health, collisionsphere(it->getSphere()->center, 1.0));

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
				//		a = direction;
				//		b = player.getCamera()->getLocation();
				vector<Enemy>::iterator it;
				for (it = enemyList.begin(); it != enemyList.end(); ++it) {
					if (collision::raysphere(it->getSphere()->center.x, it->getSphere()->center.y, it->getSphere()->center.z, direction.x, direction.y, direction.z, player.cam.getLocation().x, player.cam.getLocation().y, player.cam.getLocation().z, it->getSphere()->r))
					{
						it->decreaseHealth(player.getCurrentWeapon()->getPower());


					}
				}
				player.getCurrentWeapon()->nofire();
			}
			else {
				player.getCurrentWeapon()->nofire();
			}

		}

		//check bonuses and finish level
		int h = bonuses.update(player.getCollisionSphere());
		switch (h) {
		case -1:
			break;
		case kind::ammo:

			player.getRandomWeapon()->addAllBullets(50);
			break;
		case kind::health:
			player.setHealth(player.getHealth() + 500);
			break;
		case kind::finish:	//new level
			levels[currentLevel]->setEnd(true);
			break;
		}
	}
}

void Display(void) {
	update();
	glClearColor(0.0, 0.0, 0.0, 1.0); //clear the screen to black
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
	glClearDepth(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	gluPerspective(45, 640.0 / 480.0, 0.1, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	


	glEnable(GL_TEXTURE_2D);
	//glShadeModel(GL_SMOOTH);
	


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat lightpos[] = { .5, 1., 1., 0. };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	GLfloat cyan[] = { 1.f, .8f, .8f, 1.f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);

	bonuses.show();

	player.show();
	
	levels[currentLevel]->show();
	vector<Enemy>::iterator it;
	for (it = enemyList.begin(); it != enemyList.end(); ++it) {
		it->show();
	}
	
	//level_start = true;
	
	//Grid();
	
	

	glClear(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	informations.showTextInfo(player.getHealth(), player.getCurrentWeapon()->getAmmoClip(), player.getCurrentWeapon()->getAllBullets(), 0, player.getAllWeapon(), player.getIntCurrentWeapon(), player.getPoints(), g_viewport_width, g_viewport_height, levels[currentLevel]->getName());
	informations.displayDiffrentText("FPS: " + std::to_string((int)(fpsCount)), g_viewport_width, g_viewport_height, 10, NW, -2, vector3d(0.8, 0.8, 0.8));
	if (player.isDead()) 
		informations.displayDiffrentText("GAME OVER", g_viewport_width, g_viewport_height, 1.2, CENTER, 1, vector3d(1, 0, 0));
	if (levels[currentLevel]->isEnd()) 		//player end level?
		informations.displayDiffrentText("LEVEL SUCCES", g_viewport_width, g_viewport_height, 1.2, CENTER, 1, vector3d(0, 0, 1));//display information

	

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

int time = 0;
int z = 0;
void Timer(int value)
{

		if (g_key['w'] || g_key['W']) {
			z++;
			std::cout << "WWWW " << z << std::endl;
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

		if (g_key[32]) {
			if (time < 6) {
				player.cam.fly(0.6);
				time++;
			}
			
		}
		else {
			time = 0;
		}

		if (g_key['r'] || g_key['R']) {
			player.getCurrentWeapon()->reload();
		}
		Weapon* weapon = player.getCurrentWeapon();

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
		}
		

		
	
	
	glutTimerFunc(1000/60, Timer, 0);
}

void Idle()
{
	Display();
	calculateFPS();
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
		Weapon* weapon = new Weapon("pistol", 30, false, 50, 300, 5, 12, 1000, 1000);

		weapon->setAnimationFrames(anim);
		weapon->setNormalStateAnimation(1);
		weapon->setFireStateAnimation(15);
		weapon->setReloadStateAnimation(31);
		weapon->setPosition(vector3d(-0.06, 0.13, 0.13));
		weapon->setRotation(vector3d(0, 0, 0));
		weapon->setCurrentPosition(vector3d(-0.06, 0.13, 0.13));
		weapon->setCurrentRotation(vector3d(0, 0, 0));
		weapon->setModelId(anim[0]);


		return weapon;
	}
	if (i == 1) {
		Weapon* weapon = new Weapon("minigun", 10, false, 5, 500, 5, 100, 80, 80);

		weapon->setAnimationFrames(anim);
		weapon->setNormalStateAnimation(1);
		weapon->setFireStateAnimation(15);
		weapon->setReloadStateAnimation(20);
		weapon->setPosition(vector3d(-0.06, 0.13, 0.13));
		weapon->setRotation(vector3d(0, 0, 0));
		weapon->setCurrentPosition(vector3d(-0.06, 0.13, 0.13));
		weapon->setCurrentRotation(vector3d(0, 0, 0));
		weapon->setModelId(anim[0]);


		return weapon;
	}
	else {
		Weapon* weapon = new Weapon("shotgun", 50, false, 200, 20, 2, 2, 20, 20);

		weapon->setAnimationFrames(anim);
		weapon->setNormalStateAnimation(1);
		weapon->setFireStateAnimation(15);
		weapon->setReloadStateAnimation(20);
		weapon->setPosition(vector3d(-0.06, 0.13, 0.13));
		weapon->setRotation(vector3d(0, 0, 0));
		weapon->setCurrentPosition(vector3d(-0.06, 0.13, 0.13));
		weapon->setCurrentRotation(vector3d(0, 0, 0));
		weapon->setModelId(anim[0]);


		return weapon;
	}
}

void calculateFPS()
{
	//  Increase frame count
	frameCount++;

	//  Get the number of milliseconds since glutInit called 
	//  (or first call to glutGet(GLUT ELAPSED TIME)).
	currentTime = glutGet(GLUT_ELAPSED_TIME);

	//  Calculate time passed
	int timeInterval = currentTime - previousTime;

	if (timeInterval > 1000)
	{
		//  calculate the number of frames per second
		fpsCount = frameCount / (timeInterval / 1000.0f);

		//  Set time
		previousTime = currentTime;

		//  Reset frame count
		frameCount = 0;
	}
}
