#ifndef ENEMY_H
#define ENEMY_H
#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "vector.h"
#include "collisionsphere.h"
#include "collisionplane.h"
#include "collision.h"
#include <string>
#include <vector>

/// <summary>	A macro that defines pi. </summary>
#define M_PI 1.57079632679489661923

/// <summary>	An enemy class, display, move, ang get info about enemys. </summary>
class Enemy : private collision
{
	/// <summary>	The frames. </summary>
	static std::vector<unsigned int> frames;
	/// <summary>	The collision planes. </summary>
	std::vector<collisionplane> collisionPlanes;
	/// <summary>	The walk. </summary>
	static unsigned int walk;
	/// <summary>	The attack. </summary>
	static unsigned int attack;
	/// <summary>	The die. </summary>
	static unsigned int die;
	/// <summary>	The timer. </summary>
	unsigned int timer;
	/// <summary>	The attack time. </summary>
	unsigned int attackTime;
	/// <summary>	The health. </summary>
	int health;
	/// <summary>	The speed. </summary>
	float speed;
	/// <summary>	The strength. </summary>
	int strength;
	/// <summary>	The direction. </summary>
	vector3d direction;
	/// <summary>	true to isattack. </summary>
	bool isattack;
	/// <summary>	true to iswalk. </summary>
	bool iswalk;
	/// <summary>	The create struct. </summary>
	collisionsphere cs;
	/// <summary>	The rotation. </summary>
	vector3d rotation;
	/// <summary>	The curframe. </summary>
	unsigned int curframe;
	/// <summary>	true to isdead. </summary>
	bool isdead;
	/// <summary>	The dead timer. </summary>
	int deadTimer;


public:

	/// <summary>	Constructor. </summary>
	///
	/// <param name="f">			[in,out] The std::vector&lt;unsignedint&gt; to process. </param>
	/// <param name="w">			[in,out] The int to process. </param>
	/// <param name="at">			[in,out] at. </param>
	/// <param name="di">			[in,out] The di. </param>
	/// <param name="h">			The height. </param>
	/// <param name="s">			The float to process. </param>
	/// <param name="str">			The string. </param>
	/// <param name="c">			The collisionsphere to process. </param>
	/// <param name="rot">			The rotation </param>
	/// <param name="playerloc">	The player location </param>



	Enemy(std::vector<unsigned int>& f, unsigned int& w, unsigned int& at, unsigned int& di, int h, float s, int str, collisionsphere c, vector3d rot, vector3d playerloc);

	/// <summary>	Constructor. </summary>
	///
	/// <param name="h">		 	The height. </param>
	/// <param name="s">		 	The float to process. </param>
	/// <param name="str">		 	The string. </param>
	/// <param name="attackTime">	The attack time. </param>
	/// <param name="c">		 	The collisionsphere to process. </param>
	/// <param name="rot">		 	The rotation </param>
	/// <param name="playerloc"> 	The player location. </param>

	Enemy(int h, float s, int str, unsigned int attackTime, collisionsphere c, vector3d rot, vector3d playerloc);

	/// <summary>	Constructor. </summary>
	///
	/// <param name="f">			  	[in,out] The std::vector&lt;unsignedint&gt; to process. </param>
	/// <param name="h">			  	The height. </param>
	/// <param name="s">			  	The float to process. </param>
	/// <param name="str">			  	The string. </param>
	/// <param name="attackTime">	  	The attack time. </param>
	/// <param name="c">			  	The collisionsphere to process. </param>
	/// <param name="rot">			  	The rot. </param>
	/// <param name="playerloc">	  	The playerloc. </param>
	/// <param name="collisionPlanes">	The collision planes. </param>

	Enemy(std::vector<unsigned int>& f, int h, float s, int str, unsigned int attackTime, collisionsphere c, vector3d rot, vector3d playerloc, std::vector<collisionplane> collisionPlanes);

	/// <summary>	Updates this object. </summary>
	///
	/// <param name="parameter1">	[in,out] The first parameter. </param>
	/// <param name="parameter2">	The second parameter. </param>
	/// <param name="parameter3">	The third parameter. </param>
	///
	/// <returns>	true if it succeeds, false if it fails. </returns>

	bool update(std::vector<collisionplane>&, vector3d, collisionsphere);
	/// <summary>	Shows this object. </summary>
	void show();

	/// <summary>	Gets the sphere. </summary>
	///
	/// <returns>	null if it fails, else the sphere. </returns>

	collisionsphere* getSphere();

	/// <summary>	Sets a location. </summary>
	///
	/// <param name="loc">	[in,out] The location. </param>

	void setLocation(vector3d& loc);

	/// <summary>	Sets an attack. </summary>
	///
	/// <param name="playerloc">	The playerloc. </param>
	///
	/// <returns>	true if it succeeds, false if it fails. </returns>

	bool setAttack(collisionsphere playerloc);

	/// <summary>	Decrease health. </summary>
	///
	/// <param name="num">	Number of. </param>

	void decreaseHealth(int num);

	/// <summary>	Gets the health. </summary>
	///
	/// <returns>	The health. </returns>

	int getHealth();

	/// <summary>	Gets the strength. </summary>
	///
	/// <returns>	The strength. </returns>

	int getStrength();

	/// <summary>	Query if this object is dead. </summary>
	///
	/// <returns>	true if dead, false if not. </returns>

	bool isDead();

	/// <summary>	Determines if we can dead timer tick. </summary>
	///
	/// <returns>	true if it succeeds, false if it fails. </returns>

	bool deadTimerTick();

	/// <summary>	Gets dead timer. </summary>
	///
	/// <returns>	The dead timer. </returns>

	int getDeadTimer();

	/// <summary>	Gets collision planes. </summary>
	///
	/// <returns>	The collision planes. </returns>

	std::vector<collisionplane> getCollisionPlanes();
};

#endif
