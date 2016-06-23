#include "objectloader.h"

coordinate::coordinate(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}
face::face(int facen, int f1, int f2, int f3, int t1, int t2, int t3, int m) {
	facenum = facen;
	faces[0] = f1;
	faces[1] = f2;
	faces[2] = f3;
	texcoord[0] = t1;
	texcoord[1] = t2;
	texcoord[2] = t3;
	mat = m;
	four = false;
}
face::face(int facen, int f1, int f2, int f3, int f4, int t1, int t2, int t3, int t4, int m) {
	facenum = facen;
	faces[0] = f1;
	faces[1] = f2;
	faces[2] = f3;
	faces[3] = f4;
	texcoord[0] = t1;
	texcoord[1] = t2;
	texcoord[2] = t3;
	texcoord[3] = t4;
	mat = m;
	four = true;
}

material::material(const char* na, float al, float n, float ni2, float* d, float* a, float* s, int i, int t)
{
	name = na;
	alpha = al;
	ni = ni2;
	ns = n;
	dif[0] = d[0];
	dif[1] = d[1];
	dif[2] = d[2];

	amb[0] = a[0];
	amb[1] = a[1];
	amb[2] = a[2];

	spec[0] = s[0];
	spec[1] = s[1];
	spec[2] = s[2];

	illum = i;
	texture = t;
}

texcoord::texcoord(float a, float b)
{
	u = a;
	v = b;
}

void ObjectLoader::clean()
{
	for (int i = 0; i<coord.size(); i++)
		delete coord[i];
	for (int i = 0; i<faces.size(); i++)
		delete faces[i];
	for (int i = 0; i<normals.size(); i++)
		delete normals[i];
	for (int i = 0; i<vertex.size(); i++)
		delete vertex[i];
	for (int i = 0; i<materials.size(); i++)
		delete materials[i];
	for (int i = 0; i<texturecoordinate.size(); i++)
		delete texturecoordinate[i];
	for (int i = 0; i<vertexnormals.size(); i++)
		delete vertexnormals[i];
	coord.clear();
	faces.clear();
	normals.clear();
	vertex.clear();
	materials.clear();
	texturecoordinate.clear();
	vertexnormals.clear();
}

ObjectLoader::~ObjectLoader()
{
	for (std::vector<unsigned int>::const_iterator it = texture.begin(); it != texture.end(); it++)
	{
		glDeleteTextures(1, &(*it));
	}
	for (std::vector<unsigned int>::const_iterator it = lists.begin(); it != lists.end(); it++)
	{
		glDeleteLists(*it, 1);
	}
}

GLuint ObjectLoader::loadImage(const char * filename)
{

	GLuint texture;

	int width, height;

	unsigned char * data;

	FILE * file;

	fopen_s(&file, filename, "rb");

	if (file == NULL) {
		return 0;
	}

	width = 1024;
	height = 1024;
	data = (unsigned char *)malloc(width * height * 3);
	//int size = fseek(file,);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i < width * height; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;

	}


	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);


	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);

	return texture;
}

GLuint ObjectLoader::loadImage2(const char* filename)
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

	std::cout << width << " " << height << std::endl;
	//if this texture ID is in use, unload the current texture

	//generate an OpenGL texture ID for this texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);


	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	int result = gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, bits);
	
	std::cout << "MIP MAP IS CREATED " << result << std::endl;
	
	//free(bits);

	//Free FreeImage's copy of the data
	FreeImage_Unload(dib);

	//return success
	return texture;
}

unsigned int ObjectLoader::loadTexture(const char* filename)
{
	GLuint texture = loadImage2(filename);
	std::cout << "TEXTURE LOADED " << filename << " WITH ID " << texture << std::endl;
	glBindTexture(GL_TEXTURE_2D, texture);
	loadedTextures.push_back(filename);
	loadedTexturesNum.push_back(texture);
	return texture;
}

ObjectLoader::ObjectLoader()
{
	ismaterial = false;
	isnormals = false;
	istexture = false;
	isvertexnormal = false;
}

