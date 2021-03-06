#include "player.h"

Player::Player() {

}

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

Player::Player(std::string n, collisionsphere cs, Weapon* startWeapon, int hl, float predkosc, float sprint, float looks)
{
	weapons.push_back(startWeapon);
	currentWeapon = 0;
	name = n;
	health = hl;
	collisionSp = cs;
	sprint = sprint;
	walk = predkosc;
	setPosition(cs.center);
	force.change(0.0, -0.1, 0.0);
	energy = 10;
	sprint = false;
	points = 0;
	startPoint = cs.center;

}

Camera* Player::getCamera()
{
	return &cam;
}

void Player::show()
{
	if (weapons.size() > 0) {
		weapons[currentWeapon]->show(cam.getYaw(), cam.getPitch());
	}
}

void Player::jump()
{
	if (groundCollision)
	{
		groundCollision = false;
		direction.change(0.0, 2, 0.0);
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

	if (newpos.x > tmp.x)
	{
		wallCollision = true;
	}
	else 
	{
		wallCollision = false;
	}

	setPosition(newpos);
	if (weapons.size() > 0) {
		weapons[currentWeapon]->update(newpos);
	}

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

void Player::addWeapon(Weapon * gun)
{
	weapons.push_back(gun);
}

void Player::setSprint(bool b)
{
}

void Player::setStartPosition(vector3d pos)
{
	startPoint = pos;
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

bool Player::isDead()
{
	if(health<=0 || cam.getLocation().y<-100)
	return true;

	return false;
}

void Player::resetPlayer()
{
	setHealth(1500);
	setPosition(startPoint);
	points=0;
}

Weapon* Player::getCurrentWeapon() {
	if (weapons.size() > 0) {
		return weapons[currentWeapon];
	}

	return NULL;
	
}

Weapon* Player::getRandomWeapon() {
	if (weapons.size() > 0) {
		return weapons[rand()%weapons.size()];
	}

	return NULL;

}
void Player::changeWeapon(bool up)
{
	if(up){
		
		if (weapons.size() > (currentWeapon + 1)) {
			currentWeapon++;
		
		}
		else {
			currentWeapon = 0;
		}

	}
	else {
		
		if ((currentWeapon - 1) >= 0) {
			currentWeapon--;
		}
		else {
			currentWeapon = weapons.size()-1;
		}
	}
	cout << weapons[currentWeapon]->getName()<<"\n";
}

collisionsphere Player::getCollisionSphere() {
	return collisionSp;
}

std::vector<Weapon*> Player::getAllWeapon()
{
	return weapons;
}

int Player::getIntCurrentWeapon()
{
	return currentWeapon;
}

