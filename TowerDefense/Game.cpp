#include "Game.h"
#include "Constant.h"
using namespace States;

Game::Game()
{
#if !DEBUG
	//window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tower Defense!", sf::Style::Fullscreen);
	window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tower Defense!");
#endif
#if DEBUG
	window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tower Defense!");
#endif
	window->setFramerateLimit(60);
	LoadContent();
}


Game::~Game()
{
	delete window;
	
}

void Game::ProcessEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		if (event.type == sf::Event::KeyPressed)
		{
			//Key gets pressed
		}
	}
}

void Game::Run()
{
	while (window->isOpen())
	{
		ProcessEvents();
		Update();
		Draw();
	}

}

void Game::LoadContent()
{

}