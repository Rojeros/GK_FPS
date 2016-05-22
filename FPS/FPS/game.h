#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "vector.h"
#include "player.h"
#include "objectloader.h"
#include "camera.h"

class game {

	objloader objLoader;
	player* player;

	static void display();

public:
	game(int argc, char **argv);
	~game();

	void start();


};