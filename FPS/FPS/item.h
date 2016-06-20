#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include "vector.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "collisionsphere.h"
#include "collision.h"

struct oneItem
{
	int id;
	unsigned int mesh;
	vector3d rotation;
	vector3d speed;
	bool direction;
	collisionsphere cs;
	vector3d scale;
	oneItem(int& i, collisionsphere c);
};

class item :public collision {
	std::vector<oneItem> items;
public:
	item(int i, unsigned int mesh, collisionsphere& c);
	item();
	int update(collisionsphere playerloc);
	void show();
	void add(int i, collisionsphere c);
	void del(int id);
};

#endif
