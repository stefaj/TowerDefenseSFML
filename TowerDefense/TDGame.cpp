#include "TDGame.h"


//TO DO
//Refactor into gamescreen
//Specifically one for single player

TDGame::TDGame()
{
	player1 = new Player(1);
	player1->AddGold(30);
	LoadContent();
	
}


TDGame::~TDGame()
{
	delete hud;
}

void TDGame::Draw()
{
	window->clear();

	map1.Draw();
	hud->draw(window);

	window->display();
}

void TDGame::Update()
{
	map1.Update();
	hud->update(window);
}

void TDGame::LoadContent()
{
	map1 = World::Map(window);

	hud = new HUD(&map1, player1);

	hud->on_tower_add.connect(boost::bind(&World::Map::AddNewTower, &map1, _1));
}