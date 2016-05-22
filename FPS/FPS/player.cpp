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
	if (onGround)
	{
		onGround = false;
		direction.change(0.0, 2, 0.0);
	}
}

std::string Player::getName()
{
	return name;
}



void Player::update()
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

	cam.refresh();
	

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

