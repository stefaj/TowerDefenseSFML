#pragma once
#include "Game.h"
#include "Map.h"
#include "hud.h"
#include "Signalling\Signal.h"
#include <string>
#include "Player.h"
#include "MainMenuScreen.h"
#include <map>
#include "GameScreen.h"

class TDGame :
	public Game
{
public:
	TDGame();
	~TDGame();

	void Draw();
	void Update();
	void LoadContent();

private:
	World::Map map1;
	HUD *hud;
	MainMenuScreen *mainMenu;

	Player *player1;
	Player *player2;

	sf::View view;

	std::map<std::string, GameScreen*> screens;
	GameScreen *activeScreen;

	void exit_clicked(int v);
	void single_clicked(int v);

	sf::Clock clock;
	bool in_transition = false;
	float transition_speed = 1.0;
	float transition_time = 0;
	sf::Texture last_trans_tex;
	sf::Sprite last_trans_spr;

};

