#include "gracz.h"

gracz::gracz(std::string n, float predkosc, float sprint)
{
	imie = n;
	zdrowie = 500;
	setPozycja(vector3d(0.0, 10, 0));
	bieg =sprint;
	chodzenie = predkosc;
	sila.change(0.0, -0.3, 0.0);
	kierunek.change(0.0, 0.0, 0.0);
	energia = 10;
	czyBieg = false;
	punkty = 0;
}

void gracz::show()
{
}

void gracz::skok()
{
	if (naZiemi)
	{
		naZiemi = false;
		kierunek.change(0.0, 2, 0.0);
	}
}

std::string gracz::getImie()
{
	return imie;
}

void gracz::setPozycja(vector3d pos)
{
}

void gracz::update()
{
}


void gracz::obniZdrowie(int num)
{
	zdrowie -= num;
}

int gracz::getZdrowie()
{
	return zdrowie;
}


void gracz::setZdrowie(int h)
{
	zdrowie = h;
}


void gracz::dodZdrowie(int h)
{
	zdrowie += h;
}

void gracz::setSprint(bool b)
{
}

bool gracz::getBieg()
{
	return czyBieg;
}

void gracz::dodPunkty(int num)
{
	punkty += num;
}

int gracz::getPunkty()
{
	return punkty;
}

