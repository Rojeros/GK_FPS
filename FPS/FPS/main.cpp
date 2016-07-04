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
#include "Effects.h"
#include "FpsTimer.h"

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
void processKeyboard(void);
void processMouse(void);
Weapon* createWeapon(vector<unsigned int> anim, int i);
bool isFired = false;
void Grid();
Player player;
std::vector<Enemy> enemyList;
text informations;
Effects effects;

bool g_key[256];
bool g_shift_down = false;
int g_viewport_width = 0;
int g_viewport_height = 0;
bool g_mouse_left_down = false;
bool g_mouse_right_down = false;
bool rain = false;

bool level_start = false;

vector<Level*> levels;
int currentLevel = 0;
std::vector<collisionplane> level1_collision_planes;
std::vector<collisionplane> level2_collision_planes;
FpsTimer* timer = new FpsTimer(40);
const GLfloat specStrength = 20.0;

// Movement settings
const float g_translation_speed = 0.5;
const float g_rotation_speed = M_PI / 180 * 0.2;

item bonuses;
vector<unsigned int> enemyAnimation;
std::vector<collisionplane> enemy_collision_planes;
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("FPS");
	ObjectLoader* objectLoader = new ObjectLoader();
	std::vector<vector3d> spawn_points;
	spawn_points.push_back(vector3d(-6, 3, 4));
	spawn_points.push_back(vector3d(10, 3, 4));
	spawn_points.push_back(vector3d(-10, 3, 7));
	spawn_points.push_back(vector3d(7, 3, 16));
	spawn_points.push_back(vector3d(-5, 3, -14));
	spawn_points.push_back(vector3d(7, 3, -6));
	spawn_points.push_back(vector3d(-14, 3, -4));
	spawn_points.push_back(vector3d(18, 3, -4));

	std::vector<vector3d> spawn_points2;
	spawn_points2.push_back(vector3d(-26, 3, 4));
	spawn_points2.push_back(vector3d(10, 3, 15));
	spawn_points2.push_back(vector3d(-30, 3, 7));
	spawn_points2.push_back(vector3d(57, 3, 16));
	spawn_points2.push_back(vector3d(-15, 3, -14));
	spawn_points2.push_back(vector3d(37, 3, -6));
	spawn_points2.push_back(vector3d(-24, 3, -24));
	spawn_points2.push_back(vector3d(48, 3, -34));
	spawn_points2.push_back(vector3d(-126, 3, 44));
	spawn_points2.push_back(vector3d(100, 3, 55));
	spawn_points2.push_back(vector3d(-130, 3, 117));
	spawn_points2.push_back(vector3d(157, 3, 166));
	spawn_points2.push_back(vector3d(-135, 3, -134));
	spawn_points2.push_back(vector3d(376, 3, -66));
	spawn_points2.push_back(vector3d(-244, 3, -244));
	spawn_points2.push_back(vector3d(248, 3, -340));
	
	effects.setObjectLoader(objectLoader);
	

	//unsigned int levelId = objectLoader->load("testowa_scena.obj", &level_collision_planes);
	unsigned int levelId = objectLoader->load("Assets/Scenes/level_1/level1.obj", &level1_collision_planes);
	unsigned int levelId2 = objectLoader->load("Assets/Scenes/level_2/level_2.obj", &level2_collision_planes);

	//level adding
	levels.push_back(
		new Level(levelId, level1_collision_planes, "mapa1", spawn_points, vector3d(-3, 5, -4), vector3d(-9, 1, -4),95,95));
	levels.push_back(
		new Level(levelId2, level2_collision_planes, "mapa2", spawn_points2, vector3d(3, 5, 4), vector3d(9, 1, 4),35,35)
		);

	vector<unsigned int> anim;
	objectLoader->loadAnimation(anim, "Assets/Weapons/pistol/pistol", 47, NULL);
	Weapon* weapon0 = createWeapon(anim, 0);

	Player player_t(" ", collisionsphere(vector3d(0, 5, 0), 3), weapon0, 1500, 3, 3, 3);

	//weapons for player
	vector<unsigned int> anim2;
	objectLoader->loadAnimation(anim2, "Assets/Weapons/ak/ak", 47, NULL);
	Weapon* weapon1 = createWeapon(anim2, 1);

	vector<unsigned int> anim3;
	objectLoader->loadAnimation(anim3, "Assets/Weapons/shotgun/shotgun", 37, NULL);
	Weapon* weapon2 = createWeapon(anim3, 2);
	player_t.addWeapon(weapon1);
	player_t.addWeapon(weapon2);

	objectLoader->loadAnimation(enemyAnimation, "Assets/Creatures/MagmaElemental_1", 40, &enemy_collision_planes);

	effects.initEffects(levels[currentLevel]->getWidth(), levels[currentLevel]->getHeight());
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

	Timer(0);
	//sglutTimerFunc(1000/60, Display);
	glutMainLoop();


	effects.delEffects();

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

