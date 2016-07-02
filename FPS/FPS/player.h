#pragma once
#ifndef gracz_h
#define gracz_h
#include "vector.h"
#include <vector>
#include <string>
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <cmath>
#include "camera.h"
#include "collisionsphere.h"
#include "collisionplane.h"
#include "collision.h"
#include "weapon.h"

/// <summary>	Gets the sfps. </summary>
///
/// <value>	The sfps. </value>

extern int fps, sfps;
/// <summary>	A player class, representing main character, get weapons, health, points, etc... . </summary>
class Player

{
	/// <summary>	The weapons. </summary>
	std::vector<Weapon*> weapons;
	/// <summary>	The current weapon. </summary>
	int currentWeapon;
	/// <summary>	The collision sp. </summary>
	collisionsphere collisionSp;
	/// <summary>	The name. </summary>
	std::string name;
	/// <summary>	The health. </summary>
	int health;
	/// <summary>	The force. </summary>
	vector3d force;
	/// <summary>	The direction. </summary>
	vector3d direction;
	/// <summary>	true to ground collision. </summary>
	bool groundCollision;
	/// <summary>	The sprint. </summary>
	float sprint;
	/// <summary>	The walk. </summary>
	float walk;
	/// <summary>	true if this object is sprint. </summary>
	bool isSprint;
	/// <summary>	The energy. </summary>
	float energy;
	/// <summary>	The points. </summary>
	int points;
	/// <summary>	true to wall collision. </summary>
	bool wallCollision;
	/// <summary>	The start point. </summary>
	vector3d startPoint;


public:
	/// <summary>	The camera. </summary>
	Camera cam;
	/// <summary>	Default constructor. </summary>
	Player();

	/// <summary>	Constructor. </summary>
	///
	/// <param name="n">	   	The std::string to process. </param>
	/// <param name="predkosc">	The predkosc. </param>
	/// <param name="sprint">  	The sprint. </param>
	/// <param name="looks">   	The looks. </param>

	Player(std::string n, float predkosc, float sprint,float looks);

	/// <summary>	Constructor. </summary>
	///
	/// <param name="n">		  	The std::string to process. </param>
	/// <param name="cs">		  	The create struct. </param>
	/// <param name="startWeapon">	[in,out] If non-null, the start weapon. </param>
	/// <param name="hl">		  	The hl. </param>
	/// <param name="predkosc">   	The predkosc. </param>
	/// <param name="sprint">	  	The sprint. </param>
	/// <param name="looks">	  	The looks. </param>

	Player(std::string n, collisionsphere cs, Weapon* startWeapon, int hl, float predkosc, float sprint, float looks);

	/// <summary>	Gets the camera. </summary>
	///
	/// <returns>	null if it fails, else the camera. </returns>

	Camera* getCamera();

	/// <summary>	Updates the given cp. </summary>
	///
	/// <param name="cp">	[in,out] The cp. </param>

	void update(std::vector<collisionplane>& cp);
	/// <summary>	Shows this object. </summary>
	void show();
	/// <summary>	Jumps this object. </summary>
	void jump();

	/// <summary>	Gets the name. </summary>
	///
	/// <returns>	The name. </returns>

	std::string getName();

	/// <summary>	Decrease health. </summary>
	///
	/// <param name="num">	Number of. </param>

	void decreaseHealth(int num);

	/// <summary>	Gets the health. </summary>
	///
	/// <returns>	The health. </returns>

	int getHealth();

	/// <summary>	Sets a health. </summary>
	///
	/// <param name="h">	The height. </param>

	void setHealth(int h);

	/// <summary>	Adds a health. </summary>
	///
	/// <param name="h">	The height. </param>

	void addHealth(int h);

	/// <summary>	Adds a weapon. </summary>
	///
	/// <param name="gun">	[in,out] If non-null, the gun. </param>

	void addWeapon(Weapon*gun);

	/// <summary>	Sets a sprint. </summary>
	///
	/// <param name="b">	true to b. </param>

	void setSprint(bool b);

	/// <summary>	Sets start position. </summary>
	///
	/// <param name="pos">	The position. </param>

	void setStartPosition(vector3d pos);

	/// <summary>	Gets the sprint. </summary>
	///
	/// <returns>	true if it succeeds, false if it fails. </returns>

	bool getSprint();

	/// <summary>	Adds the points. </summary>
	///
	/// <param name="num">	Number of. </param>

	void addPoints(int num);

	/// <summary>	Query if this object is wall collision. </summary>
	///
	/// <returns>	true if wall collision, false if not. </returns>

	bool isWallCollision();

	/// <summary>	Query if this object is ground collision. </summary>
	///
	/// <returns>	true if ground collision, false if not. </returns>

	bool isGroundCollision();

	/// <summary>	Query if this object is dead. </summary>
	///
	/// <returns>	true if dead, false if not. </returns>

	bool isDead();

	/// <summary>	Gets the points. </summary>
	///
	/// <returns>	The points. </returns>

	int getPoints();
	/// <summary>	Teleports this object. </summary>
	void teleport();

	/// <summary>	Sets a position. </summary>
	///
	/// <param name="position">	The position. </param>

	void setPosition(vector3d position);
	/// <summary>	Resets the player. </summary>
	void resetPlayer();

	/// <summary>	Gets current weapon. </summary>
	///
	/// <returns>	null if it fails, else the current weapon. </returns>

	Weapon* getCurrentWeapon();

	/// <summary>	Gets random weapon. </summary>
	///
	/// <returns>	null if it fails, else the random weapon. </returns>

	Weapon* Player::getRandomWeapon();

	/// <summary>	Change weapon. </summary>
	///
	/// <param name="up">	true to up. </param>

	void changeWeapon(bool up);

	/// <summary>	Gets collision sphere. </summary>
	///
	/// <returns>	The collision sphere. </returns>

	collisionsphere getCollisionSphere();

	/// <summary>	Gets all weapon. </summary>
	///
	/// <returns>	null if it fails, else all weapon. </returns>

	std::vector<Weapon*> getAllWeapon();

	/// <summary>	Gets int current weapon. </summary>
	///
	/// <returns>	The int current weapon. </returns>

	int getIntCurrentWeapon();

};

#endif