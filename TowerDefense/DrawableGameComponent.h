#pragma once
#include <SFML/Graphics.hpp>

namespace States
{	class DrawableGameComponent
	{
	public:
		virtual void Update(sf::RenderWindow* window, float elapsed_seconds) = 0;
		virtual void Draw(sf::RenderWindow* window) = 0;
	};

}