#pragma once
#ifndef gracz_h
#define gracz_h
#include "vector.h"
#include <vector>
#include <string>
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include<cmath>
#include "camera.h"
#include "collisionsphere.h"

//Liczba klatek na sek. i aktualna
extern int fps, sfps;
class Player

{
	
	collisionsphere collisionSp;
	std::string name;
	int health;
	vector3d force;
	vector3d direction;
	bool onGround;
	float sprint;
	float walk;
	bool isSprint;
	float energy;
	int points;


public:
	Camera cam;
	Player(std::string n, float predkosc, float sprint,float looks);
	Player(std::string n, collisionsphere cs, int hl, float predkosc, float sprint, float looks);
	Camera* getCamera();
	void update();
	void show();
	void jump();
	std::string getName();
	void decreaseHealth(int num);
	int getHealth();
	void setHealth(int h);
	void addHealth(int h);
	void setSprint(bool b);
	bool getSprint();
	void addPoints(int num);
	int getPoints();
	void setPosition(vector3d position);

};

#endif