#include "Enemy.h"


std::vector<unsigned int> Enemy::frames;
unsigned int Enemy::walk = 0;
unsigned int Enemy::attack = 0;
unsigned int Enemy::die = 0;

Enemy::Enemy(std::vector<unsigned int>& f, unsigned int& w, unsigned int& at, unsigned int& di, int h, float s, int str, collisionsphere c, vector3d rot, vector3d playerpos)
{
	frames = f;
	walk = w;
	attack = at;
	die = di;
	health = h;
	speed = s;
	strength = str;
	isattack = false;
	iswalk = true;
	isdead = false;
	cs = c;
	rotation = rot;
	direction.change(playerpos - cs.center);
	direction.normalize();
	curframe = 0;
	timer = 0;
	attackTime = 200;
	deadTimer = 0;
}

Enemy::Enemy(int health, float speed, int strength, unsigned int attackTime, collisionsphere c, vector3d rot, vector3d playerloc)
{
	this->attackTime = attackTime;
	this->health = health;
	this->speed = speed;
	this->strength = strength;
	isattack = false;
	iswalk = true;
	isdead = false;
	cs = c;
	rotation = rot;
	direction.change(playerloc - cs.center);
	direction.normalize();
	curframe = 0;
	timer = 0;
	deadTimer = 0;
}

Enemy::Enemy(std::vector<unsigned int>& f, int health, float speed, int strength, unsigned int attackTime, collisionsphere c, vector3d rot, vector3d playerloc, std::vector<collisionplane> collisionPlanes)
{
	frames = f;
	this->attackTime = attackTime;
	this->health = health;
	this->speed = speed;
	this->strength = strength;
	isattack = false;
	iswalk = true;
	isdead = false;
	cs = c;
	rotation = rot;
	direction.change(playerloc - cs.center);
	direction.normalize();
	curframe = 0;
	timer = 0;
	this->collisionPlanes = collisionPlanes;
	deadTimer = 0;
	walk = 39;
}

bool Enemy::update(std::vector<collisionplane>& map2, vector3d playerpos, collisionsphere css)
{
	
		direction.change(playerpos - cs.center);
		direction.normalize();
		rotation.y = std::acos(direction.z);
		if (direction.x>0)
			rotation.y = -rotation.y;
		vector3d newpos(cs.center);
		newpos += direction*speed;
		newpos.y -= 0.3;
		for (int i = 0; i<map2.size(); i++)
			sphereplane(newpos, map2[i].normal, map2[i].p[0], map2[i].p[1], map2[i].p[2], map2[i].p[3], cs.r);


			boolean isCollision = spheresphere(cs.center, cs.r, css.center, css.r);

			if (!isCollision) {
				setLocation(newpos);
			}

	iswalk = true;
	curframe++;
	if (iswalk && curframe >= walk)
		curframe = 0;

	return 0;
}

void Enemy::show()
{
	glEnable(GL_NORMALIZE);

	glPushMatrix();
	glTranslatef(cs.center.x, cs.center.y-cs.r, cs.center.z);
	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(-rotation.y*(180 / M_PI), 0, 1, 0);
	glRotatef(rotation.z, 0, 0, 1);
	//glScalef(1.5, 1.5, 1.5);
	//glColor3ub(255, 0, 0);
	//glutSolidCube(0.5);
	glCallList(frames[curframe]);
	//glScalef(1, 1, 1);
	//glDisable(GL_TEXTURE_2D);
//	glColor4f(1, 1, 1, 0.3);
//	glutSolidSphere(cs.r, 10, 10);
	glPopMatrix();
	glDisable(GL_NORMALIZE);
//	glEnable(GL_TEXTURE_2D);
}

collisionsphere* Enemy::getSphere()
{
	return &cs;
}

void Enemy::setLocation(vector3d& loc)
{
	cs.center = loc;
}

bool Enemy::setAttack(collisionsphere playerloc)
{
	
	if (spheresphere(cs.center, cs.r, playerloc.center, playerloc.r) && !isdead && timer>attackTime)
	{
		isattack = true;
		iswalk = true;
		timer = 0;
		return 1;
	}
	else
	{

		//for (int i = 0; i < collisionPlanes.size(); i++)
		//{
		//	if (collision::sphereplane(playerloc.center, collisionPlanes[i].normal, collisionPlanes[i].p[0], collisionPlanes[i].p[1], collisionPlanes[i].p[2], collisionPlanes[i].p[3], playerloc.r))
			//{
			//	isattack = true;
			//	iswalk = true;
			//	timer = 0;
			//	return 1;
		//	}
		//}


		if (!isdead) {
			timer++;
			iswalk = true;
			isattack = false;
			return 0;
		}
	
	}

	return 0;
}


void Enemy::decreaseHealth(int num)
{
	health -= num;
}

int Enemy::getHealth()
{
	return health;
}

int Enemy::getStrength()
{
	return strength;
}

bool Enemy::isDead()
{
	if (health <= 0 || cs.center.y<-100) {
		isdead = true;
	}
	return isdead;
}

bool Enemy::deadTimerTick()
{
	deadTimer++;
	if (deadTimer>10)
	return true;
	return false;
}

int Enemy::getDeadTimer()
{
	return deadTimer;
}

std::vector<collisionplane> Enemy::getCollisionPlanes()
{
	return collisionPlanes;
}
