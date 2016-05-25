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
}

Enemy::Enemy(int h, float s, int str, collisionsphere c, vector3d rot, vector3d playerloc)
{
	//	if(frames.size()!=0)
	//	{
	health = h;
	speed = s;
	strength = str;
	isattack = false;
	iswalk = true;
	isdead = false;
	cs = c;
	rotation = rot;
	direction.change(playerloc - cs.center);
	direction.normalize();
	curframe = 0;
	//	}
}

bool Enemy::update(std::vector<collisionplane>& map2, vector3d playerpos, collisionsphere css)
{
		direction.change(playerpos - cs.center);
		direction.normalize();
		rotation.y = std::acos(direction.z);
		if (direction.x>0)
			rotation.y = -rotation.y;
		vector3d newpos(cs.center);
		//		std::cout << direction;
		newpos += direction*speed;
		newpos.y -= 0.3;
		for (int i = 0; i<map2.size(); i++)
			sphereplane(newpos, map2[i].normal, map2[i].p[0], map2[i].p[1], map2[i].p[2], map2[i].p[3], cs.r);


			boolean isCollision = spheresphere(cs.center, cs.r, css.center, css.r);

			if (isCollision) {
				setLocation(vector3d(10, 50, 10));
			}
			else {
				setLocation(newpos);
			}
		//		std::cout << "collision" << std::endl;
		
		

		
		

		
	//	std::cout << "dir: " << direction;
	//	std::cout << rotation.y*(180/M_PI) << std::endl;
	//	std::cout << direction;
	return 0;
	//	std::cout << cs.center << " ----- " << iswalk << " " << isattack << " "  << curframe <<  "  ---- " << direction << std::endl;
}

void Enemy::show()
{
	glEnable(GL_NORMALIZE);

	glPushMatrix();
	glTranslatef(cs.center.x, cs.center.y, cs.center.z);
	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(-rotation.y*(180 / M_PI), 0, 1, 0);
	glRotatef(rotation.z, 0, 0, 1);
	glColor3ub(255, 0, 0);
	glutSolidCube(0.5);
	glPopMatrix();
	glDisable(GL_NORMALIZE);
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
	if (spheresphere(cs.center, cs.r, playerloc.center, playerloc.r) && !isdead)
	{
		isattack = true;
		iswalk = false;
		return 1;
	}
	else if (!isdead) {
		iswalk = true;
		isattack = false;
		return 0;
	}
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
	return isdead;
}
