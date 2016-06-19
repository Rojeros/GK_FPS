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
	void text::startText(int g_viewport_width, int g_viewport_height);
	void text::displayText(std::string text, int g_viewport_width, int g_viewport_height, int size,coordinates coord,int line);
	void text::endText();
public:
	void text::showTextInfo(int health, int ammo, int allammo, int point, std::string& weaponName, int g_viewport_width, int g_viewport_height);
};
#endif
