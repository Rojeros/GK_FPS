#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <vector>
#include "vector.h"

using namespace std;

/// <summary>	A weapon class, displaying weapon on screen, get information about ammo, speed, clip. </summary>
class Weapon {

	/// <summary>	The name. </summary>
	string name;
	/// <summary>	The animation frames. </summary>
	vector<unsigned int> animationFrames;
	/// <summary>	Identifier for the model. </summary>
	unsigned int modelId;

	/// <summary>	2,3,4. </summary>
	unsigned int normalStateAnimation;
	/// <summary>	0,1. </summary>
	unsigned int fireStateAnimation;
	/// <summary>	2,3,4. </summary>
	unsigned int reloadStateAnimation;

	/// <summary>	all bullets. </summary>
	unsigned int allBullets;

	/// <summary>	true if this object is fired. </summary>
	bool isFired;
	/// <summary>	true if this object is realoading. </summary>
	bool isRealoading;
	/// <summary>	true if this object is aim. </summary>
	bool isAim;
	/// <summary>	true if this object is automatic. </summary>
	bool isAutomatic;


	vector3d currentPosition;
	/// <summary>	The current rotation. </summary>
	vector3d currentRotation;

	/// <summary>	The position. </summary>
	vector3d position;
	/// <summary>	The rotation. </summary>
	vector3d rotation;

	/// <summary>	The maximum magazine bullets. </summary>
	int maxMagazineBullets;

	/// <summary>	The ammo clip. </summary>
	int ammoClip;
	/// <summary>	The lastshot. </summary>
	unsigned int lastshot;
	/// <summary>	The speed. </summary>
	unsigned int speed;
	/// <summary>	The precision. </summary>
	float precision;
	/// <summary>	The aimprecision. </summary>
	float aimprecision;
	/// <summary>	The power. </summary>
	unsigned int power;

	/// <summary>	The current state. </summary>
	unsigned int currentState;
	/// <summary>	The current animation frame. </summary>
	unsigned int currentAnimationFrame;
	/// <summary>	The last shot. </summary>
	unsigned int lastShot;

public:

	/// <summary>	Constructor. </summary>
	///
	/// <param name="name">				 	The name. </param>
	/// <param name="speed">			 	The speed. </param>
	/// <param name="isAutomatic">		 	true if this object is automatic. </param>
	/// <param name="power">			 	The power. </param>
	/// <param name="allBullets">		 	all bullets. </param>
	/// <param name="ammoClip">			 	The ammo clip. </param>
	/// <param name="maxMagazineBullets">	The maximum magazine bullets. </param>
	/// <param name="precision">		 	The precision. </param>
	/// <param name="aimprecision">		 	The aimprecision. </param>

	Weapon(string name, unsigned int speed, bool isAutomatic, unsigned int power, unsigned int allBullets, unsigned int ammoClip, unsigned int maxMagazineBullets,float precision, float aimprecision);

	/// <summary>	Sets a name. </summary>
	///
	/// <param name="name_p">	The name p. </param>

	void setName(string name_p);

	/// <summary>	Sets animation frames. </summary>
	///
	/// <param name="animationFrames_p">	The animation frames p. </param>

	void setAnimationFrames(vector<unsigned int> animationFrames_p);

	/// <summary>	Sets model identifier. </summary>
	///
	/// <param name="modelId_p">	The model identifier p. </param>

	void setModelId(unsigned int modelId_p);

	/// <summary>	Sets normal state animation. </summary>
	///
	/// <param name="normalStateAnimation_p">	The normal state animation p. </param>

	void setNormalStateAnimation(unsigned int normalStateAnimation_p);

	/// <summary>	Sets fire state animation. </summary>
	///
	/// <param name="fireStateAnimation_p">	The fire state animation p. </param>

	void setFireStateAnimation(unsigned int fireStateAnimation_p);

	/// <summary>	Sets reload state animation. </summary>
	///
	/// <param name="reloadStateAnimation_p">	The reload state animation p. </param>

	void setReloadStateAnimation(unsigned int reloadStateAnimation_p);

	/// <summary>	Sets current position. </summary>
	///
	/// <param name="currentPosition_p">	The current position p. </param>

	void setCurrentPosition(vector3d currentPosition_p);

	/// <summary>	Sets current rotation. </summary>
	///
	/// <param name="currentRotation_p">	The current rotation p. </param>

	void setCurrentRotation(vector3d currentRotation_p);

	/// <summary>	Sets a position. </summary>
	///
	/// <param name="position_p">	The position p. </param>

	void setPosition(vector3d position_p);

	/// <summary>	Sets a rotation. </summary>
	///
	/// <param name="rotation_p">	The rotation p. </param>

