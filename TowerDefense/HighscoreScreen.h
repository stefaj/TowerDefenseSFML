#pragma once
#include "GameScreen.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Label.h"
#include "InputManager.h"
#include "Component.h"
#include "Signalling\Signal.h";
#include "highscorefile.h"
#include "highscore.h"
#include <vector>

namespace States
{
	class HighscoreScreen : public GameScreen
	{
	public:
		HighscoreScreen(sf::RenderWindow *rt);
		~HighscoreScreen();

		Gallant::Signal1<int> On_Close;
		void back_click(UI::Component *c);

		void OnLoad();
	

	private:
		sf::Texture background_tex;
		sf::Sprite background_sprite;
		void update(float elapsed_seconds);
		void draw();
		void LoadContent();

		InputManager *input;

		UI::Label *backLabel;
		UI::Label *nameLabel;

		std::vector<Highscore> scores;
	};
}

