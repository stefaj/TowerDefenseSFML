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
#include "Constant.h"

namespace States
{
	class WinnerScreen : public GameScreen
	{
	public:
		WinnerScreen(sf::RenderWindow *rt);;
		~WinnerScreen();
		Gallant::Signal1<int> On_Close;
		void SetWinner(bool didWin);
	private:
		sf::Texture background_tex;
		sf::Sprite background_sprite;
		void update(float elapsed_seconds);
		void draw();
		void LoadContent();

		
		void back_click(UI::Component *c);

		UI::Label *backLabel;
		Font font;
		Text text;
		bool isWinner;

		InputManager *input;

	};
}

