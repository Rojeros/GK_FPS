#include"particle.h"
#include"objectloader.h"
#include <vector>
class Effects {

	particleSystemT raining;
	GLuint rainBitmap;
	
	std::vector<BulletT> bullets;
	GLuint bulletBitmap;
	GLuint fireBitmap;
	ObjectLoader* objectLoader;
	
	void initRain(particleSystemT *particleSystem, float GroundHeight, float maxParticleHeight, int maxParticleLifeTime, int width, int height, int number, float speed, float size);
	void freeRain(particleSystemT *particleSystem);
	void renderRain(particleSystemT particleSystem);


public:
	Effects();
	void initEffects();
	void display();
	void update();
	void delEffects();
	void setObjectLoader(ObjectLoader* objL);
	void addBullet(vector3d start,vector3d end,vector3d direction,float speed,float size,float dist);
	void bulletUpdate();
	void bulletDisplay();
	void bulletDelete();
	bool rain;
};