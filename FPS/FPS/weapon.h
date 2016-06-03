#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <vector>
#include "vector.h"

using namespace std;

class Weapon {

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
	void setName(string name_p);
	void setAnimationFrames(vector<unsigned int> animationFrames_p);
	void setModelId(unsigned int modelId_p);
	void setNormalStateAnimation(unsigned int normalStateAnimation_p);
	void setFireStateAnimation(unsigned int fireStateAnimation_p);
	void setReloadStateAnimation(unsigned int reloadStateAnimation_p);
	void setCurrentPosition(vector3d currentPosition_p);
	void setCurrentRotation(vector3d currentRotation_p);
	void setPosition(vector3d position_p);
	void setRotation(vector3d rotation_p);
	void setMaxMagazineBullets(unsigned int maxMagazineBullets_p);
	void setAllBullets(unsigned int allBullets_p);
	void setCurrentState(unsigned int currentState_p);
	void setCurrentAnimationFrame(unsigned int currentAnimationFrame_p);
	void setLastShot(unsigned int lastShot_p);

	string getName();
	vector<unsigned int>& getAnimationFrames();
	unsigned int getNormalStateAnimation();
	unsigned int getFireStateAnimation();
	unsigned int getReloadStateAnimation();
	vector3d getCurrentPosition();
	vector3d getCurrentRotation();
	vector3d getPosition();
	vector3d getRotation();
	unsigned int getMaxMagazineBullets();
	unsigned int getAllBullets();
	unsigned int getCurrentState();
	unsigned int getCurrentAnimationFrame();
	unsigned int getLastShot();


	void update(vector3d newPosition);
	void fire();
	void reload();
	void show(float angleYaw, float anglePitch);

	void test(const char key);

};