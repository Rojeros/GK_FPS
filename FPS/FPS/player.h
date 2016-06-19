#pragma once
#ifndef gracz_h
#define gracz_h
#include "vector.h"
#include <vector>
#include <string>
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <cmath>
#include "camera.h"
#include "collisionsphere.h"
#include "collisionplane.h"
#include "collision.h"
#include "weapon.h"

//Liczba klatek na sek. i aktualna
extern int fps, sfps;
class Player

{
	std::vector<Weapon*> weapons;
	int currentWeapon;
	collisionsphere collisionSp;
	std::string name;
	int health;
	vector3d force;
	vector3d direction;
	bool groundCollision;
	float sprint;
	float walk;
	bool isSprint;
	float energy;
	int points;
	bool wallCollision;
	vector3d startPoint;


public:
	Camera cam;
	Player();
	Player(std::string n, float predkosc, float sprint,float looks);
	Player(std::string n, collisionsphere cs, Weapon* startWeapon, int hl, float predkosc, float sprint, float looks);
	Camera* getCamera();
	void update(std::vector<collisionplane>& cp);
	void show();
	void jump();
	std::string getName();
	void decreaseHealth(int num);
	int getHealth();
	void setHealth(int h);
	void addHealth(int h);
	void addWeapon(Weapon*gun);
	void setSprint(bool b);
	bool getSprint();
	void addPoints(int num);
	bool isWallCollision();
	bool isGroundCollision();
	bool isDead();
	int getPoints();
	void teleport();
	void setPosition(vector3d position);
	void resetPlayer();
	Weapon* getCurrentWeapon();
	Weapon* Player::getRandomWeapon();
	void changeWeapon(bool up);
	collisionsphere getCollisionSphere();
	std::vector<Weapon*> getAllWeapon();
	int getIntCurrentWeapon();

};

#endif