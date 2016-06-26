#include"particle.h"
#include"objectloader.h"
#include <vector>
class Effects {

	particleSystemT raining;
	GLuint rainBitmap;
	
	std::vector<BulletT> bullets;
	GLuint bulletBitmap;
	GLuint fireBitmap;
	
	void initRain(particleSystemT *particleSystem, float GroundHeight, float maxParticleHeight, int maxParticleLifeTime, int width, int height, int number, float speed, float size);
	void freeRain(particleSystemT *particleSystem);
	void renderRain(particleSystemT particleSystem);
	GLuint Effects::loadImage3(const char* filename);



public:
	Effects();
	void initEffects();
	void display();
	void update();
	void delEffects();

	void addBullet(vector3d start,vector3d end,vector3d direction,float speed,float size,float dist);
	void bulletUpdate();
	void bulletDisplay();
	void bulletDelete();
	bool rain;
};