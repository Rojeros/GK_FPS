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
class player

{
	
	collisionsphere collisionSp;
	std::string imie;
	int zdrowie;
	vector3d sila;
	vector3d kierunek;
	bool naZiemi;
	float bieg;
	float chodzenie;
	bool czyBieg;
	float energia;
	int punkty;


public:
	Camera cam;
	player(std::string n, float predkosc, float sprint,float looks);
	player(std::string n, collisionsphere cs, int hl, float predkosc, float sprint, float looks);
	Camera* getCamera();
	void update();
	void show();
	void skok();
	std::string getImie();
	void obniZdrowie(int num);
	int getZdrowie();
	void setZdrowie(int h);
	void dodZdrowie(int h);
	void setSprint(bool b);
	bool getBieg();
	void dodPunkty(int num);
	int getPunkty();
	void setPosition(vector3d position);

};

#endif