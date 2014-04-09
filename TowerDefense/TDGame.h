#pragma once
#include "Game.h"
#include "Map.h"
#include "hud.h"
#include <boost/signals2.hpp>
#include <boost/bind.hpp>
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

	

};

