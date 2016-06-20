#include "item.h"

oneItem::oneItem(int& i,  collisionsphere c)
{
	id = i;
	direction = false;
	speed.change(0, 0, 0);
	rotation.change(0, 0, 0);
	cs = c;
	scale = vector3d(1, 1, 1);
}


item::item(int i, unsigned int mesh, collisionsphere& c)
{
	items.push_back(oneItem(i, c));
}

item::item()
{

}

int item::update(collisionsphere playerpos)
{
	for (int i = 0;i<items.size();i++)
	{
		items[i].rotation.y += 0.01;
		if (items[i].rotation.y>360)
			items[i].rotation.y -= 360;
		
		
		if (items[i].speed.y < 2 && !items[i].direction) {
			items[i].speed.y += 0.005;
		}
		if (items[i].speed.y >= 2) {
			items[i].direction = true;
		}
		if (items[i].speed.y>0 && items[i].direction)
			items[i].speed.y -= 0.005;

		if (items[i].speed.y<0 && items[i].direction)
			items[i].direction = false;
		items[i].speed.z = sin(items[i].rotation.y*2);
		items[i].speed.x = cos(items[i].rotation.y*2);
	}
	for (int i = 0;i<items.size();i++)
	{
		if (spheresphere(items[i].cs.center, items[i].cs.r, playerpos.center, playerpos.r))
		{
			int id = items[i].id;
			items.erase(items.begin() + i);
			return id;
		}
	}
	return -1;
}

void item::show()
{
	glEnable(GL_NORMALIZE);
	for (int i = 0;i<items.size();i++)
	{
		glPushMatrix();
		glTranslatef(items[i].cs.center.x+items[i].speed.x, items[i].cs.center.y+items[i].speed.y, items[i].cs.center.z+ items[i].speed.z);
		glRotatef(items[i].rotation.x, 1.0, 0.0, 0.0);
		glRotatef(items[i].rotation.y, 0.0, 1.0, 0.0);
		glRotatef(items[i].rotation.z, 0.0, 0.0, 1.0);
		glScalef(items[i].scale.x, items[i].scale.y, items[i].scale.z);

		switch (items[i].id) {
		case 0:
			glColor3f(0, 0, 1);
			break;
		case 1:
			glColor3f(1, 0.5, 0.5);
			break;
		default:
			glColor3f(1, 1, 1);
			break;
		
		}
		
		glutSolidCube(0.5);
		glPopMatrix();
	}
	glDisable(GL_NORMALIZE);
}

void item::add(int i,  collisionsphere c)
{
	items.push_back(oneItem(i, c));
}

void item::del(int id)
{
	for (int i = 0;i<items.size();i++)
	{
		if (items[i].id == id)
		{
			items.erase(items.begin() + i);
			break;
		}
	}
}
