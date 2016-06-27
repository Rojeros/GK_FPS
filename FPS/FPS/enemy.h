#ifndef ENEMY_H
#define ENEMY_H
#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "vector.h"
#include "collisionsphere.h"
#include "collisionplane.h"
#include "collision.h"
#include <string>
#include <vector>

#define M_PI 1.57079632679489661923

class Enemy : private collision
{
	static std::vector<unsigned int> frames;
	std::vector<collisionplane> collisionPlanes;
	static unsigned int walk;
	static unsigned int attack;
	static unsigned int die;
	unsigned int timer;
	unsigned int attackTime;
	int health;
	float speed;
	int strength;
	vector3d direction;
	bool isattack;
	bool iswalk;
	collisionsphere cs;
	vector3d rotation;
	unsigned int curframe;
	bool isdead;
	int deadTimer;


public:
	Enemy(std::vector<unsigned int>& f, unsigned int& w, unsigned int& at, unsigned int& di, int h, float s, int str, collisionsphere c, vector3d rot, vector3d playerloc);
	Enemy(int h, float s, int str, unsigned int attackTime, collisionsphere c, vector3d rot, vector3d playerloc);
	Enemy(std::vector<unsigned int>& f, int h, float s, int str, unsigned int attackTime, collisionsphere c, vector3d rot, vector3d playerloc, std::vector<collisionplane> collisionPlanes);
	bool update(std::vector<collisionplane>&, vector3d, collisionsphere);
	void show();
	collisionsphere* getSphere();
	void setLocation(vector3d& loc);
	bool setAttack(collisionsphere playerloc);
	void decreaseHealth(int num);
	int getHealth();
	int getStrength();
	bool isDead();
	bool deadTimerTick();
	int getDeadTimer();
	std::vector<collisionplane> getCollisionPlanes();
};

#endif
