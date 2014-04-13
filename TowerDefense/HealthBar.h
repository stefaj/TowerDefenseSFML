#pragma once
#include <SFML/Graphics.hpp>

class HealthBar
{
public:
	HealthBar();
	HealthBar(int, int);
	~HealthBar();

	void Draw(int x, int y, float percentage, sf::RenderTarget *rw);

private:
	int width;
	int height;
	sf::RectangleShape innerBar;
};
