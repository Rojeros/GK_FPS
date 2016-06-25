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


