#include "effects.h"

Effects::Effects()
{
	
	rain=false;
}

void Effects::setObjectLoader(ObjectLoader* objL) {
	objectLoader = objL;
}

void Effects::initEffects(int width,int height)
{
	rainBitmap = objectLoader->loadParticleImage("Assets/Effects/waterCircle.png");
	bulletBitmap = objectLoader->loadParticleImage("Assets/Effects/fireball.png");
	initRain(&raining, 0, 100.0f, 75, width, height, 500, 1.0f, 1.5f);
}

void Effects::display()
{
	if (rain)
	renderRain(raining);
	
	bulletDisplay();
	dispalyDestroy();
	dispalyTeleport();
}

void Effects::update()
{
	bulletUpdate();
	updateDestroy();
	updateTeleport();
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
			if (abs(tmp.x)<2 &&abs(tmp.y)<2 &&abs(tmp.z)<4) {
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
			glEnable(GL_BLEND);
			
			glBegin(GL_QUADS);
	//		glPushMatrix();
	//			glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	//			glEnable(GL_TEXTURE_GEN_T);
	//		glTranslatef(it->positionInAir.x, it->positionInAir.y, it->positionInAir.z);
	//		glScalef(it->size, it->size, it->size);
			float sizeFactor = it->size*10;
			glColor3f(1, 0, 0);
	
			vector3d normal=(it->positionInAir - it->destination);
			normal.normalize();
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f((it->positionInAir.x - sizeFactor), (it->positionInAir.y + sizeFactor), (it->positionInAir.z));
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f((it->positionInAir.x - sizeFactor), (it->positionInAir.y - sizeFactor), (it->positionInAir.z));
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f((it->positionInAir.x +sizeFactor), (it->positionInAir.y - sizeFactor), (it->positionInAir.z ));
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f((it->positionInAir.x + sizeFactor), (it->positionInAir.y + sizeFactor), (it->positionInAir.z));
		
			glEnd();
	//		glPopMatrix();

	//			glDisable(GL_TEXTURE_GEN_S); //disable texture coordinate generation
	//			glDisable(GL_TEXTURE_GEN_T);
			glDisable(GL_BLEND);
	//		it->size += 0.5;
		
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
			
			glEnable(GL_TEXTURE_2D);
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

void Effects::destroyEnemy(vector3d point,int partitions)
{
	for (int i = 0; i < partitions; i++) {
		vector3d r(rand() % 100 - 50, rand() % 100 - 50, rand() % 100 - 50);
		r.normalize();
		destroy.push_back(BulletT(point, vector3d(0, 0, 0), r, 0.1, 1, false,30));
	}
	
}

void Effects::dispalyDestroy()
{
	for (std::vector<BulletT>::iterator it = destroy.begin(); it != destroy.end(); ++it) {
		glPushMatrix();
	
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glPushMatrix();
		glTranslatef(it->positionInAir.x, it->positionInAir.y, it->positionInAir.z);
		glScalef(it->size, it->size, it->size);
		glColor3f(1,0,0);
		//	glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
		//	glEnable(GL_TEXTURE_GEN_T);
		//	glBindTexture(GL_TEXTURE_2D, bulletBitmap);
		glutSolidCube(1);
		//	glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
		//	glDisable(GL_TEXTURE_GEN_T);
		glPopMatrix();
		glDisable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		if(it->size>0.02)
		it->size -= 0.01;
	
	}

}

void Effects::updateDestroy()
{
	for (std::vector<BulletT>::iterator it = destroy.begin(); it != destroy.end(); ++it) {
		it->positionInAir = it->positionInAir +it->direction* it->speed;
		it->life++;
		if (it->life > it->maxTimer)
			it->boom = true;
		if (it->positionInAir.y < 0) {
			it->boom = true;
		}
	}
	deleteDestroy();

}

void Effects::deleteDestroy()
{
	std::vector<BulletT>::iterator it = destroy.begin();
	while (it != destroy.end()) {
		if (it->boom==true) {
			it = destroy.erase(it);
		}
		else {
			it++;
		}
	}

}

void Effects::teleportEnemy(vector3d point,int ray,int partitions)
{
	double part;
	part =  360/(double)partitions ;
	double partial=0;

	vector3d n(0, 1, 0);
	n.normalize();
	vector3d tmp;
	for (int i = 0; i < partitions; i++) {
		partial = i*part;
		tmp=vector3d(0, 0, 0);
			tmp.x = sin(partial)*ray+point.x;
			tmp.z = cos(partial)*ray+point.z;

			teleport.push_back(BulletT(tmp, vector3d(0, 0, 0), n, 0.05, 1, false, 40));
	}
}

void Effects::dispalyTeleport()
{
	for (std::vector<BulletT>::iterator it = teleport.begin(); it != teleport.end(); ++it) {
		glPushMatrix();

		glDisable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glPushMatrix();
		glTranslatef(it->positionInAir.x, it->positionInAir.y, it->positionInAir.z);
		glScalef(it->size, it->size, it->size);
		glColor3f(0.3, 0.3, 1);
		//	glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
		//	glEnable(GL_TEXTURE_GEN_T);
		//	glBindTexture(GL_TEXTURE_2D, bulletBitmap);
		glutSolidCube(1);
		//	glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
		//	glDisable(GL_TEXTURE_GEN_T);
		glPopMatrix();
		glDisable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);

	}
}

void Effects::updateTeleport()
{
	for (std::vector<BulletT>::iterator it = teleport.begin(); it != teleport.end(); ++it) {
		//it->positionInAir.x = (it->positionInAir.x + (rand()%20-10)*0.01)*0.01* it->speed*it->direction.z;
		it->positionInAir.y = it->positionInAir.y + it->speed*(rand() % 20)*0.02*it->direction.y;
		//it->positionInAir.z = (it->positionInAir.z + (rand() % 20 - 10)*0.01)* it->speed*it->direction.z;
		it->life++;
		if (it->life > it->maxTimer)
			it->boom = true;
		
	}
	deleteTeleport();
}

void Effects::deleteTeleport()
{
	std::vector<BulletT>::iterator it = teleport.begin();
	while (it != teleport.end()) {
		if (it->boom == true) {
			it = teleport.erase(it);
		}
		else {
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
