#pragma once
#ifndef gracz_h
#define gracz_h
#include "vector.h"
#include <vector>
#include <string>
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include<cmath>

class gracz
{
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
	gracz(std::string n, float predkosc, float sprint);
	
	void update();
	void show();
	void skok();
	std::string getImie();
	void setPozycja(vector3d pos);
	void obniZdrowie(int num);
	int getZdrowie();
	void setZdrowie(int h);
	void dodZdrowie(int h);
	void setSprint(bool b);
	bool getBieg();
	void dodPunkty(int num);
	int getPunkty();

};

#endif