int jumpTime = 0;
int z = 0;

void processKeyboard(void)
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

	if (g_key[32]) {
		if (jumpTime < 12) {
			player.cam.fly(0.6);
			jumpTime++;
		}

	}
	else {
		jumpTime = 0;
	}

	if (g_key['r'] || g_key['R']) {
		player.getCurrentWeapon()->reload();
	}
	if (g_key['1']) {
		effects.rain = true;
	}

	if (g_key['2']) {
		effects.rain = false;
	}
}


void processMouse(void) 
{
	
	if (g_mouse_left_down) {
		isFired = true;
	}
	if (!g_mouse_left_down) {
		isFired = false;
	}
	if (g_mouse_right_down) {
		//g_camera.Fly(g_translation_speed);
	}
}

void update(void) {

	processKeyboard();
	processMouse();
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
			effects.delEffects();
			effects.initEffects(levels[currentLevel]->getWidth(), levels[currentLevel]->getHeight());
			//new end platform on next level
			bonuses.add(kind::finish, collisionsphere(levels[currentLevel]->getEndPoint(), 1), vector3d(0, 0, 0), vector3d(0, 0, 0), vector3d(1, 0.1, 1));
		
		}
	}
	else {		//normal update for everything
		player.update(levels[currentLevel]->getCollisionPlanes());

		if (enemyList.size() <= 6) {
			vector3d spawn = levels[currentLevel]->getRandomSpawnPoint();
			std::cout << spawn.x << " " << spawn.y << " " << spawn.z << std::endl;
			enemyList.push_back(Enemy(enemyAnimation, 200, 0.3, 15,100, collisionsphere(spawn, 4), vector3d(0, 0, 0), player.cam.getLocation(), enemy_collision_planes));
			
			effects.teleportEnemy(vector3d(spawn.x, spawn.y-4, spawn.z), 4,50);

		}

		vector<Enemy>::iterator it = enemyList.begin();
		while (it != enemyList.end()) {
			it->update(levels[currentLevel]->getCollisionPlanes(), player.cam.getLocation(), player.getCollisionSphere());
			if (it->setAttack(player.getCollisionSphere()))
			{
				player.decreaseHealth(it->getStrength());
			}
			if (it->isDead()) {
				if(it->getDeadTimer()==1)
					effects.destroyEnemy(vector3d(it->getSphere()->center.x, it->getSphere()->center.y- it->getSphere()->r, it->getSphere()->center.z),50);
				if(it->deadTimerTick()){
				player.addPoints(5);

				//add ammo or  health bonus 
				int g = rand() % 10;
				if (g == 1)
					bonuses.add(kind::ammo, collisionsphere(vector3d(it->getSphere()->center.x, it->getSphere()->center.y-it->getSphere()->r, it->getSphere()->center.z), 1.0));
				else if (g == 2)
					bonuses.add(kind::health, collisionsphere(vector3d(it->getSphere()->center.x, it->getSphere()->center.y - it->getSphere()->r, it->getSphere()->center.z), 1.0));

				it = enemyList.erase(it);
				}
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
					float dist=0;
					vector3d point=vector3d(0,0,0);
					
					if (collision::raysphere(it->getSphere()->center.x, it->getSphere()->center.y-it->getSphere()->r, it->getSphere()->center.z, direction.x, direction.y, direction.z, player.cam.getLocation().x, player.cam.getLocation().y, player.cam.getLocation().z, it->getSphere()->r,&dist,&point))
					{
						it->decreaseHealth(player.getCurrentWeapon()->getPower());
					}
			//		else
			//		{
			//			std::vector<collisionplane> cp = it->getCollisionPlanes();
			//			for (int i = 0; i < cp.size(); i++)
			//			{
			//				if (collision::rayplane(cp[i].normal.x, cp[i].normal.y, cp[i].normal.z, cp[i].p[0].x, cp[i].p[0].y, cp[i].p[0].z, direction.x, direction.y, direction.z, -cp[i].normal.x, -cp[i].normal.y, -cp[i].normal.z, cp[i].p[0], cp[i].p[1], cp[i].p[2], cp[i].p[3], &dist, &point))
			//				{
			//					it->decreaseHealth(player.getCurrentWeapon()->getPower());
			//					break;

			//				}
			//			}
			//		}



					effects.addBullet(player.cam.getLocation(), point, direction, 100, 0.5,dist);
				}
				player.getCurrentWeapon()->nofire();
			}
			else {
				player.getCurrentWeapon()->nofire();
			}

		}

		effects.update();
	
		if (player.getPoints() >= 100) {
			player.addPoints(-player.getPoints());
			levels[currentLevel]->setEnd(true);
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
			if (player.getPoints() >= 100) {
				player.addPoints(-player.getPoints());
				levels[currentLevel]->setEnd(true);
			}
			break;
		}
	}
}

