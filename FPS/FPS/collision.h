#pragma once
#include "vector.h"
#include <cmath>

/// <summary>	A collision. </summary>
class collision {
public:

	/// <summary>	Sphereplanes. </summary>
	///
	/// <param name="sp">	[in,out] The sphareplane. </param>
	/// <param name="pn">	The plane. </param>
	/// <param name="p1">	The first plane. </param>
	/// <param name="p2">	The second plane. </param>
	/// <param name="p3">	The third plane. </param>
	/// <param name="p4">	The fourth plane. </param>
	/// <param name="r"> 	The ray. </param>
	///
	/// <returns>	true if it succeeds, false if it fails. </returns>

	static bool sphereplane(vector3d& sp, vector3d pn, vector3d p1, vector3d p2, vector3d p3, vector3d p4, float r);

	/// <summary>	Rayspheres. </summary>
	///
	/// <param name="xc">			The x of point's collison. </param>
	/// <param name="yc">			The y of point's collison. </param>
	/// <param name="zc">			The z of point's collison. </param>
	/// <param name="xd">			The x of ray's direction . </param>
	/// <param name="yd">			The y of ray's direction. </param>
	/// <param name="zd">			The z of ray's direction. </param>
	/// <param name="xs">			The x sphere . </param>
	/// <param name="ys">			The y sphere. </param>
	/// <param name="zs">			The z sphere. </param>
	/// <param name="r">			The ray. </param>
	/// <param name="dist">			[in,out] (Optional) If non-null, the distance. </param>
	/// <param name="collpoint">	[in,out] (Optional) If non-null, the collpoint. </param>
	///
	/// <returns>	true if it succeeds, false if it fails. </returns>

	static bool raysphere(float xc, float yc, float zc, float xd, float yd, float zd, float xs, float ys, float zs, float r, float* dist = NULL, vector3d* collpoint = NULL);

	/// <summary>	Rayplanes. </summary>
	///
	/// <param name="nx">   	The nx. </param>
	/// <param name="ny">   	The ny. </param>
	/// <param name="nz">   	The nz. </param>
	/// <param name="x0">   	The x coordinate 0. </param>
	/// <param name="y0">   	The y coordinate 0. </param>
	/// <param name="z0">   	The z coordinate 0. </param>
	/// <param name="xs">   	The xs. </param>
	/// <param name="ys">   	The ys. </param>
	/// <param name="zs">   	The zs. </param>
	/// <param name="xd">		The x of ray's direction . </param>
	/// <param name="yd">		The y of ray's direction. </param>
	/// <param name="zd">		The z of ray's direction. </param>
	/// <param name="p1">   	The first plane. </param>
	/// <param name="p2">   	The second plane. </param>
	/// <param name="p3">   	The third plane. </param>
	/// <param name="p4">   	The fourth plane. </param>
	/// <param name="dis">  	[in,out] (Optional) If non-null, the distance. </param>
	/// <param name="point">	[in,out] (Optional) If non-null, the point. </param>
	///
	/// <returns>	true if it succeeds, false if it fails. </returns>

	static bool rayplane(const float& nx, float ny, float nz, float x0, float y0, float z0, float xs, float ys, float zs, float xd, float yd, float zd, vector3d p1, vector3d p2, vector3d p3, vector3d p4, float* dis = NULL, vector3d* point = NULL);

	/// <summary>	Rayplanedists. </summary>
	///
	/// <param name="nx">	The nx. </param>
	/// <param name="ny">	The ny. </param>
	/// <param name="nz">	The nz. </param>
	/// <param name="x0">	The x coordinate 0. </param>
	/// <param name="y0">	The y coordinate 0. </param>
	/// <param name="z0">	The z coordinate 0. </param>
	/// <param name="xs">	The xs. </param>
	/// <param name="ys">	The ys. </param>
	/// <param name="zs">	The zs. </param>
	/// <param name="xd">	The x of ray's direction . </param>
	/// <param name="yd">	The y of ray's direction. </param>
	/// <param name="zd">	The z of ray's direction. </param>
	///
	/// <returns>	A float. </returns>

	static float rayplanedist(float nx, float ny, float nz, float x0, float y0, float z0, float xs, float ys, float zs, float xd, float yd, float zd);

	/// <summary>	Triangleareas. </summary>
	///
	/// <param name="p1">	The first vector3d. </param>
	/// <param name="p2">	The second vector3d. </param>
	/// <param name="p3">	The third vector3d. </param>
	///
	/// <returns>	A float. </returns>

	static float trianglearea(vector3d p1, vector3d p2, vector3d p3);

	/// <summary>	Spherespheres. </summary>
	///
	/// <param name="c1">	[in,out] The first vector3d. </param>
	/// <param name="r1">	The first float. </param>
	/// <param name="c2">	[in,out] The second vector3d. </param>
	/// <param name="r2">	The second float. </param>
	///
	/// <returns>	true if it succeeds, false if it fails. </returns>

	static bool spheresphere(vector3d& c1, float r1, vector3d& c2, float r2);

	/// <summary>	Pointdistacesquares. </summary>
	///
	/// <param name="p1">	The first vector3d. </param>
	/// <param name="p2">	The second vector3d. </param>
	///
	/// <returns>	A float. </returns>

	static float pointdistacesquare(vector3d p1, vector3d p2);

	/// <summary>	Pointdistaces. </summary>
	///
	/// <param name="p1">	The first vector3d. </param>
	/// <param name="p2">	The second vector3d. </param>
	///
	/// <returns>	A float. </returns>

	static float pointdistace(vector3d p1, vector3d p2);
};