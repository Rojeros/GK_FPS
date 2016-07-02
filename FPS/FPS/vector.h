#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <cmath>

/// <summary>	A vector for calculating in 3d. </summary>
class vector3d {
public:

	/// <summary>	Gets the z coordinate. </summary>
	///
	/// <value>	The z coordinate. </value>

	float x, y, z;
	/// <summary>	Default constructor. </summary>
	vector3d();

	/// <summary>	Constructor. </summary>
	///
	/// <param name="a">	The float to process. </param>
	/// <param name="b">	The float to process. </param>

	vector3d(float a, float b);

	/// <summary>	Constructor. </summary>
	///
	/// <param name="a">	The float to process. </param>
	/// <param name="b">	The float to process. </param>
	/// <param name="c">	The float to process. </param>

	vector3d(float a, float b, float c);
	/// <summary>	Destructor. </summary>
	~vector3d() {};

	/// <summary>	Dotproducts the given vector 2. </summary>
	///
	/// <param name="vec2">	The second vector. </param>
	///
	/// <returns>	A float. </returns>

	float dotproduct(const vector3d& vec2);

	/// <summary>	Crossproducts the given vector 2. </summary>
	///
	/// <param name="vec2">	The second vector. </param>
	///
	/// <returns>	A vector3d. </returns>

	vector3d crossproduct(const vector3d& vec2);

	/// <summary>	Gets the length. </summary>
	///
	/// <returns>	A float. </returns>

	float length();

	/// <summary>	Changes. </summary>
	///
	/// <param name="a">	The float to process. </param>
	/// <param name="b">	The float to process. </param>
	/// <param name="c">	The float to process. </param>

	void change(float a, float b, float c);

	/// <summary>	Changes the given parameter 1. </summary>
	///
	/// <param name="parameter1">	[in,out] The first parameter. </param>

	void change(vector3d&);

	/// <summary>	Changes the given parameter 1. </summary>
	///
	/// <param name="parameter1">	The first parameter. </param>

	void change(vector3d);

	/// <summary>	Change x coordinate. </summary>
	///
	/// <param name="a">	The float to process. </param>

	void changeX(float a);

	/// <summary>	Change y coordinate. </summary>
	///
	/// <param name="b">	The float to process. </param>

	void changeY(float b);

	/// <summary>	Change z coordinate. </summary>
	///
	/// <param name="c">	The float to process. </param>

	void changeZ(float c);
	/// <summary>	Normalizes this object. </summary>
	void normalize();

	/// <summary>	Equality operator. </summary>
	///
	/// <param name="vec2">	The second vector. </param>
	///
	/// <returns>	true if the parameters are considered equivalent. </returns>

	bool operator==(const vector3d& vec2);

	/// <summary>	Inequality operator. </summary>
	///
	/// <param name="vec2">	The second vector. </param>
	///
	/// <returns>	true if the parameters are not considered equivalent. </returns>

	bool operator!=(const vector3d& vec2);

	/// <summary>	Greater-than-or-equal comparison operator. </summary>
	///
	/// <param name="vec2">	The second vector. </param>
	///
	/// <returns>	true if the first parameter is greater than or equal to the second. </returns>

	bool operator>=(const vector3d& vec2);

	/// <summary>	Addition operator. </summary>
	///
	/// <param name="vec2">	The second vector. </param>
	///
	/// <returns>	The result of the operation. </returns>

	vector3d operator+(const vector3d& vec2);

	/// <summary>	Addition operator. </summary>
	///
	/// <param name="vec2">	The second vector. </param>
	///
	/// <returns>	The result of the operation. </returns>

	vector3d operator+(const float vec2);

	/// <summary>	Subtraction operator. </summary>
	///
	/// <param name="vec2">	The second vector. </param>
	///
	/// <returns>	The result of the operation. </returns>

	vector3d operator-(const vector3d& vec2);

	/// <summary>	Multiplication operator. </summary>
	///
	/// <param name="num">	Number of. </param>
	///
	/// <returns>	The result of the operation. </returns>

	vector3d operator*(const float& num);

	/// <summary>	Division operator. </summary>
	///
	/// <param name="num">	Number of. </param>
	///
	/// <returns>	The result of the operation. </returns>

	vector3d operator/(const float& num);

	/// <summary>	Addition assignment operator. </summary>
	///
	/// <param name="vec2">	The second vector. </param>
	///
	/// <returns>	The result of the operation. </returns>

	vector3d& operator+=(const vector3d& vec2);

	/// <summary>	Subtraction assignment operator. </summary>
	///
	/// <param name="vec2">	The second vector. </param>
	///
	/// <returns>	The result of the operation. </returns>

	vector3d& operator-=(const vector3d& vec2);

	/// <summary>	Multiplication assignment operator. </summary>
	///
	/// <param name="num">	Number of. </param>
	///
	/// <returns>	The result of the operation. </returns>

	vector3d& operator*=(const float& num);

	/// <summary>	Division assignment operator. </summary>
	///
	/// <param name="num">	Number of. </param>
	///
	/// <returns>	The result of the operation. </returns>

	vector3d& operator/=(const float& num);

	/// <summary>	Stream insertion operator. </summary>
	///
	/// <param name="out"> 	[in,out] The out. </param>
	/// <param name="vec2">	The second vector. </param>
	///
	/// <returns>	The shifted result. </returns>

	friend std::ostream& operator<<(std::ostream& out, vector3d vec2);
};
#endif
