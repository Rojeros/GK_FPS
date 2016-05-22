#include "player.h"


Player::Player(std::string n, float predkosc, float sprint,float looks)
{
	name = n;
	health = 500;
	sprint =sprint;
	walk = predkosc;
	force.change(0.0, -0.3, 0.0);
	direction.change(0.0, 0.0, 0.0);
	energy = 10;
	sprint = false;
	points = 0;

}

Player::Player(std::string n, collisionsphere cs, int hl, float predkosc, float sprint, float looks)
{
	name = n;
	health = hl;
	collisionSp = cs;
	sprint = sprint;
	walk = predkosc;
	setPosition(cs.center);
	force.change(0.0, -0.3, 0.0);
	direction.change(0.0, 0.0, 0.0);
	energy = 10;
	sprint = false;
	points = 0;

}

Camera* Player::getCamera()
{
	return &cam;
}

void Player::show()
{
}

void Player::jump()
{
	if (groundCollision)
	{
		groundCollision = false;
		direction.change(0.0, 2, 0.0);
	}
	else {
		//direction.change(0.0, 50, 0.0);
	}
}

void Player::teleport()
{
	direction.change(0.0, 50, 0.0);
}

std::string Player::getName()
{
	return name;
}



void Player::update(std::vector<collisionplane>& cp)
{

	if (direction.y >= force.y)
		direction += force;
	//	std::cout << direction;
	
	if (energy<10 && !sprint)
		energy += 0.01;
	if (sprint)
		energy -= 0.05;
	if (energy <= 0)
		setSprint(false);
		
	vector3d newpos(cam.getLocation());
	newpos += direction;
	vector3d tmp(newpos);
	for (int i = 0; i < cp.size(); i++)
	{
		collision::sphereplane(newpos, cp[i].normal, cp[i].p[0], cp[i].p[1], cp[i].p[2], cp[i].p[3], collisionSp.r);
	}

	if (newpos.y > tmp.y)
	{
		groundCollision = true;
	}
	else
	{
		groundCollision = false;
	}

		

	if (newpos.x > tmp.x)
	{
		wallCollision = true;
	}
	else 
	{
		wallCollision = false;
	}

	std::cout << "WALL COLLISION " << wallCollision << std::endl;
	std::cout << "GROUND COLLISION " << groundCollision << std::endl;

	setPosition(newpos);
	//cam.refresh();
	

}


void Player::decreaseHealth(int num)
{
	health -= num;
}

int Player::getHealth()
{
	return health;
}


void Player::setHealth(int h)
{
	health = h;
}


void Player::addHealth(int h)
{
	health += h;
}

void Player::setSprint(bool b)
{
}

bool Player::getSprint()
{
	return sprint;
}

void Player::addPoints(int num)
{
	points += num;
}

int Player::getPoints()
{
	return points;
}

void Player::setPosition(vector3d position)
{
	collisionSp.center = position;
	cam.setLocation(position);
}

bool Player::isWallCollision() {
	return wallCollision;
}

bool Player::isGroundCollision() {
	return groundCollision;
}

