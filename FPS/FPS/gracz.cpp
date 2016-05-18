#include "gracz.h"

gracz::gracz(std::string n, float predkosc, float sprint,float looks)
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

Camera* gracz::getCamera()
{
	return &cam;
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



void gracz::update()
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

