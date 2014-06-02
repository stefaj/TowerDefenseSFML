#pragma once
#include "GameScreen.h"
#include <SFML/Graphics.hpp>
#include "Constant.h"
#include "Signalling\Signal.h"
#include <string>
namespace States
{
	class ScreenManager
	{
	public:
		ScreenManager();
		ScreenManager(sf::RenderWindow *rw);
		~ScreenManager();
		void Update(float elapsed_seconds);
		void Draw();

		void ProcessEvent(sf::Event *e);

		void TransitionToScreen(std::string screenName);
		void AddScreen(std::string screenName, GameScreen *screen);
		void RemoveScreen(std::string screenName);

		const GameScreen* GetScreen(std::string screenName);

		Gallant::Signal1<sf::RenderWindow*> PostMapDraw;
		Gallant::Signal1<sf::RenderWindow*> PostMapUpdate;
	private:
		std::map<std::string, GameScreen*> screens;
		GameScreen *activeScreen;
		
		//Transition
		
		bool in_transition = false;
		float transition_speed = 1.0;
		float transition_time = 0;
		sf::Texture last_trans_tex;
		sf::Sprite last_trans_spr;

		sf::RenderWindow *window;
	};
}