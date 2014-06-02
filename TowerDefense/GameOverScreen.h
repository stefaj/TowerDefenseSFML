#pragma once
#include "GameScreen.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Label.h"
#include "InputManager.h"
#include "Component.h"
#include "Signalling\Signal.h";
class GameOverScreen : public GameScreen
{
public:
	GameOverScreen(sf::RenderWindow *rt);
	~GameOverScreen();

	void close_click(UI::Component *c);

	Gallant::Signal1<int> On_Close;

	void SetScore(int s);

private:
	sf::Texture background_tex;
	sf::Sprite background_sprite;
	void update(float elapsed_seconds);
	void draw();
	void LoadContent();
	void ProcessEvent(sf::Event *e);

	int score;
	InputManager *input;

	UI::Label *closeLabel;
	UI::Label *textLabel;
	UI::Label *descripLabel;

	sf::String text;
};