void ObjectLoader::smoothnormals()
{
	for (int i = 1; i<vertex.size() + 1; i++)
	{
		float vecX = 0.0, vecY = 0.0, vecZ = 0.0;
		int num = 0;
		for (int j = 0; j<faces.size(); j++)
		{
			if (faces[j]->faces[0] == i || faces[j]->faces[1] == i || faces[j]->faces[2] == i || faces[j]->faces[3] == i)
			{
				vecX += normals[faces[j]->facenum - 1]->x;
				vecY += normals[faces[j]->facenum - 1]->y;
				vecZ += normals[faces[j]->facenum - 1]->z;
				num++;
			}
		}
		if (num)
		{
			vecX /= num;
			vecY /= num;
			vecZ /= num;
		}
		float d = sqrt(vecX*vecX + vecY*vecY + vecZ*vecZ);
		if (d)
		{
			vecX /= d;
			vecY /= d;
			vecZ /= d;
		}
		vertexnormals.push_back(new coordinate(vecX, vecY, vecZ));
	}
}

int ObjectLoader::load(const std::string& filename, std::vector<collisionplane>* collplane)
{
	ismaterial = false;
	isnormals = false;
	istexture = false;
	isvertexnormal = false;
	std::ifstream in(filename.c_str());
	if (!in.is_open())
	{
		return -1;
	}
	std::string path = filename.substr(0, ((filename.find_last_of('/') + 1 != std::string::npos) ? (filename.find_last_of('/') + 1) : 0));
	char buf[10000];
	int curmat = 0;
	bool coll = false;
	int z = 0;
	int h = -1;
	int xx = 0;
	while (!in.eof())
	{
		//xx++;
		//std::cout << xx << std::endl;
		in.getline(buf, 10000);
		//std::cout << buf << std::endl;
		coord.push_back(new std::string(buf));
	}
	for (int i = 0; i<coord.size(); i++)
	{
		if ((*coord[i])[0] == '#')
			continue;
		else if ((*coord[i])[0] == 'v' && (*coord[i])[1] == ' ')
		{
			float tmpx, tmpy, tmpz;
			sscanf_s(coord[i]->c_str(), "v %f %f %f", &tmpx, &tmpy, &tmpz);
			vertex.push_back(new coordinate(tmpx, tmpy, tmpz));
		}
		else if ((*coord[i])[0] == 'v' && (*coord[i])[1] == 'n')
		{
			float tmpx, tmpy, tmpz;
			sscanf_s(coord[i]->c_str(), "vn %f %f %f", &tmpx, &tmpy, &tmpz);
			normals.push_back(new coordinate(tmpx, tmpy, tmpz));
		}
		else if ((*coord[i])[0] == 'f')
		{
			int a, b, c, d, e;
			if (coll && collplane != NULL)
			{
				sscanf_s(coord[i]->c_str(), "f %d//%d %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b, &e, &b);
				collplane->push_back(collisionplane(normals[b - 1]->x, normals[b - 1]->y, normals[b - 1]->z, vertex[a - 1]->x, vertex[a - 1]->y, vertex[a - 1]->z, vertex[c - 1]->x, vertex[c - 1]->y, vertex[c - 1]->z, vertex[d - 1]->x, vertex[d - 1]->y, vertex[d - 1]->z, vertex[e - 1]->x, vertex[e - 1]->y, vertex[e - 1]->z));
			}
			else
			{
				if (count(coord[i]->begin(), coord[i]->end(), ' ') == 4)
				{
					if (coord[i]->find("//") != std::string::npos)
					{
						sscanf_s(coord[i]->c_str(), "f %d//%d %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b, &e, &b);
						faces.push_back(new face(b, a, c, d, e, 0, 0, 0, 0, curmat));
					}
					else if (coord[i]->find("/") != std::string::npos)
					{
						int t[4];
						sscanf_s(coord[i]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &a, &t[0], &b, &c, &t[1], &b, &d, &t[2], &b, &e, &t[3], &b);
						faces.push_back(new face(b, a, c, d, e, t[0], t[1], t[2], t[3], curmat));
					}
					else {
						sscanf_s(coord[i]->c_str(), "f %d %d %d %d", &a, &b, &c, &d);
						faces.push_back(new face(-1, a, b, c, d, 0, 0, 0, 0, curmat));
					}
				}
				else {
					if (coord[i]->find("//") != std::string::npos)
					{
						sscanf_s(coord[i]->c_str(), "f %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b);
						faces.push_back(new face(b, a, c, d, 0, 0, 0, curmat));
					}
					else if (coord[i]->find("/") != std::string::npos)
					{
						int t[3];
						sscanf_s(coord[i]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &a, &t[0], &b, &c, &t[1], &b, &d, &t[2], &b);
						faces.push_back(new face(b, a, c, d, t[0], t[1], t[2], curmat));
					}
					else {
						sscanf_s(coord[i]->c_str(), "f %d %d %d", &a, &b, &c);
						faces.push_back(new face(-1, a, b, c, 0, 0, 0, curmat));
					}
				}
			}
		}
		else if ((*coord[i])[0] == 'u' && (*coord[i])[1] == 's' && (*coord[i])[2] == 'e')
		{
			char tmp[200];
			sscanf_s(coord[i]->c_str(), "usemtl %s", tmp, 200);
			if (strcmp(tmp, "collision") == 0)
			{
				coll = true;
			}
			else {
				coll = false;
				for (int i = 0; i<materials.size(); i++)
				{
					if (strcmp(materials[i]->name.c_str(), tmp) == 0)
					{
						curmat = i;
						break;
					}
				}
			}
		}
		else if ((*coord[i])[0] == 'm' && (*coord[i])[1] == 't' && (*coord[i])[2] == 'l' && (*coord[i])[3] == 'l')
		{
			char filen[200];
			sscanf_s(coord[i]->c_str(), "mtllib %s", filen, 200);
			std::string filen2 = path + filen;
			std::ifstream mtlin(filen2.c_str());
			if (!mtlin.is_open())
			{
				clean();
				return -1;
			}
			ismaterial = true;
			std::vector<std::string> tmp;
			char c[200];
			while (!mtlin.eof())
			{
				mtlin.getline(c, 200);
				tmp.push_back(c);
			}
			char name[200];
			char filename[200];
			float amb[3], dif[3], spec[3], alpha, ns, ni;
			int illum;
			unsigned int texture;
			bool ismat = false;
			strcpy_s(filename, "\0");
			//		std::cout << tmp.size() << std::endl;
			for (int i = 0; i<tmp.size(); i++)
			{
				if (tmp[i][0] == '#')
					continue;
				if (tmp[i][0] == 'n' && tmp[i][1] == 'e' && tmp[i][2] == 'w')
				{
					if (ismat)
					{
						
						if (strcmp(filename, "\0") != 0 && strcmp(filename, "collision") != 0)
						{
							materials.push_back(new material(name, alpha, ns, ni, dif, amb, spec, illum, texture));
							strcpy_s(filename, "\0");
						}
						else {
							materials.push_back(new material(name, alpha, ns, ni, dif, amb, spec, illum, -1));
						}
					}

					ismat = false;
					sscanf_s(tmp[i].c_str(), "newmtl %s", name, 200);
					
				}
				else if (tmp[i][0] == 'N' && tmp[i][1] == 's')
				{
					sscanf_s(tmp[i].c_str(), "Ns %f", &ns);
					ismat = true;
				}
				else if (tmp[i][0] == 'K' && tmp[i][1] == 'a')
				{
					sscanf_s(tmp[i].c_str(), "Ka %f %f %f", &amb[0], &amb[1], &amb[2]);
					ismat = true;
				}
				else if (tmp[i][0] == 'K' && tmp[i][1] == 'd')
				{
					sscanf_s(tmp[i].c_str(), "Kd %f %f %f", &dif[0], &dif[1], &dif[2]);
					ismat = true;
				}
				else if (tmp[i][0] == 'K' && tmp[i][1] == 's')
				{
					sscanf_s(tmp[i].c_str(), "Ks %f %f %f", &spec[0], &spec[1], &spec[2]);
					ismat = true;
				}
				else if (tmp[i][0] == 'N' && tmp[i][1] == 'i')
				{
					sscanf_s(tmp[i].c_str(), "Ni %f", &ni);
					ismat = true;
				}
				else if (tmp[i][0] == 'd' && tmp[i][1] == ' ')
				{
					sscanf_s(tmp[i].c_str(), "d %f", &alpha);
					ismat = true;
				}
				else if (tmp[i][0] == 'i' && tmp[i][1] == 'l')
				{
					sscanf_s(tmp[i].c_str(), "illum %d", &illum);
					ismat = true;
				}
				else if (tmp[i][0] == 'm' && tmp[i][1] == 'a')
				{
					sscanf_s(tmp[i].c_str(), "map_Kd %s", filename, 200);
					bool l = 0;
					std::string filename2 = path + filename;
					for (int i = 0; i<loadedTextures.size(); i++)
						if (loadedTextures[i] == filename2)
						{
							texture = loadedTexturesNum[i];
							l = 1;
							break;
						}
					if (l == 0)
						texture = loadTexture(filename2.c_str());
					ismat = true;
				}
			}
			if (ismat)
			{
				if (strcmp(filename, "\0") != 0)
				{
					materials.push_back(new material(name, alpha, ns, ni, dif, amb, spec, illum, texture));
				}
				else {
					materials.push_back(new material(name, alpha, ns, ni, dif, amb, spec, illum, -1));
				}
			}
		}
		else if ((*coord[i])[0] == 'v' && (*coord[i])[1] == 't')
		{
			float u, v;
			sscanf_s(coord[i]->c_str(), "vt %f %f", &u, &v);
			texturecoordinate.push_back(new texcoord(u, 1 - v));
			istexture = true;
		}
	}
	if (materials.size() == 0)
		ismaterial = false;
	else
		ismaterial = true;
	//draw
	if (isvertexnormal)
		smoothnormals();
	int num;
	num = glGenLists(1);
	glNewList(num, GL_COMPILE);
	int last = -1;
	for (int i = 0; i<faces.size(); i++)
	{
		if (last != faces[i]->mat && ismaterial)
		{
			float diffuse[] = { materials[faces[i]->mat]->dif[0],materials[faces[i]->mat]->dif[1],materials[faces[i]->mat]->dif[2],1.0 };
			float ambient[] = { materials[faces[i]->mat]->amb[0],materials[faces[i]->mat]->amb[1],materials[faces[i]->mat]->amb[2],1.0 };
			float specular[] = { materials[faces[i]->mat]->spec[0],materials[faces[i]->mat]->spec[1],materials[faces[i]->mat]->spec[2],1.0 };
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
			glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
			glMaterialf(GL_FRONT, GL_SHININESS, materials[faces[i]->mat]->ns);
			glColor3f(diffuse[0], diffuse[1], diffuse[2]);
			last = faces[i]->mat;
			if (materials[faces[i]->mat]->texture == -1)
				glDisable(GL_TEXTURE_2D);
			else {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, materials[faces[i]->mat]->texture);
			}
		}
		if (faces[i]->texcoord[0] == 0)
			istexture = false;
		else
			istexture = true;

		//std::cout << "IS TEXTURE " << istexture << std::endl;ww

		isnormals = false;
		if (faces[i]->four)
		{
			glBegin(GL_QUADS);
			if (isnormals)
				glNormal3f(normals[faces[i]->facenum - 1]->x, normals[faces[i]->facenum - 1]->y, normals[faces[i]->facenum - 1]->z);

			if (istexture && materials[faces[i]->mat]->texture != -1)
				glTexCoord2f(texturecoordinate[faces[i]->texcoord[0] - 1]->u, texturecoordinate[faces[i]->texcoord[0] - 1]->v);

			if (isvertexnormal)
				glNormal3f(vertexnormals[faces[i]->faces[0] - 1]->x, vertexnormals[faces[i]->faces[0] - 1]->y, vertexnormals[faces[i]->faces[0] - 1]->z);


			glVertex3f(vertex[faces[i]->faces[0] - 1]->x, vertex[faces[i]->faces[0] - 1]->y, vertex[faces[i]->faces[0] - 1]->z);

			if (istexture && materials[faces[i]->mat]->texture != -1)
				glTexCoord2f(texturecoordinate[faces[i]->texcoord[1] - 1]->u, texturecoordinate[faces[i]->texcoord[1] - 1]->v);


			if (isvertexnormal)
				glNormal3f(vertexnormals[faces[i]->faces[1] - 1]->x, vertexnormals[faces[i]->faces[1] - 1]->y, vertexnormals[faces[i]->faces[1] - 1]->z);

			glVertex3f(vertex[faces[i]->faces[1] - 1]->x, vertex[faces[i]->faces[1] - 1]->y, vertex[faces[i]->faces[1] - 1]->z);

			if (istexture && materials[faces[i]->mat]->texture != -1)
				glTexCoord2f(texturecoordinate[faces[i]->texcoord[2] - 1]->u, texturecoordinate[faces[i]->texcoord[2] - 1]->v);

			if (isvertexnormal)
				glNormal3f(vertexnormals[faces[i]->faces[2] - 1]->x, vertexnormals[faces[i]->faces[2] - 1]->y, vertexnormals[faces[i]->faces[2] - 1]->z);

			glVertex3f(vertex[faces[i]->faces[2] - 1]->x, vertex[faces[i]->faces[2] - 1]->y, vertex[faces[i]->faces[2] - 1]->z);

			if (istexture && materials[faces[i]->mat]->texture != -1)
				glTexCoord2f(texturecoordinate[faces[i]->texcoord[3] - 1]->u, texturecoordinate[faces[i]->texcoord[3] - 1]->v);

			if (isvertexnormal)
				glNormal3f(vertexnormals[faces[i]->faces[3] - 1]->x, vertexnormals[faces[i]->faces[3] - 1]->y, vertexnormals[faces[i]->faces[3] - 1]->z);

			glVertex3f(vertex[faces[i]->faces[3] - 1]->x, vertex[faces[i]->faces[3] - 1]->y, vertex[faces[i]->faces[3] - 1]->z);
			glEnd();
		}
		else {
			glBegin(GL_TRIANGLES);
			if (isnormals)
				glNormal3f(normals[faces[i]->facenum - 1]->x, normals[faces[i]->facenum - 1]->y, normals[faces[i]->facenum - 1]->z);

			if (istexture && materials[faces[i]->mat]->texture != -1)
				glTexCoord2f(texturecoordinate[faces[i]->texcoord[0] - 1]->u, texturecoordinate[faces[i]->texcoord[0] - 1]->v);

			if (isvertexnormal)
				glNormal3f(vertexnormals[faces[i]->faces[0] - 1]->x, vertexnormals[faces[i]->faces[0] - 1]->y, vertexnormals[faces[i]->faces[0] - 1]->z);


			glVertex3f(vertex[faces[i]->faces[0] - 1]->x, vertex[faces[i]->faces[0] - 1]->y, vertex[faces[i]->faces[0] - 1]->z);

			if (istexture && materials[faces[i]->mat]->texture != -1)
				glTexCoord2f(texturecoordinate[faces[i]->texcoord[1] - 1]->u, texturecoordinate[faces[i]->texcoord[1] - 1]->v);


			if (isvertexnormal)
				glNormal3f(vertexnormals[faces[i]->faces[1] - 1]->x, vertexnormals[faces[i]->faces[1] - 1]->y, vertexnormals[faces[i]->faces[1] - 1]->z);

			glVertex3f(vertex[faces[i]->faces[1] - 1]->x, vertex[faces[i]->faces[1] - 1]->y, vertex[faces[i]->faces[1] - 1]->z);


			if (istexture && materials[faces[i]->mat]->texture != -1)
				glTexCoord2f(texturecoordinate[faces[i]->texcoord[2] - 1]->u, texturecoordinate[faces[i]->texcoord[2] - 1]->v);


			if (isvertexnormal)
				glNormal3f(vertexnormals[faces[i]->faces[2] - 1]->x, vertexnormals[faces[i]->faces[2] - 1]->y, vertexnormals[faces[i]->faces[2] - 1]->z);

			glVertex3f(vertex[faces[i]->faces[2] - 1]->x, vertex[faces[i]->faces[2] - 1]->y, vertex[faces[i]->faces[2] - 1]->z);
			glEnd();
		}
	}
	glEndList();
	clean();
	lists.push_back(num);
	return num;
}

void ObjectLoader::loadAnimation(std::vector<unsigned int>& anim, const std::string filename, int frames) {

	char frameBuffer[7];

	for (int i = 1; i <= frames; i++) {
		std::string tempName(filename + "_");
		std::string leadingZeros("");

		sprintf_s(frameBuffer, 7, "%d", i);
		int length = strlen(frameBuffer);

		for (int i = 0; i < 6 - length; i++) {
			leadingZeros += "0";
		}
		tempName += leadingZeros + std::to_string(i) + ".obj";
		//std::cout << tempName << std::endl;
		unsigned int index = load(tempName, NULL);

		if (index != -1)
			anim.push_back(index);


	}


}