void Display(void) {
	update();
	timer->timeFrame();

	glClearColor(0.0, 0.0, 0.0, 1.0); //clear the screen to black
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
	glClearDepth(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	

	gluPerspective(45, 640.0 / 480.0, 0.1, 500.0);
	glMatrixMode(GL_MODELVIEW); 
	glEnable(GL_DEPTH_TEST); // Disables Depth Testing
	glEnable(GL_TEXTURE_2D); 
	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);                         // Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);                  // Type Of Blending To Perform
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);           // Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);                 // Really Nice Point Smoothing

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//defining global ambient
	GLfloat global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	// Create light components
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
	GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat position[] = { -1.5f, 4.0f, 4.0f, 1.0f };

	// Assign created components to GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	float specReflection[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);
	glMateriali(GL_FRONT, GL_SHININESS, 96);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
	bonuses.show();

	player.show();
	
	levels[currentLevel]->show();
	vector<Enemy>::iterator it;
	for (it = enemyList.begin(); it != enemyList.end(); ++it) {
		it->show();
	}

	glClear(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_LIGHTING);
	informations.showTextInfo(player.getHealth(), player.getCurrentWeapon()->getAmmoClip(), player.getCurrentWeapon()->getAllBullets(), 0, player.getAllWeapon(), player.getIntCurrentWeapon(), player.getPoints(), g_viewport_width, g_viewport_height, levels[currentLevel]->getName());
	informations.displayDiffrentText("FPS: " + timer->getFps(), g_viewport_width, g_viewport_height, 10, NW, -2, vector3d(0.8, 0.8, 0.8));
	if (player.isDead()) 
		informations.displayDiffrentText("GAME OVER", g_viewport_width, g_viewport_height, 1.2, CENTER, 1, vector3d(1, 0, 0));
	if (levels[currentLevel]->isEnd()) 		//player end level?
		informations.displayDiffrentText("LEVEL SUCCES", g_viewport_width, g_viewport_height, 1.2, CENTER, 1, vector3d(0, 0, 1));//display information


	
	effects.display();
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
	glutPostRedisplay();
	Sleep(1000 / 60);
	glutTimerFunc(1, Timer, 0);

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
		Weapon* weapon = new Weapon("AK", 10, false, 15, 500, 5, 100, 80, 80);

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
