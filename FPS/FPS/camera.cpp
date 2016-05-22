#include <stdio.h>

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "camera.h"
#include <cmath>
#include "vector.h"
#define M_PI_2 3.14159265358979323846
#define M_PI 1.57079632679489661923

void Camera::init()
{
	m_yaw = 0.0;
	m_pitch = 0.0;

	setPosition(0, 1, 0);
}

void Camera::refresh()
{
	// Camera parameter according to Riegl's co-ordinate system
	// x/y for flat, z for height
	m_lx = cos(m_yaw) * cos(m_pitch);
	m_ly = sin(m_pitch);
	m_lz = sin(m_yaw) * cos(m_pitch);

	m_strafe_lx = cos(m_yaw - M_PI_2);
	m_strafe_lz = sin(m_yaw - M_PI_2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(m_x, m_y, m_z, m_x + m_lx, m_y + m_ly, m_z + m_lz, 0.0, 1.0, 0.0);

	printf("Camera: %f %f %f Direction vector: %f %f %f\n", m_x, m_y, m_z, m_lx, m_ly, m_lz);
}

void Camera::setPosition(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;

	refresh();
}

void Camera::setLocation(vector3d newPosition)
{
	m_x = newPosition.x;
	m_y = newPosition.y;
	m_z = newPosition.z;

	refresh();
}

void Camera::getPosition(float &x, float &y, float &z)
{
	x = m_x;
	y = m_y;
	z = m_z;
}

void Camera::getDirectionVector(float &x, float &y, float &z)
{
	x = m_lx;
	y = m_ly;
	z = m_lz;
}

void Camera::move(float incr)
{

	float lx = cos(m_yaw)*cos(m_pitch);
	float ly = sin(m_pitch);
	float lz = sin(m_yaw)*cos(m_pitch);

	m_x = m_x + incr*lx;
	//	m_y = m_y + incr*ly;
	m_z = m_z + incr*lz;

	refresh();
}

void Camera::strafe(float incr)
{
	float lx = cos(m_yaw)*cos(m_pitch);
	float ly = sin(m_pitch);
	float lz = sin(m_yaw)*cos(m_pitch);


	m_x += -lz*incr;
	m_z += lx*incr;
	refresh();
}

void Camera::fly(float incr)
{
	m_y = m_y + incr;

	refresh();
}

void Camera::rotateYaw(float angle)
{
	m_yaw += angle;

	refresh();
}

void Camera::rotatePitch(float angle)
{
	const float limit = 89.0 * M_PI / 180.0;

	m_pitch += angle;

	if (m_pitch < -limit)
		m_pitch = -limit;

	if (m_pitch > limit)
		m_pitch = limit;

	refresh();
}

void Camera::setYaw(float angle)
{
	m_yaw = angle;

	refresh();
}

void Camera::setPitch(float angle)
{
	m_pitch = angle;

	refresh();
}
