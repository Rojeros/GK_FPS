#include"particle.h"
#include"objectloader.h"
#include <vector>
/// <summary>	Create and displaying effects on screen. </summary>
class Effects {

	/// <summary>	The raining. </summary>
	particleSystemT raining;
	/// <summary>	The rain bitmap. </summary>
	GLuint rainBitmap;
	
	/// <summary>	The bullets. </summary>
	std::vector<BulletT> bullets;
	/// <summary>	The destroy. </summary>
	std::vector<BulletT> destroy;
	/// <summary>	The teleport. </summary>
	std::vector<BulletT> teleport;
	/// <summary>	The bullet bitmap. </summary>
	GLuint bulletBitmap;
	/// <summary>	The fire bitmap. </summary>
	GLuint fireBitmap;
	/// <summary>	The object loader. </summary>
	ObjectLoader* objectLoader;

	/// <summary>	Init rain. </summary>
	///
	/// <param name="particleSystem">	  	[in,out] If non-null, the particle system. </param>
	/// <param name="GroundHeight">		  	Height of the ground. </param>
	/// <param name="maxParticleHeight">  	The maximum particle height. </param>
	/// <param name="maxParticleLifeTime">	The maximum particle life time. </param>
	/// <param name="width">			  	The width. </param>
	/// <param name="height">			  	The height. </param>
	/// <param name="number">			  	Number of. </param>
	/// <param name="speed">			  	The speed. </param>
	/// <param name="size">				  	The size. </param>

	void initRain(particleSystemT *particleSystem, float GroundHeight, float maxParticleHeight, int maxParticleLifeTime, int width, int height, int number, float speed, float size);

	/// <summary>	Free rain. </summary>
	///
	/// <param name="particleSystem">	[in,out] If non-null, the particle system. </param>

	void freeRain(particleSystemT *particleSystem);

	/// <summary>	Renders the rain described by particleSystem. </summary>
	///
	/// <param name="particleSystem">	The particle system. </param>

	void renderRain(particleSystemT particleSystem);


public:
	/// <summary>	Default constructor. </summary>
	Effects();

	/// <summary>	Init effects. </summary>
	///
	/// <param name="width"> 	The width. </param>
	/// <param name="height">	The height. </param>

	void initEffects(int width,int height);
	/// <summary>	Displays this object. </summary>
	void display();
	/// <summary>	Updates this object. </summary>
	void update();
	/// <summary>	Deletes the effects. </summary>
	void delEffects();

	/// <summary>	Sets object loader. </summary>
	///
	/// <param name="objL">	[in,out] If non-null, the object l. </param>

	void setObjectLoader(ObjectLoader* objL);

	/// <summary>	Adds a bullet. </summary>
	///
	/// <param name="start">		The start. </param>
	/// <param name="end">			The end. </param>
	/// <param name="direction">	The direction. </param>
	/// <param name="speed">		The speed. </param>
	/// <param name="size">			The size. </param>
	/// <param name="dist">			The distance. </param>

	void addBullet(vector3d start,vector3d end,vector3d direction,float speed,float size,float dist);
	/// <summary>	Bullet update. </summary>
	void bulletUpdate();
	/// <summary>	Bullet display. </summary>
	void bulletDisplay();
	/// <summary>	Bullet delete. </summary>
	void bulletDelete();

	/// <summary>	Destroys the enemy described by point. </summary>
	///
	/// <param name="point">	The point. </param>

	void destroyEnemy(vector3d point,int partitions);
	/// <summary>	Dispaly destroy. </summary>
	void dispalyDestroy();
	/// <summary>	Updates the destroy. </summary>
	void updateDestroy();
	/// <summary>	Deletes the destroy. </summary>
	void deleteDestroy();

	/// <summary>	Teleport enemy. </summary>
	///
	/// <param name="point">	The point. </param>
	/// <param name="ray">  	The ray. </param>

	void teleportEnemy(vector3d point,int ray,int partitions);
	/// <summary>	Dispaly teleport. </summary>
	void dispalyTeleport();
	/// <summary>	Updates the teleport. </summary>
	void updateTeleport();
	/// <summary>	Deletes the teleport. </summary>
	void deleteTeleport();
	/// <summary>	true to rain. </summary>
	bool rain;
};