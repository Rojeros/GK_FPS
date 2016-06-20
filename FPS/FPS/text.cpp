#include "text.h"

void text::showTextInfo(int health, int ammo, int allammo, int point, std::vector<Weapon*> weaponName, int currentWeapon,int points, int g_viewport_width, int g_viewport_height,std::string level)
{
	startText(g_viewport_width, g_viewport_height);
	glLineWidth(5);
	displayText("HP:", g_viewport_width, g_viewport_height, 8,NW,0);
	endText();

	startText(g_viewport_width, g_viewport_height);
	glLineWidth(5);
	displayText(std::to_string(health), g_viewport_width, g_viewport_height, 8, NW, -1);
	endText();

	startText(g_viewport_width, g_viewport_height);
	glLineWidth(5);
	displayText(weaponName[currentWeapon]->getName(), g_viewport_width, g_viewport_height, 8, NE, 0);
	endText();

	startText(g_viewport_width, g_viewport_height);
	glLineWidth(5);
	displayText( std::to_string(ammo) + "/" + std::to_string(allammo)  , g_viewport_width, g_viewport_height, 8, NE, -1);
	endText();
	if (currentWeapon+1 < weaponName.size()) {
		currentWeapon++;
	}
	else
		currentWeapon = 0;
	startText(g_viewport_width, g_viewport_height);
	glLineWidth(2);
	displayText(weaponName[currentWeapon]->getName() + " " +
		std::to_string(weaponName[currentWeapon]->getAmmoClip())  + "/" + std::to_string(weaponName[currentWeapon]->getAllBullets()) + " "
		, g_viewport_width, g_viewport_height, 10, NE, -2);
	endText();
	
	if (currentWeapon + 1 < weaponName.size()) {
		currentWeapon++;
	}
	else
		currentWeapon = 0;
	startText(g_viewport_width, g_viewport_height);
	glLineWidth(2);
	displayText(weaponName[currentWeapon]->getName() + " " +
		std::to_string(weaponName[currentWeapon]->getAmmoClip()) + "/" + std::to_string(weaponName[currentWeapon]->getAllBullets()) + " "
		, g_viewport_width, g_viewport_height, 10, NE, -3);

	endText();

	startText(g_viewport_width, g_viewport_height);
	glLineWidth(2);
	displayText("Level: " + level, g_viewport_width, g_viewport_height, 8, N, 0);
	endText();

	startText(g_viewport_width, g_viewport_height);
	glLineWidth(2);
	displayText("Points: "+to_string(points), g_viewport_width, g_viewport_height, 8, N, -1);
	endText();

	startText(g_viewport_width, g_viewport_height);
	glLineWidth(5);
	displayText("+", g_viewport_width, g_viewport_height, 8, CENTER, 0);
	endText();
}

void text::displayDiffrentText(std::string text, int g_viewport_width, int g_viewport_height, double size, coordinates coord, int line, vector3d color)
{
	startText(g_viewport_width, g_viewport_height);
	glLineWidth(5);
	displayText(text, g_viewport_width, g_viewport_height, size, coord, line,color);
	endText();
}

void text::startText(int g_viewport_width,int g_viewport_height) {

	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, g_viewport_width, 0.0, g_viewport_height);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void text::displayText(std::string text, int g_viewport_width, int g_viewport_height, double size, coordinates coord,int line, vector3d color)
{
	void * font = GLUT_STROKE_ROMAN;
	float height = glutStrokeHeight(font);
	float x = 0, y = 0;



	float d = 0, h = 0, w = 0;
	for (std::string::iterator i = text.begin(); i != text.end(); ++i)
	{
		char c = *i;
		d += glutStrokeWidth(font, c);

	}
	h = (g_viewport_height / 20) / height;
	w = (g_viewport_width / size) / d;

	glPushMatrix();


	if (coord == N || coord == NW || coord == NE)
		y = g_viewport_height - (height*h);
	if (coord == E || coord == NE || coord == SE)
		x = g_viewport_width - (d*w);
	if (coord == N || coord == S || coord == CENTER)
		x = g_viewport_width / 2 - (d*w / 2);
	if (coord == W || coord == E || coord == CENTER)
		y = (g_viewport_height / 2) - (height*h);


	glTranslatef(x, y + (line* height*h), 0);
	glScalef(w, h, 1);
	glColor3f(color.x, color.y, color.z);
	for (std::string::iterator i = text.begin(); i != text.end(); ++i)
	{
		char c = *i;
		glutStrokeCharacter(font, c);

	}
}



void text::displayText(std::string text, int g_viewport_width, int g_viewport_height,double size, coordinates coord, int line) {

	void * font = GLUT_STROKE_ROMAN;
	float height = glutStrokeHeight(font);
	float x = 0,y=0;


	
	float d = 0,h=0,w=0;
	for (std::string::iterator i = text.begin(); i != text.end(); ++i)
	{
		char c = *i;
		d += glutStrokeWidth(font, c);

	}
	h = (g_viewport_height / 20) / height;
	w = (g_viewport_width / size) / d;

	glPushMatrix();
	

	if (coord == N || coord == NW || coord == NE)
		y = g_viewport_height-(height*h);
	if (coord == E || coord == NE || coord == SE)
		x = g_viewport_width-(d*w);
	if(coord==N || coord == S || coord == CENTER)
		x = g_viewport_width/2 - (d*w/2);
	if (coord == W || coord == E || coord == CENTER)
		y = (g_viewport_height / 2)- (height*h);


	glTranslatef(x, y + (line* height*h), 0);
	glScalef(w, h, 1);
	for (std::string::iterator i = text.begin(); i != text.end(); ++i)
	{
		char c = *i;
		glutStrokeCharacter(font, c);

	}

}

void text::endText() {
	glMatrixMode(GL_PROJECTION); 
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW); 
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	
}
