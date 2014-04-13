#pragma once
#include "Game.h"
#include "Map.h"
#include "hud.h"
#include "Signalling\Signal.h"
#include <string>
#include "Player.h"

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

	Player *player1;

	sf::View view;

	

};

