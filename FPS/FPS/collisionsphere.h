#pragma once
#include "vector.h"

class collisionsphere {
public:
	float r;
	vector3d center;
	collisionsphere(vector3d c, float rad);
	collisionsphere();
};