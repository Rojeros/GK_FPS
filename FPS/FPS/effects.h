#include"particle.h"
#include"objectloader.h"
class Effects {

	particleSystemT raining;
	GLuint rainBitmap;
	
	void initRain(particleSystemT *particleSystem, float GroundHeight, float maxParticleHeight, int maxParticleLifeTime, int width, int height, int number, float speed, float size);
	void freeRain(particleSystemT *particleSystem);
	void renderRain(particleSystemT particleSystem);
	GLuint Effects::loadImage3(const char* filename);
public:
	Effects();
	void initEffects();
	void display();
	void delEffects();

	bool rain;
};