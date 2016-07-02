#pragma once
#include "vector.h"

/// <summary>	A collisionsphere. </summary>
class collisionsphere {
public:
	/// <summary>	The float to process. </summary>
	float r;
	/// <summary>	The center. </summary>
	vector3d center;

	/// <summary>	Constructor. </summary>
	///
	/// <param name="c">  	The vector3d to process. </param>
	/// <param name="rad">	The radians. </param>

	collisionsphere(vector3d c, float rad);
	/// <summary>	Default constructor. </summary>
	collisionsphere();
};