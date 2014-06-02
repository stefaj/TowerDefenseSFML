#pragma once
#include "GameScreen.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Label.h"
#include "InputManager.h"
#include "Component.h"
#include "Signalling\Signal.h";

namespace States
{
	class MainMenuScreen : public GameScreen
	{
	public:
		MainMenuScreen(sf::RenderWindow *rt);
		~MainMenuScreen();

		void singlePlayer_hover(UI::Component *c);
		void singlePlayer_click(UI::Component *c);
		void highscore_click(UI::Component *c);
		void multiPlayer_click(UI::Component *c);

		void OnLoad();


		void exit_click(UI::Component *c);

		Gallant::Signal1<int> On_Highscore;
		Gallant::Signal1<int> On_Exit;
		Gallant::Signal1<int> On_SinglePlayer;
		Gallant::Signal1<int> On_Multiplayer;

	private:
		sf::Texture background_tex;
		sf::Sprite background_sprite;
		void update(float elapsed_seconds);
		void draw();
		void LoadContent();

		InputManager *input;

		UI::Label *singlePlayerlbl;
		UI::Label *multiplayerlbl;
		UI::Label *highscorelbl;
		UI::Label *exitlbl;
		UI::Label *titleLabel;
		sf::Music backgroundMusic;

	
	};
}