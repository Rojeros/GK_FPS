#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#ifndef TEXT_H
#define TEXT_H
#include <string>
#include <cstring>
#include <iostream>
#include "vector.h"
#include "collisionplane.h"
#include <vector>
#include "weapon.h"
enum coordinates {
	NW,
	N,
	NE,
	E,
	SE,
	S,
	SW,
	W,
	CENTER

};




class text {
	void text::displayText(std::string text, int g_viewport_width, int g_viewport_height, double size, coordinates coord, int line);
	void text::startText(int g_viewport_width, int g_viewport_height);
	void text::displayText(std::string text, int g_viewport_width, int g_viewport_height, double size, coordinates coord, int line, vector3d color);
	void text::endText();
public:
	void text::showTextInfo(int health, int ammo, int allammo, int point, std::vector<Weapon*> weaponName,int currentWeapon,int points, int g_viewport_width, int g_viewport_height,std::string level);
	void text::displayDiffrentText(std::string text, int g_viewport_width, int g_viewport_height, double size, coordinates coord, int line,vector3d color);

};
#endif
