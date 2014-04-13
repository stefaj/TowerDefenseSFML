#include "HealthBar.h"


HealthBar::HealthBar()
{
	width = 28;
	height = 10;

	innerBar = sf::RectangleShape(sf::Vector2f(width, height));
	innerBar.setFillColor(sf::Color(0, 255, 0, 200));
	innerBar.setOutlineThickness(2);
	innerBar.setOutlineColor(sf::Color(200, 255, 200, 200));
}

HealthBar::HealthBar(int w, int h)
{
	width = w;
	height = h;

	innerBar = sf::RectangleShape(sf::Vector2f(width, height));
	innerBar.setFillColor(sf::Color(0, 255, 0, 200));
	innerBar.setOutlineThickness(2);
	innerBar.setOutlineColor(sf::Color(200, 255, 200, 200));
}


HealthBar::~HealthBar()
{
}


void HealthBar::Draw(int x, int y, float percentage, sf::RenderTarget *rw)
{
	innerBar.setScale(percentage, 1);
	innerBar.setPosition(x, y);
	rw->draw(innerBar);
}