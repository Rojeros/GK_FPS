#include "weapon.h"
Weapon::Weapon(string name, unsigned int speed, bool isAutomatic,unsigned int power,unsigned int allBullets,unsigned int ammoClip,unsigned int maxMagazineBullets,float precision, float aimprecision ) {
	
	this->precision = precision;
	this->aimprecision = aimprecision;
	
	this->speed = speed;
	this->power = power;
	this->allBullets = allBullets;
	this->ammoClip = ammoClip;
	this->isAutomatic = isAutomatic;
	this->maxMagazineBullets = maxMagazineBullets;
	this->name = name;

	lastShot = 0;
	isAim = false;
	isRealoading = false;
	
	isFired = false;
	currentState = 1;

}

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
void Weapon::setAmmoClip(unsigned int ammoClip_p) {
	ammoClip = ammoClip_p;
}
void Weapon::setAllBullets(unsigned int ammoClip_p) {
	allBullets = ammoClip_p;
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

void Weapon::addAllBullets(unsigned int ammoClip_p)
{
	allBullets += ammoClip_p;
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
unsigned int Weapon::getPower()
{
	return power;
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
unsigned int Weapon::getAmmoClip() {
	return ammoClip;
}
unsigned int Weapon::getAllBullets()
{
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

	
	currentAnimationFrame++;
	if (currentState == 1)
	{
		if (currentAnimationFrame>=normalStateAnimation)
			currentAnimationFrame = 0;
	}
	else if (currentState == 2)
	{
		if (currentAnimationFrame>normalStateAnimation + fireStateAnimation)
		{
			if (isAutomatic && isFired)
			{
				currentAnimationFrame = normalStateAnimation;
			}
			else {
				currentState = 1;
				currentAnimationFrame = 0;
			}
		}
	}
	else if (currentState == 3)
	{
		if (currentAnimationFrame >= normalStateAnimation + fireStateAnimation + reloadStateAnimation - 1)
		{
			currentState = 1;
			currentAnimationFrame = 0;
			isRealoading = false;
		}
	}
	lastShot++;
	currentPosition = newPosition;

}
bool Weapon::fire(vector3d& direction, vector3d& camdirection) {
	if (isRealoading)
		return 0;
	if ((!isAutomatic && !isFired) || isAutomatic)
	{
		
		if (lastShot >= speed)
		{
			if (ammoClip>0)
			{
				if (isAim)
				{
					direction.x = camdirection.x + ((float)(rand() % 2 - 1) / aimprecision);
					direction.y = camdirection.y + ((float)(rand() % 2 - 1) / aimprecision);
					direction.z = camdirection.z + ((float)(rand() % 2 - 1) / aimprecision);
				}
				else {
					direction.x = camdirection.x + ((float)(rand() % 2 - 1) / precision);
					direction.y = camdirection.y + ((float)(rand() % 2 - 1) / precision);
					direction.z = camdirection.z + ((float)(rand() % 2 - 1) / precision);
				}
				isFired = true;
				lastShot = 0;
				ammoClip--;
			
				currentState = 2;
				currentAnimationFrame = normalStateAnimation;

				return 1;
			}

		}
	}
	return 0;
}
void Weapon::nofire()
{
	isFired = false;
}
void Weapon::reload() {
	if ((!isRealoading) && (allBullets > 0) && (ammoClip!=maxMagazineBullets))
	{
		isRealoading = true;
		if (maxMagazineBullets < allBullets) {
			allBullets -= maxMagazineBullets;
			ammoClip = maxMagazineBullets;
		}
		else {
			//niepe³ny magazynek
			ammoClip = allBullets;
			allBullets = 0;
		}

		currentAnimationFrame = normalStateAnimation+fireStateAnimation;
		currentState = 3;
	}
}
void Weapon::show(float angleYaw, float anglePitch) {
	glPushMatrix();
		glTranslatef(currentPosition.x, currentPosition.y, currentPosition.z);
		//glRotatef(angle * 57.2957795, 1, 0, 0);
		glRotatef(-angleYaw * 57.2957795, 0, 1, 0);
		glRotatef(anglePitch * 57.2957795, 0, 0, 1);
		glTranslatef(1.4, -0.6, 0.5);

		glCallList(animationFrames[currentAnimationFrame]);
	glPopMatrix();
}

void Weapon::test(const char key) {

	if (key == 'i') {
		currentPosition.z += 0.05;
	}
	else if (key == 'k') {
		currentPosition.z -= 0.05;
	}
	else if (key == 'j') {
		currentPosition.x -= 0.05;
	}
	else if (key == 'l') {
		currentPosition.x += 0.05;
	}
	else if (key == 'u') {
		currentPosition.y -= 0.05;

	}
	else if (key == 'o') {
		currentPosition.y += 0.05;
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