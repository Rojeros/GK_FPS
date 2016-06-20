#include "item.h"

oneItem::oneItem(kind i,  collisionsphere c)
{
	id = i;
	direction = false;
	speed.change(0, 0, 0);
	rotation.change(0, 0, 0);
	cs = c;
	scale = vector3d(1, 1, 1);
	colour = vector3d(1, 1, 1);
}

oneItem::oneItem(kind i, collisionsphere c, vector3d rotation, vector3d speed, vector3d scale,vector3d colour)
{
	id = i;
	direction = false;
	speed.change(speed.x, speed.y, speed.z);
	rotation.change(rotation.x, rotation.y, rotation.z);
	cs = c;
	this->scale = scale;
	this->colour = colour;
}


item::item(kind i, unsigned int mesh, collisionsphere& c)
{
	items.push_back(oneItem(i, c));
}

item::item()
{

}

int item::update(collisionsphere playerpos)
{
	
	
	for (int i = 0;i < items.size();i++)
	{
		if (items[i].id == finish) {
			items[i].colour.x += 0.001;
			if (items[i].colour.y>1)
				items[i].colour.x =0;
		
		}
		else {
			items[i].rotation.y += 0.01;
			if (items[i].rotation.y>360)
				items[i].rotation.y -= 360;


			if (items[i].speed.y < 2 && !items[i].direction) {
				items[i].speed.y += 0.005;
			}
			if (items[i].speed.y >= 2) {
				items[i].direction = true;
			}
			if (items[i].speed.y > 0 && items[i].direction)
				items[i].speed.y -= 0.005;

			if (items[i].speed.y < 0 && items[i].direction)
				items[i].direction = false;
			items[i].speed.z = sin(items[i].rotation.y * 2);
			items[i].speed.x = cos(items[i].rotation.y * 2);
		}
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
		case ammo:
			glColor3f(0, 0, 1);
			glutSolidCube(0.5);
			glPopMatrix();
			break;
		case health:
			glColor3f(1, 0.5, 0.5);
			glutSolidSphere(0.5, 10, 10);

			glPopMatrix();
			break;
		case finish:
			glColor3f(1, 0.5, 0.5);
		//	glColor3f(items[i].colour.x, items[i].colour.y, items[i].colour.z);
			glutSolidCube(2);
			glPopMatrix();
			break;
		default:
			glColor3f(1, 1, 1);
			glutSolidCube(4);
			glPopMatrix();
		}
	
		
		
	}
	glDisable(GL_NORMALIZE);
}

void item::add(kind i,  collisionsphere c)
{
	items.push_back(oneItem(i, c));
}

void item::add(kind i, collisionsphere c, vector3d rotation, vector3d speed, vector3d scale)
{
	items.push_back(oneItem( i, c,rotation,speed,scale,vector3d(1,1,1)));

}



void item::del(kind id)
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

void item::clear()
{
	items.clear();
}
