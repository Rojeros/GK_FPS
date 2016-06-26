#include "effects.h"

Effects::Effects()
{
	
	rain=false;
}

void Effects::initEffects()
{
	rainBitmap = loadImage3("Assets\\Effects\\waterCircle.png");
	bulletBitmap = loadImage3("Assets\\Effects\\fireball.png");
	initRain(&raining, 0, 100.0f, 75, 35, 35, 500, 1.0f, 1.5f);
}

void Effects::display()
{
	if (rain)
	renderRain(raining);

	bulletDisplay();
}

void Effects::update()
{
	bulletUpdate();
}

void Effects::delEffects()
{
	freeRain(&raining);
}

void Effects::addBullet(vector3d start, vector3d end, vector3d direction, float speed, float size,float dist)
{
	bool t=false;
	int timer = 0;
	if (end.x == 0&& end.y == 0&& end.z == 0) {
		t = true;
	}
	bullets.push_back(BulletT(start, end, direction, size, speed,t,timer));
}

void Effects::bulletUpdate()
{
	for (std::vector<BulletT>::iterator it = bullets.begin(); it != bullets.end(); ++it) {

		if (!it->boom) {
			vector3d tmp;
			tmp = vector3d(abs(it->destination.x) -abs( it->positionInAir.x), abs(it->destination.y) - abs(it->positionInAir.y), abs(it->destination.z) - abs(it->positionInAir.z));
			if (abs(tmp.x)<1 &&abs(tmp.y)<1 &&abs(tmp.z)<1) {
				it->life++;

			}
			else {
				it->positionInAir = it->positionInAir + (it->direction * it->speed);

			}
		}

		else {
			it->positionInAir = it->positionInAir + (it->direction * it->speed);
			it->life++;
		}
	}
	bulletDelete();
}

void Effects::bulletDisplay()
{

	

	
	for (std::vector<BulletT>::iterator it = bullets.begin(); it != bullets.end(); ++it) {
		if (!it->boom) {
		
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, bulletBitmap);
			//glEnable(GL_BLEND);
			

			glPushMatrix();
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
				glEnable(GL_TEXTURE_GEN_T);
			glTranslatef(it->positionInAir.x, it->positionInAir.y, it->positionInAir.z);
			glScalef(it->size, it->size, it->size);
			glColor3f(1, 1, 1);

			glutSolidCube(2);
			glPopMatrix();

				glDisable(GL_TEXTURE_GEN_S); //disable texture coordinate generation
				glDisable(GL_TEXTURE_GEN_T);
			glDisable(GL_BLEND);
			it->size += 0.5;
		
		}
		else {
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glPushMatrix();
			glTranslatef(it->positionInAir.x, it->positionInAir.y, it->positionInAir.z);
			glScalef(it->size, it->size, it->size);
			glColor4f(0.8, 0.8, 0.8, 1);
			//	glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
			//	glEnable(GL_TEXTURE_GEN_T);
			//	glBindTexture(GL_TEXTURE_2D, bulletBitmap);
			glutSolidCube(2);
			//	glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
			//	glDisable(GL_TEXTURE_GEN_T);
			glPopMatrix();
			glDisable(GL_BLEND);
			it->size -= 0.01;
		}
	}
	

	

	glEnable(GL_TEXTURE_2D);
}

void Effects::bulletDelete()
{
	std::vector<BulletT>::iterator it = bullets.begin();
	while (it != bullets.end()) {
		if (it->life > 100) {
			it = bullets.erase(it);
		}
		else{
			it++;
		}
	}
}

void Effects::initRain(particleSystemT *particleSystem, float GroundHeight, float maxParticleHeight, int maxParticleLifeTime, int width, int height, int number, float speed, float size)
{
	int i;

	particleSystem->GroundHeight = GroundHeight;
	particleSystem->maxParticleHeight = maxParticleHeight;
	particleSystem->maxParticleLifeTime = maxParticleLifeTime;
	particleSystem->width = width;
	particleSystem->height = height;
	particleSystem->number = number;
	particleSystem->speed = speed;
	particleSystem->size = size;
	particleSystem->particles = (particleT*)malloc(sizeof(particleT) * number);

	for (i = 0; i < number; i++)
	{
		particleSystem->particles[i].visible = 0;
		particleSystem->particles[i].FirstLifeTime = 0;

		particleSystem->particles[i].positionInAir.x = (float)(rand() % width * 2 - width);
		particleSystem->particles[i].positionInAir.y = (float)(rand() % (int)maxParticleHeight);
		particleSystem->particles[i].positionInAir.z = (float)(rand() % height * 2 - height);
	}
}



