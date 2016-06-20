#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "vector.h"
#include <vector>
#include "collisionplane.h"

class Level {
	unsigned int levelId;
	std::vector<collisionplane> cp;
	std::vector<vector3d> spawnPoints;
	vector3d playerSpawnPoint;
	vector3d endPoint;
	std::string name;
	bool end;
	//skybox* sky;
public:
	Level(unsigned int lId, std::vector<collisionplane>& cplane, std::string n,std::vector<vector3d>& sp,vector3d pStartPoint,vector3d endp); // std::vector<std::string>& skyImages, 
	void update();
	void show();
	std::vector<collisionplane>& getCollisionPlanes();
	std::string& getName();
	//skybox* getSkybox();
	void change(unsigned int m, std::vector<collisionplane>& cplane, std::string n);// , std::string skyImages[]);
	std::vector<vector3d>* getSpawnPoints();
	vector3d getRandomSpawnPoint();
	vector3d getPlayerSpawnPoint();
	vector3d getEndPoint();
	void setEnd(bool i);
	bool isEnd();
};