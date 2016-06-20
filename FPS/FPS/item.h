#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include "vector.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "collisionsphere.h"
#include "collision.h"
enum kind {
	finish,
	health,
	ammo
};
struct oneItem
{
	kind id;
	unsigned int mesh;
	vector3d rotation;
	vector3d speed;
	bool direction;
	collisionsphere cs;
	vector3d scale;
	vector3d colour;
	oneItem(kind i, collisionsphere c);
	oneItem(kind i, collisionsphere c, vector3d rotation, vector3d speed, vector3d scale, vector3d colour);
};

class item :public collision {
	std::vector<oneItem> items;
public:
	item(kind i, unsigned int mesh, collisionsphere& c);

	item();
	int update(collisionsphere playerloc);
	void show();
	void add(kind i, collisionsphere c);
	void add(kind i, collisionsphere c, vector3d rotation, vector3d speed, vector3d scale);
	void del(kind id);
	void clear();
};

#endif
