#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <vector>
#include "vector.h"
#include "weapon.h"

using namespace std;

class WeaponBuilder {

	string name;
	vector<unsigned int> animationFrames;
	unsigned int modelId;

	unsigned int normalStateAnimation;	//2,3,4
	unsigned int fireStateAnimation;	//0,1
	unsigned int reloadStateAnimation;	//2,3,4

	bool isFired;
	bool isRealoading;

	vector3d currentPosition;
	vector3d currentRotation;

	vector3d position;
	vector3d rotation;

	int maxMagazineBullets;
	int allBullets;

	unsigned int currentState;
	unsigned int currentAnimationFrame;
	unsigned int lastShot;

public:
	WeaponBuilder setName(string name_p);
	WeaponBuilder setAnimationFrames(vector<unsigned int> animationFrames_p);
	WeaponBuilder setModelId(unsigned int modelId_p);
	WeaponBuilder setNormalStateAnimation(unsigned int normalStateAnimation_p);
	WeaponBuilder setFireStateAnimation(unsigned int fireStateAnimation_p);
	WeaponBuilder setReloadStateAnimation(unsigned int reloadStateAnimation_p);
	WeaponBuilder setCurrentPosition(vector3d currentPosition_p);
	WeaponBuilder setCurrentRotation(vector3d currentRotation_p);
	WeaponBuilder setPosition(vector3d position_p);
	WeaponBuilder setRotation(vector3d rotation_p);
	WeaponBuilder setMaxMagazineBullets(unsigned int maxMagazineBullets_p);
	WeaponBuilder setAllBullets(unsigned int allBullets_p);
	WeaponBuilder setCurrentState(unsigned int currentState_p);
	WeaponBuilder setCurrentAnimationFrame(unsigned int currentAnimationFrame_p);
	WeaponBuilder setLastShot(unsigned int lastShot_p);

	Weapon* build();

};