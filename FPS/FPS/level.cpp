#include "level.h"


Level::Level(unsigned int lId, std::vector<collisionplane>& cplane, std::string n, std::vector<vector3d>& sp,vector3d pStartPoint,vector3d endp) // std::vector<std::string>& skyImages, 
{
	levelId = lId;
	cp = cplane;
	name = n;
	//sky = new skybox(skyImages[0].c_str(), skyImages[1].c_str(), skyImages[2].c_str(), skyImages[3].c_str(), skyImages[4].c_str(), skyImages[5].c_str());
	spawnPoints = sp;
	playerSpawnPoint = pStartPoint;
	endPoint = endp;
	end = false;
}
void Level::update()
{
	//empty
}
void Level::show()
{
	glCallList(levelId);
}
std::vector<collisionplane>& Level::getCollisionPlanes()
{
	return cp;
}
std::string& Level::getName()
{

	return  name;
}
void Level::change(unsigned int lId, std::vector<collisionplane>& cplane, std::string n) //, std::string skyImages[]
{
	levelId = lId;
	cp = cplane;
	name = n;
	//sky->change(skyImages[0].c_str(), skyImages[1].c_str(), skyImages[2].c_str(), skyImages[3].c_str(), skyImages[4].c_str(), skyImages[5].c_str());
}

/*skybox* map::getSkybox()
{
	return sky;
}*/

std::vector<vector3d>* Level::getSpawnPoints()
{
	return &spawnPoints;
}

vector3d Level::getRandomSpawnPoint()
{
	return (spawnPoints[rand() % spawnPoints.size()]);
}

vector3d Level::getPlayerSpawnPoint()
{
	return playerSpawnPoint;
}

vector3d Level::getEndPoint()
{
	return endPoint;
}

void Level::setEnd(bool i)
{
	end = i;
}

bool Level::isEnd()
{
	return end;
}