void Effects::freeRain(particleSystemT *particleSystem)
{
	free(particleSystem->particles);
}



void Effects::renderRain(particleSystemT particleSystem)
{
	int i;



	glDisable(GL_TEXTURE_2D);
	glLineWidth(2.0f);
	glColor3f(0.75f, 0.75f, 0.75f);
	glBegin(GL_LINES);
	for (i = 0; i < particleSystem.number; i++)
	{
		particleSystem.particles[i].positionInAir.y -= particleSystem.speed;
		if (particleSystem.particles[i].positionInAir.y < particleSystem.GroundHeight)
		{
			particleSystem.particles[i].visible = 1;
			particleSystem.particles[i].FirstLifeTime = 0;

			particleSystem.particles[i].positionOnGround.x = particleSystem.particles[i].positionInAir.x;
			particleSystem.particles[i].positionOnGround.y = particleSystem.particles[i].positionInAir.y;
			particleSystem.particles[i].positionOnGround.z = particleSystem.particles[i].positionInAir.z;

			particleSystem.particles[i].positionInAir.x = (float)(rand() % particleSystem.width * 2 - particleSystem.width);
			particleSystem.particles[i].positionInAir.y = particleSystem.maxParticleHeight;
			particleSystem.particles[i].positionInAir.z = (float)((rand() % particleSystem.height) * 2 - particleSystem.height);
		}

		glVertex3f(particleSystem.particles[i].positionInAir.x, particleSystem.particles[i].positionInAir.y, particleSystem.particles[i].positionInAir.z);
		glVertex3f(particleSystem.particles[i].positionInAir.x, particleSystem.particles[i].positionInAir.y + particleSystem.size, particleSystem.particles[i].positionInAir.z);
	}
	glEnd();

	//	glEnable(GL_DEPTH_TEST);
	//	glEnable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, rainBitmap);
	glBegin(GL_QUADS);
	for (i = 0; i < particleSystem.number; i++)
	{
		particleSystem.particles[i].FirstLifeTime++;

		if (particleSystem.particles[i].visible)
		{
			float sizeFactor = (float)(particleSystem.particles[i].FirstLifeTime);

			glColor4f(1.0f, 1.0f, 1.0f, 1.0f - ((float)particleSystem.particles[i].FirstLifeTime / (float)particleSystem.maxParticleLifeTime));

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(particleSystem.particles[i].positionOnGround.x - 0.01f*sizeFactor, particleSystem.GroundHeight, particleSystem.particles[i].positionOnGround.z - 0.01f*sizeFactor);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(particleSystem.particles[i].positionOnGround.x - 0.01f*sizeFactor, particleSystem.GroundHeight, particleSystem.particles[i].positionOnGround.z + 0.01f*sizeFactor);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(particleSystem.particles[i].positionOnGround.x + 0.01f*sizeFactor, particleSystem.GroundHeight, particleSystem.particles[i].positionOnGround.z + 0.01f*sizeFactor);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(particleSystem.particles[i].positionOnGround.x + 0.01f*sizeFactor, particleSystem.GroundHeight, particleSystem.particles[i].positionOnGround.z - 0.01f*sizeFactor);
		}

		if (particleSystem.particles[i].FirstLifeTime > particleSystem.maxParticleLifeTime)
		{
			particleSystem.particles[i].visible = 0;
		}
	}

	glEnd();
	glDisable(GL_BLEND);
}
GLuint Effects::loadImage3(const char* filename)
{
	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);
	//OpenGL's image ID to map to
	GLuint texture;

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	//if still unkown, return failure
	if (fif == FIF_UNKNOWN)
		return false;

	std::cout << "FIF " << fif << std::endl;

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	//if the image failed to load, return failure
	if (!dib)
		return false;

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (width == 0) || (height == 0))
		return false;

	//if this texture ID is in use, unload the current texture
	try {
	//generate an OpenGL texture ID for this texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, bits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//free(bits);
	}
	catch (...) {
		return 100;
	}
	//Free FreeImage's copy of the data
	FreeImage_Unload(dib);

	//return successzz
	return texture;
}