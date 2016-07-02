#ifndef __CAMERA_H__
#define __CAMERA_H__
#include "vector.h"


/// <summary>	A camera class, display eye of user  </summary>
class Camera
{

public:
	Camera() { init(); }
	~Camera() {}

	/// <summary>	init cameras position  </summary>
	void init();

	/// <summary>	Refreshes this object. </summary>
	void refresh();

	/// <summary>	Sets a position. </summary>
	///
	/// <param name="x">	The x coordinate. </param>
	/// <param name="y">	The y coordinate. </param>
	/// <param name="z">	The z coordinate. </param>

	void setPosition(float x, float y, float z);

	/// <summary>	Sets a location. </summary>
	///
	/// <param name="newPosition">	The new position for camera </param>

	void setLocation(const vector3d& newPosition);

	/// <summary>	Gets a position of camera location </summary>
	///
	/// <param name="x">	[in,out] The x float to process. </param>
	/// <param name="y">	[in,out] The y float to process. </param>
	/// <param name="z">	[in,out] The z float to process. </param>

	void getPosition(float &x, float &y, float &z);

	/// <summary>	Gets direction vector pf camera </summary>
	///
	/// <param name="x">	[in,out] The x float in 3d to process. </param>
	/// <param name="y">	[in,out] The y float in 3d to process. </param>
	/// <param name="z">	[in,out] The z float in 3d to process. </param>

	void getDirectionVector(float &x, float &y, float &z);

	/// <summary>	Gets direction vector of camera. </summary>
	///
	/// <returns>	The direction vector. </returns>

	vector3d Camera::getDirectionVector();

	/// <summary>	Sets a yaw for camera. </summary>
	///
	/// <param name="angle">	The angle of yaw </param>

	void setYaw(float angle);

	/// <summary>	Sets a pitch for camera </summary>
	///
	/// <param name="angle">	The angle of pitch. </param>

	void setPitch(float angle);

	/// <summary>	Gets the location of camera </summary>
	///
	/// <returns>	The location. </returns>

	vector3d getLocation();

	/// <summary>	Moves. </summary>
	///
	/// <param name="incr">	Amount to increment by. </param>

	void move(float incr);

	/// <summary>	slide camera into side  </summary>
	///
	/// <param name="incr">	Amount to increment z and x. </param>

	void strafe(float incr);

	/// <summary>	slide camera to up </summary>
	///
	/// <param name="incr">	Amount to increment y. </param>

	void fly(float incr);

	/// <summary>	Rotate yaw. </summary>
	///
	/// <param name="angle">	The angle. </param>

	void rotateYaw(float angle);

	/// <summary>	Rotate pitch. </summary>
	///
	/// <param name="angle">	The angle. </param>

	void rotatePitch(float angle);

	/// <summary>	Gets the yaw. </summary>
	///
	/// <returns>	The yaw. </returns>

	float getYaw();

	/// <summary>	Gets the pitch. </summary>
	///
	/// <returns>	The pitch. </returns>

	float getPitch();

private:


	float m_x, m_y, m_z;   // Position
	float m_lx, m_ly, m_lz; // Direction vector of where we are looking at
	float m_yaw, m_pitch; // Various rotation angles
	float m_strafe_lx, m_strafe_lz; // Always 90 degree to direction vector
	vector3d location;
};

#endif
// End of camera.h
