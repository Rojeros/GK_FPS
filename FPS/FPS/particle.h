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


typedef struct _particleT
{
	bool visible;
	int FirstLifeTime;
	vector3d positionInAir;
	vector3d positionOnGround;
} particleT;

typedef struct BulletT
{
	vector3d positionInAir;
	vector3d destination;
	vector3d direction;
	float size;
	float speed;
	bool boom;
	int life;
	int maxTimer;
	int timer;
	BulletT(vector3d positionInAir, vector3d destination, vector3d direction, float size, float speed,bool boom,float timer) :positionInAir(positionInAir), destination(destination), direction(direction), size(size), speed(speed), boom(boom), life(0),maxTimer(timer),timer(0){};
} ;

typedef struct _particleSystemT
{
	float GroundHeight;
	float maxParticleHeight;
	int maxParticleLifeTime;
	int width, height;
	int number;
	float speed;
	float size;
	particleT *particles;
} particleSystemT;


