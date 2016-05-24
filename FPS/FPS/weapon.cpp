#include "weapon.h"

void Weapon::setName(string name_p) {
	name = name_p;
}
void Weapon::setAnimationFrames(vector<unsigned int> animationFrames_p) {
	animationFrames = animationFrames_p;
}

void Weapon::setModelId(unsigned int modelId_p) {
	modelId = modelId_p;
}

void Weapon::setNormalStateAnimation(unsigned int normalStateAnimation_p) {
	normalStateAnimation = normalStateAnimation_p;
}
void Weapon::setFireStateAnimation(unsigned int fireStateAnimation_p) {
	fireStateAnimation = fireStateAnimation_p;
}
void Weapon::setReloadStateAnimation(unsigned int reloadStateAnimation_p) {
	reloadStateAnimation = reloadStateAnimation_p;
}
void Weapon::setCurrentPosition(vector3d currentPosition_p) {
	currentPosition = currentPosition_p;
}
void Weapon::setCurrentRotation(vector3d currentRotation_p) {
	currentRotation = currentRotation_p;
}
void Weapon::setPosition(vector3d position_p) {
	position = position_p;
}
void Weapon::setRotation(vector3d rotation_p) {
	rotation = rotation_p;
}
void Weapon::setMaxMagazineBullets(unsigned int maxMagazineBullets_p) {
	maxMagazineBullets = maxMagazineBullets_p;
}
void Weapon::setAllBullets(unsigned int allBullets_p) {
	allBullets = allBullets_p;
}
void Weapon::setCurrentState(unsigned int currentState_p) {
	currentState = currentState_p;
}
void Weapon::setCurrentAnimationFrame(unsigned int currentAnimationFrame_p) {
	currentAnimationFrame = currentAnimationFrame_p;
}
void Weapon::setLastShot(unsigned int lastShot_p) {
	lastShot = lastShot_p;
}

string Weapon::getName() {
	return name;
}
vector<unsigned int>& Weapon::getAnimationFrames() {
	return animationFrames;
}
unsigned int Weapon::getNormalStateAnimation() {
	return normalStateAnimation;
}
unsigned int Weapon::getFireStateAnimation() {
	return fireStateAnimation;
}
unsigned int Weapon::getReloadStateAnimation() {
	return reloadStateAnimation;
}
vector3d Weapon::getCurrentPosition() {
	return currentPosition;
}
vector3d Weapon::getCurrentRotation() {
	return currentRotation;
}
vector3d Weapon::getPosition() {
	return position;
}
vector3d Weapon::getRotation() {
	return rotation;
}
unsigned int Weapon::getMaxMagazineBullets() {
	return maxMagazineBullets;
}
unsigned int Weapon::getAllBullets() {
	return allBullets;
}
unsigned int Weapon::getCurrentState() {
	return currentState;
}
unsigned int Weapon::getCurrentAnimationFrame() {
	return currentAnimationFrame;
}
unsigned int Weapon::getLastShot() {
	return lastShot;
}


void Weapon::update(vector3d newPosition) {

	/*
	vector3d tmpVec(curpos-curPos);
	tmpVec.normalize();
//		std::cout << "tmpVec: " << tmpVec;
	tmpVec*=0.3;
	curPos+=tmpVec;
	if(std::abs(curPos.x-curpos.x)<0.3 && std::abs(curPos.y-curpos.y)<0.3 && std::abs(curPos.z-curpos.z)<0.3)
		curPos=curpos;
	std::cout << "curpos: " << curPos;
	tmpVec.change(currot-curRot);
	tmpVec.normalize();
	tmpVec*=0.3;
	curRot+=tmpVec;	
	if(std::abs(curRot.x-currot.x)<0.3 && std::abs(curRot.y-currot.y)<0.3 && std::abs(curRot.z-currot.z)<0.3)
		curRot=currot; 
	*/
	
	vector3d temp(newPosition);
	temp.normalize();
	temp *= 0.3;
	currentPosition = temp;
	if (abs(currentPosition.x - position.x) < 0.3 && abs(currentPosition.y - position.y) < 0.3 && abs(currentPosition.z - position.z) < 0.3)
		currentPosition = position;

	
		


}
void Weapon::fire() {

}
void Weapon::reload() {

}
void Weapon::show() {
	glPushMatrix();
		glTranslatef(currentPosition.x, currentPosition.y, currentPosition.z);
		glRotatef(currentRotation.x, 1, 0, 0);
		glRotatef(currentRotation.y, 0, 1, 0);
		glRotatef(currentRotation.z, 0, 0, 1);
		glCallList(animationFrames[currentAnimationFrame]);
	glPopMatrix();
}

void Weapon::test(const char key) {

	if (key == 'i') {
		currentPosition.z += 0.01;
	}
	else if (key == 'k') {
		currentPosition.z -= 0.01;
	}
	else if (key == 'j') {
		currentPosition.x -= 0.01;
	}
	else if (key == 'l') {
		currentPosition.x += 0.01;
	}
	else if (key == 'u') {
		currentPosition.y -= 0.01;

	}
	else if (key == 'o') {
		currentPosition.y += 0.01;
	}

	std::cout << currentPosition.x << " " << currentPosition.y << " " << currentPosition.z << std::endl;

	/*
	if(keys[SDLK_j])
			curpos.x-=0.01;
		if(keys[SDLK_l])
			curpos.x+=0.01;
		if(keys[SDLK_k])
			curpos.z-=0.01;
		if(keys[SDLK_i])
			curpos.z+=0.01;
		if(keys[SDLK_u])
			curpos.y-=0.01;
		if(keys[SDLK_o])
			curpos.y+=0.01;
	*/


}