	void setRotation(vector3d rotation_p);

	/// <summary>	Sets maximum magazine bullets. </summary>
	///
	/// <param name="maxMagazineBullets_p">	The maximum magazine bullets p. </param>

	void setMaxMagazineBullets(unsigned int maxMagazineBullets_p);

	/// <summary>	Sets all bullets. </summary>
	///
	/// <param name="ammoClip_p">	The ammo clip. </param>

	void setAllBullets(unsigned int ammoClip_p);

	/// <summary>	Sets ammo clip. </summary>
	///
	/// <param name="ammoClip_p">	The ammo clip. </param>

	void setAmmoClip(unsigned int ammoClip_p);

	/// <summary>	Sets current state. </summary>
	///
	/// <param name="currentState_p">	The current state p. </param>

	void setCurrentState(unsigned int currentState_p);

	/// <summary>	Sets current animation frame. </summary>
	///
	/// <param name="currentAnimationFrame_p">	The current animation frame p. </param>

	void setCurrentAnimationFrame(unsigned int currentAnimationFrame_p);

	/// <summary>	Sets last shot. </summary>
	///
	/// <param name="lastShot_p">	The last shot p. </param>

	void setLastShot(unsigned int lastShot_p);

	/// <summary>	Adds all bullets. </summary>
	///
	/// <param name="ammoClip_p">	The ammo clip. </param>

	void addAllBullets(unsigned int ammoClip_p);

	/// <summary>	Gets the name. </summary>
	///
	/// <returns>	The name. </returns>

	string getName();

	/// <summary>	Gets animation frames. </summary>
	///
	/// <returns>	The animation frames. </returns>

	vector<unsigned int>& getAnimationFrames();

	/// <summary>	Gets normal state animation. </summary>
	///
	/// <returns>	The normal state animation. </returns>

	unsigned int getNormalStateAnimation();

	/// <summary>	Gets fire state animation. </summary>
	///
	/// <returns>	The fire state animation. </returns>

	unsigned int getFireStateAnimation();

	/// <summary>	Gets reload state animation. </summary>
	///
	/// <returns>	The reload state animation. </returns>

	unsigned int getReloadStateAnimation();

	/// <summary>	Gets the power. </summary>
	///
	/// <returns>	The power. </returns>

	unsigned int getPower();

	/// <summary>	Gets current position. </summary>
	///
	/// <returns>	The current position. </returns>

	vector3d getCurrentPosition();

	/// <summary>	Gets current rotation. </summary>
	///
	/// <returns>	The current rotation. </returns>

	vector3d getCurrentRotation();

	/// <summary>	Gets the position. </summary>
	///
	/// <returns>	The position. </returns>

	vector3d getPosition();

	/// <summary>	Gets the rotation. </summary>
	///
	/// <returns>	The rotation. </returns>

	vector3d getRotation();

	/// <summary>	Gets maximum magazine bullets. </summary>
	///
	/// <returns>	The maximum magazine bullets. </returns>

	unsigned int getMaxMagazineBullets();

	/// <summary>	Gets ammo clip. </summary>
	///
	/// <returns>	The ammo clip. </returns>

	unsigned int getAmmoClip();

	/// <summary>	Gets all bullets. </summary>
	///
	/// <returns>	all bullets. </returns>

	unsigned int getAllBullets();

	/// <summary>	Gets current state. </summary>
	///
	/// <returns>	The current state. </returns>

	unsigned int getCurrentState();

	/// <summary>	Gets current animation frame. </summary>
	///
	/// <returns>	The current animation frame. </returns>

	unsigned int getCurrentAnimationFrame();

	/// <summary>	Gets the last shot. </summary>
	///
	/// <returns>	The last shot. </returns>

	unsigned int getLastShot();

	/// <summary>	Updates the given newPosition. </summary>
	///
	/// <param name="newPosition">	The new position. </param>

	void update(vector3d newPosition);

	/// <summary>	Fires. </summary>
	///
	/// <param name="direction">   	[in,out] The direction. </param>
	/// <param name="camdirection">	[in,out] The camdirection. </param>
	///
	/// <returns>	true if it succeeds, false if it fails. </returns>

	bool fire(vector3d& direction, vector3d& camdirection);
	/// <summary>	Nofires this object. </summary>
	void nofire();
	/// <summary>	Reloads this object. </summary>
	void reload();

	/// <summary>	Shows. </summary>
	///
	/// <param name="angleYaw">  	The angle yaw. </param>
	/// <param name="anglePitch">	The angle pitch. </param>

	void show(float angleYaw, float anglePitch);

};