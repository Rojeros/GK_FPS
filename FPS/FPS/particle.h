#include <windows.h>
#include <iostream>
#include <vector>
#include <list>
#define GLUT_DISABLE_ATEXIT_HACK

#include <math.h>
#include <ctime>
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

#include "vector.h"


/// <summary>	Defines an alias representing the particle t. </summary>
typedef struct _particleT
{
	/// <summary>	true to show, false to hide. </summary>
	bool visible;
	/// <summary>	The first life time. </summary>
	int FirstLifeTime;
	/// <summary>	The position in air. </summary>
	vector3d positionInAir;
	/// <summary>	The position ground. </summary>
	vector3d positionOnGround;
/// <summary>	. </summary>
} particleT;

/// <summary>	Defines an alias representing the bullet. </summary>
typedef struct BulletT
{
	/// <summary>	The position in air. </summary>
	vector3d positionInAir;
	/// <summary>	Destination for the. </summary>
	vector3d destination;
	/// <summary>	The direction. </summary>
	vector3d direction;
	/// <summary>	The size. </summary>
	float size;
	/// <summary>	The speed. </summary>
	float speed;
	/// <summary>	true to boom. </summary>
	bool boom;
	/// <summary>	The life. </summary>
	int life;
	/// <summary>	The maximum timer. </summary>
	int maxTimer;
	/// <summary>	The timer. </summary>
	int timer;

	/// <summary>	Constructor. </summary>
	///
	/// <param name="positionInAir">	The position in air. </param>
	/// <param name="destination">  	Destination for the. </param>
	/// <param name="direction">		The direction. </param>
	/// <param name="size">				The size. </param>
	/// <param name="speed">			The speed. </param>
	/// <param name="boom">				true to boom. </param>
	/// <param name="timer">			The timer. </param>

	BulletT(vector3d positionInAir, vector3d destination, vector3d direction, float size, float speed,bool boom,float timer) :positionInAir(positionInAir), destination(destination), direction(direction), size(size), speed(speed), boom(boom), life(0),maxTimer(timer),timer(0){};
} ;

/// <summary>	Defines an alias representing the particle system t. </summary>
typedef struct _particleSystemT
{
	/// <summary>	Height of the ground. </summary>
	float GroundHeight;
	/// <summary>	The maximum particle height. </summary>
	float maxParticleHeight;
	/// <summary>	The maximum particle life time. </summary>
	int maxParticleLifeTime;

	/// <summary>	Gets the height. </summary>
	///
	/// <value>	The height. </value>

	int width, height;
	/// <summary>	Number of. </summary>
	int number;
	/// <summary>	The speed. </summary>
	float speed;
	/// <summary>	The size. </summary>
	float size;
	/// <summary>	The particles. </summary>
	particleT *particles;
// End of particle.h
} particleSystemT;


