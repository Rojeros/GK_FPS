#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "vector.h"
#include <vector>
#include "collisionplane.h"

/// <summary>	A level, gets all info about level. </summary>
class Level {
	/// <summary>	Identifier for the level. </summary>
	unsigned int levelId;
	/// <summary>	The cp. </summary>
	std::vector<collisionplane> cp;
	/// <summary>	The spawn points. </summary>
	std::vector<vector3d> spawnPoints;
	/// <summary>	The player spawn point. </summary>
	vector3d playerSpawnPoint;
	/// <summary>	The end point. </summary>
	vector3d endPoint;
	/// <summary>	The name. </summary>
	std::string name;
	/// <summary>	true to end. </summary>
	bool end;
	/// <summary>	The width. </summary>
	int width;
	/// <summary>	The height. </summary>
	int height;
	
public:

	/// <summary>	Constructor. </summary>
	///
	/// <param name="lId">		  	The identifier. </param>
	/// <param name="cplane">	  	[in,out] The cplane. </param>
	/// <param name="n">		  	The std::string to process. </param>
	/// <param name="sp">		  	[in,out] The sp. </param>
	/// <param name="pStartPoint">	The start point. </param>
	/// <param name="endp">		  	The endp. </param>
	/// <param name="width">	  	The width. </param>
	/// <param name="height">	  	The height. </param>

	Level(unsigned int lId, std::vector<collisionplane>& cplane, std::string n,std::vector<vector3d>& sp,vector3d pStartPoint,vector3d endp,int width,int height); // std::vector<std::string>& skyImages, 
	/// <summary>	Updates this object. </summary>
	void update();
	/// <summary>	Shows this object. </summary>
	void show();

	/// <summary>	Gets collision planes. </summary>
	///
	/// <returns>	The collision planes. </returns>

	std::vector<collisionplane>& getCollisionPlanes();

	/// <summary>	Gets the name. </summary>
	///
	/// <returns>	The name. </returns>

	std::string& getName();
	

	/// <summary>	Changes. </summary>
	///
	/// <param name="m">	 	The int to process. </param>
	/// <param name="cplane">	[in,out] The cplane. </param>
	/// <param name="n">	 	The std::string to process. </param>

	void change(unsigned int m, std::vector<collisionplane>& cplane, std::string n);// , std::string skyImages[]);

	/// <summary>	Gets spawn points. </summary>
	///
	/// <returns>	null if it fails, else the spawn points. </returns>

	std::vector<vector3d>* getSpawnPoints();

	/// <summary>	Gets random spawn point. </summary>
	///
	/// <returns>	The random spawn point. </returns>

	vector3d getRandomSpawnPoint();

	/// <summary>	Gets player spawn point. </summary>
	///
	/// <returns>	The player spawn point. </returns>

	vector3d getPlayerSpawnPoint();

	/// <summary>	Gets end point. </summary>
	///
	/// <returns>	The end point. </returns>

	vector3d getEndPoint();

	/// <summary>	Sets an end. </summary>
	///
	/// <param name="i">	true to i. </param>

	void setEnd(bool i);

	/// <summary>	Query if this object is end. </summary>
	///
	/// <returns>	true if end, false if not. </returns>

	bool isEnd();

	/// <summary>	Gets the width. </summary>
	///
	/// <returns>	The width. </returns>

	int getWidth();

	/// <summary>	Gets the height. </summary>
	///
	/// <returns>	The height. </returns>

	int getHeight();
};