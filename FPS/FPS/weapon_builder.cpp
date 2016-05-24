#include "weapon_builder.h"

WeaponBuilder WeaponBuilder::setName(string name_p) {
	name = name_p;
	return this;
}
WeaponBuilder WeaponBuilder::setAnimationFrames(vector<unsigned int> animationFrames_p) {
	animationFrames = animationFrames_p;
}

WeaponBuilder WeaponBuilder::setModelId(unsigned int modelId_p) {
	modelId = modelId_p;
}

WeaponBuilder WeaponBuilder::setNormalStateAnimation(unsigned int normalStateAnimation_p) {
	normalStateAnimation = normalStateAnimation_p;
}
WeaponBuilder WeaponBuilder::setFireStateAnimation(unsigned int fireStateAnimation_p) {
	fireStateAnimation = fireStateAnimation_p;
}
WeaponBuilder WeaponBuilder::setReloadStateAnimation(unsigned int reloadStateAnimation_p) {
	reloadStateAnimation = reloadStateAnimation_p;
}
WeaponBuilder WeaponBuilder::setCurrentPosition(vector3d currentPosition_p) {
	currentPosition = currentPosition_p;
}
WeaponBuilder WeaponBuilder::setCurrentRotation(vector3d currentRotation_p) {
	currentRotation = currentRotation_p;
}
WeaponBuilder WeaponBuilder::setPosition(vector3d position_p) {
	position = position_p;
}
WeaponBuilder WeaponBuilder::setRotation(vector3d rotation_p) {
	rotation = rotation_p;
}
WeaponBuilder WeaponBuilder::setMaxMagazineBullets(unsigned int maxMagazineBullets_p) {
	maxMagazineBullets = maxMagazineBullets_p;
}
WeaponBuilder WeaponBuilder::setAllBullets(unsigned int allBullets_p) {
	allBullets = allBullets_p;
}
WeaponBuilder WeaponBuilder::setCurrentState(unsigned int currentState_p) {
	currentState = currentState_p;
}
WeaponBuilder WeaponBuilder::setCurrentAnimationFrame(unsigned int currentAnimationFrame_p) {
	currentAnimationFrame = currentAnimationFrame_p;
}
WeaponBuilder WeaponBuilder::setLastShot(unsigned int lastShot_p) {
	lastShot = lastShot_p;
}