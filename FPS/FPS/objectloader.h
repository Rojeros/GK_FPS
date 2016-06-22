#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "collisionplane.h"
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <map>
#ifndef GL_UNSIGNED_SHORT_5_6_5
#define GL_UNSIGNED_SHORT_5_6_5 0x8363
#endif
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

struct coordinate {
	float x, y, z;
	coordinate(float a, float b, float c);
};

struct face {
	int facenum;
	bool four;
	int faces[4];
	int texcoord[4];
	int mat;
	face(int facen, int f1, int f2, int f3, int t1, int t2, int t3, int m);
	face(int facen, int f1, int f2, int f3, int f4, int t1, int t2, int t3, int t4, int m);
};

struct material {
	std::string name;
	float alpha, ns, ni;
	float dif[3], amb[3], spec[3];
	int illum;
	int texture;
	material(const char* na, float al, float n, float ni2, float* d, float* a, float* s, int i, int t);
};

struct texcoord {
	float u, v;
	texcoord(float a, float b);
};

class ObjectLoader {
	std::vector<std::string*> coord;
	std::vector<coordinate*> vertex;
	std::vector<face*> faces;
	std::vector<coordinate*> normals;
	std::vector<unsigned int> texture;
	std::vector<unsigned int> lists;
	std::vector<material*> materials;
	std::vector<texcoord*> texturecoordinate;
	std::vector<coordinate*> vertexnormals;
	bool ismaterial, isnormals, istexture, isvertexnormal;
	unsigned int loadTexture(const char* filename);
	void clean();
	void smoothnormals();
	std::vector<std::string> loadedTextures;
	std::vector<int> loadedTexturesNum;
	std::ofstream out;
public:
	ObjectLoader();
	~ObjectLoader();
	int load(const std::string& filename, std::vector<collisionplane>* collisionplane);
	void loadAnimation(std::vector<unsigned int>& anim, const std::string filename, int frames);
	GLuint loadImage(const char * filename);
};