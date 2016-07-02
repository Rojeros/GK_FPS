#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\freeImage\FreeImage.h"
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

/// <summary>	A coordinate. </summary>
struct coordinate {

	/// <summary>	Gets the z coordinate. </summary>
	///
	/// <value>	The z coordinate. </value>

	float x, y, z;

	/// <summary>	Constructor. </summary>
	///
	/// <param name="a">	The float to process. </param>
	/// <param name="b">	The float to process. </param>
	/// <param name="c">	The float to process. </param>

	coordinate(float a, float b, float c);
};

/// <summary>	A face. </summary>
struct face {
	/// <summary>	The facenum. </summary>
	int facenum;
	/// <summary>	true to four. </summary>
	bool four;
	/// <summary>	The faces[ 4]. </summary>
	int faces[4];
	/// <summary>	The texcoord[ 4]. </summary>
	int texcoord[4];
	/// <summary>	The matrix. </summary>
	int mat;

	/// <summary>	Constructor. </summary>
	///
	/// <param name="facen">	The facen. </param>
	/// <param name="f1">   	The first int. </param>
	/// <param name="f2">   	The second int. </param>
	/// <param name="f3">   	The third int. </param>
	/// <param name="t1">   	The first int. </param>
	/// <param name="t2">   	The second int. </param>
	/// <param name="t3">   	The third int. </param>
	/// <param name="m">		The int to process. </param>

	face(int facen, int f1, int f2, int f3, int t1, int t2, int t3, int m);

	/// <summary>	Constructor. </summary>
	///
	/// <param name="facen">	The facen. </param>
	/// <param name="f1">   	The first int. </param>
	/// <param name="f2">   	The second int. </param>
	/// <param name="f3">   	The third int. </param>
	/// <param name="f4">   	The fourth int. </param>
	/// <param name="t1">   	The first int. </param>
	/// <param name="t2">   	The second int. </param>
	/// <param name="t3">   	The third int. </param>
	/// <param name="t4">   	The fourth int. </param>
	/// <param name="m">		The int to process. </param>

	face(int facen, int f1, int f2, int f3, int f4, int t1, int t2, int t3, int t4, int m);
};

/// <summary>	A material. </summary>
struct material {
	/// <summary>	The name. </summary>
	std::string name;

	/// <summary>	Gets the ni. </summary>
	///
	/// <value>	The ni. </value>

	float alpha, ns, ni;

	/// <summary>	Gets the spec[ 3]. </summary>
	///
	/// <value>	The spec[ 3]. </value>

	float dif[3], amb[3], spec[3];
	/// <summary>	The illum. </summary>
	int illum;
	/// <summary>	The texture. </summary>
	int texture;

	/// <summary>	Constructor. </summary>
	///
	/// <param name="na"> 	The na. </param>
	/// <param name="al"> 	The al. </param>
	/// <param name="n">  	The float to process. </param>
	/// <param name="ni2">	The second ni. </param>
	/// <param name="d">  	[in,out] If non-null, the float to process. </param>
	/// <param name="a">  	[in,out] If non-null, the float to process. </param>
	/// <param name="s">  	[in,out] If non-null, the float to process. </param>
	/// <param name="i">  	Zero-based index of the. </param>
	/// <param name="t">  	The int to process. </param>

	material(const char* na, float al, float n, float ni2, float* d, float* a, float* s, int i, int t);
};

/// <summary>	A texcoord. </summary>
struct texcoord {

	/// <summary>	Gets the v. </summary>
	///
	/// <value>	The v. </value>

	float u, v;

	/// <summary>	Constructor. </summary>
	///
	/// <param name="a">	The float to process. </param>
	/// <param name="b">	The float to process. </param>

	texcoord(float a, float b);
};

/// <summary>	An object loader. </summary>
class ObjectLoader {
	/// <summary>	The coordinate. </summary>
	std::vector<std::string*> coord;
	/// <summary>	The vertex. </summary>
	std::vector<coordinate*> vertex;
	/// <summary>	The faces. </summary>
	std::vector<face*> faces;
	/// <summary>	The normals. </summary>
	std::vector<coordinate*> normals;
	/// <summary>	The texture. </summary>
	std::vector<unsigned int> texture;
	/// <summary>	The lists. </summary>
	std::vector<unsigned int> lists;
	/// <summary>	The materials. </summary>
	std::vector<material*> materials;
	/// <summary>	The texturecoordinate. </summary>
	std::vector<texcoord*> texturecoordinate;
	/// <summary>	The vertexnormals. </summary>
	std::vector<coordinate*> vertexnormals;

	/// <summary>	Gets the isvertexnormal. </summary>
	///
	/// <value>	The isvertexnormal. </value>

	bool ismaterial, isnormals, istexture, isvertexnormal;

