#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include "vector.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "collisionsphere.h"
#include "collision.h"
/// <summary>	Values that represent kinds. </summary>
enum kind {
	finish,
	health,
	ammo
};
/// <summary>	An one item. </summary>
struct oneItem
{
	/// <summary>	The identifier. </summary>
	kind id;
	/// <summary>	The mesh. </summary>
	unsigned int mesh;
	/// <summary>	The rotation. </summary>
	vector3d rotation;
	/// <summary>	The speed. </summary>
	vector3d speed;
	/// <summary>	true to direction. </summary>
	bool direction;
	/// <summary>	The create struct. </summary>
	collisionsphere cs;
	/// <summary>	The scale. </summary>
	vector3d scale;
	/// <summary>	The colour. </summary>
	vector3d colour;

	/// <summary>	Constructor. </summary>
	///
	/// <param name="i">	Zero-based index of the. </param>
	/// <param name="c">	The collisionsphere to process. </param>

	oneItem(kind i, collisionsphere c);

	/// <summary>	Constructor. </summary>
	///
	/// <param name="i">	   	Zero-based index of the. </param>
	/// <param name="c">	   	The collisionsphere to process. </param>
	/// <param name="rotation">	The rotation. </param>
	/// <param name="speed">   	The speed. </param>
	/// <param name="scale">   	The scale. </param>
	/// <param name="colour">  	The colour. </param>

	oneItem(kind i, collisionsphere c, vector3d rotation, vector3d speed, vector3d scale, vector3d colour);
};

/// <summary>	An item class,contains all bonuses, have type of item (most of bonuses), display it, . </summary>
class item :public collision {
	/// <summary>	The items. </summary>
	std::vector<oneItem> items;
public:

	/// <summary>	Constructor. </summary>
	///
	/// <param name="i">   	Zero-based index of the. </param>
	/// <param name="mesh">	The mesh. </param>
	/// <param name="c">   	[in,out] The collisionsphere to process. </param>

	item(kind i, unsigned int mesh, collisionsphere& c);

	/// <summary>	Default constructor. </summary>
	item();

	/// <summary>	Updates the given playerloc. </summary>
	///
	/// <param name="playerloc">	The playerloc. </param>
	///
	/// <returns>	An int. </returns>

	int update(collisionsphere playerloc);
	/// <summary>	Shows this object. </summary>
	void show();

	/// <summary>	Adds i. </summary>
	///
	/// <param name="i">	Zero-based index of the. </param>
	/// <param name="c">	The collisionsphere to process. </param>

	void add(kind i, collisionsphere c);

	/// <summary>	Adds i. </summary>
	///
	/// <param name="i">	   	Zero-based index of the. </param>
	/// <param name="c">	   	The collisionsphere to process. </param>
	/// <param name="rotation">	The rotation. </param>
	/// <param name="speed">   	The speed. </param>
	/// <param name="scale">   	The scale. </param>

	void add(kind i, collisionsphere c, vector3d rotation, vector3d speed, vector3d scale);

	/// <summary>	Deletes the given ID. </summary>
	///
	/// <param name="id">	The identifier. </param>

	void del(kind id);
	/// <summary>	Clears this object to its blank/initial state. </summary>
	void clear();
};

#endif
