#include "TDGame.h"


//TO DO
//Refactor into gamescreen
//Specifically one for single player

TDGame::TDGame()
{
	player1 = new Player(1);
	player1->AddGold(50);
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
	Gallant::Signal1< int > updateLabel;
		
	hud->on_tower_add.Connect(&map1, &World::Map::AddNewTower);

	map1.on_new_wave.Connect(hud, &HUD::OnNewWave);
	map1.on_creep_killed.Connect(hud, &HUD::OnCreepKilled);
	map1.on_tower_added.Connect(hud, &HUD::OnTowerAdded);
}