	/// <summary>	Loads a texture. </summary>
	///
	/// <param name="filename">	Filename of the file. </param>
	///
	/// <returns>	The texture. </returns>

	unsigned int loadTexture(const char* filename);

	/// <summary>	Loads texture image. </summary>
	///
	/// <param name="filename">	Filename of the file. </param>
	///
	/// <returns>	The texture image. </returns>

	GLuint loadTextureImage(const char * filename);

	/// <summary>	Parse file. </summary>
	///
	/// <param name="filename">	Filename of the file. </param>
	///
	/// <returns>	An int. </returns>

	int parseFile(const std::string& filename);

	/// <summary>	Parse vertex. </summary>
	///
	/// <param name="line">	[in,out] If non-null, the line. </param>
	///
	/// <returns>	An int. </returns>

	int parseVertex(std::string* line);

	/// <summary>	Parse normal. </summary>
	///
	/// <param name="line">	[in,out] If non-null, the line. </param>
	///
	/// <returns>	An int. </returns>

	int parseNormal(std::string* line);

	/// <summary>	Parse collision. </summary>
	///
	/// <param name="line">			[in,out] If non-null, the line. </param>
	/// <param name="collplane">	[in,out] If non-null, the collplane. </param>
	///
	/// <returns>	An int. </returns>

	int parseCollision(std::string* line, std::vector<collisionplane>* collplane);

	/// <summary>	Parse face. </summary>
	///
	/// <param name="line">  	[in,out] If non-null, the line. </param>
	/// <param name="curmat">	The curmat. </param>
	///
	/// <returns>	An int. </returns>

	int parseFace(std::string* line, int curmat);

	/// <summary>	Parse material. </summary>
	///
	/// <param name="line">	   	[in,out] If non-null, the line. </param>
	/// <param name="filename">	Filename of the file. </param>
	///
	/// <returns>	An int. </returns>

	int parseMaterial(std::string* line, const std::string& filename);

	/// <summary>	Parse material file. </summary>
	///
	/// <param name="line">	[in,out] If non-null, the line. </param>
	/// <param name="path">	Full pathname of the file. </param>
	/// <param name="tmp"> 	[in,out] If non-null, the temporary. </param>
	///
	/// <returns>	An int. </returns>

	int parseMaterialFile(std::string* line, std::string path, std::vector<std::string>* tmp);

	/// <summary>	Parse texture. </summary>
	///
	/// <param name="line">	[in,out] If non-null, the line. </param>
	///
	/// <returns>	An int. </returns>

	int parseTexture(std::string* line);

	/// <summary>	Parse faces. </summary>
	///
	/// <returns>	An int. </returns>

	int parseFaces();

	/// <summary>	Parse faces. </summary>
	///
	/// <param name="last">	The last. </param>
	/// <param name="i">   	Zero-based index of the. </param>
	///
	/// <returns>	An int. </returns>

	int parseFaces(int last, int i);

	/// <summary>	Parse quads. </summary>
	///
	/// <param name="i">	Zero-based index of the. </param>
	///
	/// <returns>	An int. </returns>

	int parseQuads(int i);

	/// <summary>	Parse triangles. </summary>
	///
	/// <param name="i">	Zero-based index of the. </param>
	///
	/// <returns>	An int. </returns>

	int parseTriangles(int i);


	/// <summary>	Cleans this object. </summary>
	void clean();
	/// <summary>	Smoothnormals this object. </summary>
	void smoothnormals();
	/// <summary>	The loaded textures. </summary>
	std::vector<std::string> loadedTextures;
	/// <summary>	The loaded textures number. </summary>
	std::vector<int> loadedTexturesNum;
	/// <summary>	The out. </summary>
	std::ofstream out;
public:
	/// <summary>	Default constructor. </summary>
	ObjectLoader();
	/// <summary>	Destructor. </summary>
	~ObjectLoader();

	/// <summary>	Loads the given file. </summary>
	///
	/// <param name="filename">		 	Filename of the file. </param>
	/// <param name="collisionplane">	[in,out] If non-null, the collisionplane. </param>
	///
	/// <returns>	An int. </returns>

	int load(const std::string& filename, std::vector<collisionplane>* collisionplane);

	/// <summary>	Loads an animation. </summary>
	///
	/// <param name="anim">			[in,out] The animation. </param>
	/// <param name="filename"> 	Filename of the file. </param>
	/// <param name="frames">   	The frames. </param>
	/// <param name="collplane">	[in,out] If non-null, the collplane. </param>

	void loadAnimation(std::vector<unsigned int>& anim, const std::string filename, int frames, std::vector<collisionplane>* collplane);

	/// <summary>	Loads particle image. </summary>
	///
	/// <param name="filename">	Filename of the file. </param>
	///
	/// <returns>	The particle image. </returns>

	GLuint loadParticleImage(const char* filename);
};