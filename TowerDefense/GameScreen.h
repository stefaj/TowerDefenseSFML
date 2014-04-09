#pragma once

#include <vector>
#include "DrawableGameComponent.h"
#include <SFML/Graphics.hpp>

using namespace std;


namespace States
{
	class GameScreen
	{
	public:
		explicit GameScreen(sf::RenderWindow *rw);
		GameScreen();
		~GameScreen();
		void Update();
		void Draw();
		void AddComponent(DrawableGameComponent *comp);
		void RemoveComponent(DrawableGameComponent *comp);
	protected:
		vector<DrawableGameComponent*> gameComponents;
		virtual void update(float elapsed_seconds) = 0;
		virtual void draw() = 0;
		sf::RenderWindow *render_window;
		virtual void LoadContent() = 0;
		sf::Clock clock;


	};

}