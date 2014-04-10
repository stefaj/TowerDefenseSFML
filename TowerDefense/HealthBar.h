#pragma once
#include <SFML/Graphics.hpp>

class HealthBar
{
public:
	HealthBar();
	HealthBar(int, int);
	~HealthBar();

	void Draw(int x, int y, float percentage, sf::RenderWindow *rw);

private:
	int width;
	int height;
	sf::RectangleShape innerBar;
};
