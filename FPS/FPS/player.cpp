#include "player.h"

player::player(std::string n, float predkosc, float sprint,float looks)
{
	imie = n;
	zdrowie = 500;
	bieg =sprint;
	chodzenie = predkosc;
	sila.change(0.0, -0.3, 0.0);
	kierunek.change(0.0, 0.0, 0.0);
	energia = 10;
	czyBieg = false;
	punkty = 0;

}

player::player(std::string n, collisionsphere cs, int hl, float predkosc, float sprint, float looks)
{
	imie = n;
	zdrowie = hl;
	collisionSp = cs;
	bieg = sprint;
	chodzenie = predkosc;
	setPosition(cs.center);
	sila.change(0.0, -0.3, 0.0);
	kierunek.change(0.0, 0.0, 0.0);
	energia = 10;
	czyBieg = false;
	punkty = 0;

}

Camera* player::getCamera()
{
	return &cam;
}

void player::show()
{
}

void player::skok()
{
	if (naZiemi)
	{
		naZiemi = false;
		kierunek.change(0.0, 2, 0.0);
	}
}

std::string player::getImie()
{
	return imie;
}



void player::update()
{

	if (kierunek.y >= sila.y)
		kierunek += sila;
	//	std::cout << direction;
	
	if (energia<10 && !czyBieg)
		energia += 0.01;
	if (czyBieg)
		energia -= 0.05;
	if (energia <= 0)
		setSprint(false);
	

}


void player::obniZdrowie(int num)
{
	zdrowie -= num;
}

int player::getZdrowie()
{
	return zdrowie;
}


void player::setZdrowie(int h)
{
	zdrowie = h;
}


void player::dodZdrowie(int h)
{
	zdrowie += h;
}

void player::setSprint(bool b)
{
}

bool player::getBieg()
{
	return czyBieg;
}

void player::dodPunkty(int num)
{
	punkty += num;
}

int player::getPunkty()
{
	return punkty;
}

void player::setPosition(vector3d position)
{
	collisionSp.center = position;
	cam.setLocation(position);
}

