#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#ifndef TEXT_H
#define TEXT_H
#include <string>
#include <cstring>
#include <iostream>
#include "vector.h"
#include "collisionplane.h"
#include <vector>
#include "weapon.h"
/// <summary>	Values that represent coordinates. </summary>
enum coordinates {
	NW,
	N,
	NE,
	E,
	SE,
	S,
	SW,
	W,
	CENTER

};




/// <summary>	Class displaying text on the screen. </summary>
class text {

	/// <summary>	Displays a text. </summary>
	///
	/// <param name="text">					The text. </param>
	/// <param name="g_viewport_width"> 	Width of the viewport. </param>
	/// <param name="g_viewport_height">	Height of the viewport. </param>
	/// <param name="size">					The size. </param>
	/// <param name="coord">				The coordinate. </param>
	/// <param name="line">					The line. </param>

	void text::displayText(std::string text, int g_viewport_width, int g_viewport_height, double size, coordinates coord, int line);

	/// <summary>	Starts a text. </summary>
	///
	/// <param name="g_viewport_width"> 	Width of the viewport. </param>
	/// <param name="g_viewport_height">	Height of the viewport. </param>

	void text::startText(int g_viewport_width, int g_viewport_height);

	/// <summary>	Displays a text. </summary>
	///
	/// <param name="text">					The text. </param>
	/// <param name="g_viewport_width"> 	Width of the viewport. </param>
	/// <param name="g_viewport_height">	Height of the viewport. </param>
	/// <param name="size">					The size. </param>
	/// <param name="coord">				The coordinate. </param>
	/// <param name="line">					The line. </param>
	/// <param name="color">				The color. </param>

	void text::displayText(std::string text, int g_viewport_width, int g_viewport_height, double size, coordinates coord, int line, vector3d color);
	/// <summary>	Ends a text. </summary>
	void text::endText();
public:

	/// <summary>	Shows the text information. </summary>
	///
	/// <param name="health">				The health. </param>
	/// <param name="ammo">					The ammo. </param>
	/// <param name="allammo">				The allammo. </param>
	/// <param name="point">				The point. </param>
	/// <param name="weaponName">			[in,out] If non-null, name of the weapon. </param>
	/// <param name="currentWeapon">		The current weapon. </param>
	/// <param name="points">				The points. </param>
	/// <param name="g_viewport_width"> 	Width of the viewport. </param>
	/// <param name="g_viewport_height">	Height of the viewport. </param>
	/// <param name="level">				The level. </param>

	void text::showTextInfo(int health, int ammo, int allammo, int point, std::vector<Weapon*> weaponName,int currentWeapon,int points, int g_viewport_width, int g_viewport_height,std::string level);

	/// <summary>	Displays a diffrent text. </summary>
	///
	/// <param name="text">					The text. </param>
	/// <param name="g_viewport_width"> 	Width of the viewport. </param>
	/// <param name="g_viewport_height">	Height of the viewport. </param>
	/// <param name="size">					The size. </param>
	/// <param name="coord">				The coordinate. </param>
	/// <param name="line">					The line. </param>
	/// <param name="color">				The color. </param>

	void text::displayDiffrentText(std::string text, int g_viewport_width, int g_viewport_height, double size, coordinates coord, int line,vector3d color);

};
#endif
