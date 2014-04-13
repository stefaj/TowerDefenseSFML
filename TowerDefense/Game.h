#pragma once
#include <SFML/Graphics.hpp>
namespace States
{
	class Game
	{
	public:
		Game();
		virtual ~Game();

		virtual void LoadContent() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;


		void Run();

	private:
		void ProcessEvents();

	protected:
		sf::RenderWindow *window;

	};

}