#include "TDGame.h"


//TO DO
//Refactor into gamescreen
//Specifically one for single player

TDGame::TDGame()
{
	player1 = new Player(1,true);
	player1->AddGold(50);

	player2 = new Player(2,false);
	player2->AddGold(50);

	LoadContent();


	view = sf::View(sf::FloatRect(0, 0, 1280, 720));
	//view.zoom(TILES_X * GRID_WIDTH / 1280.0f);
	//view.rotate(10);
	window->setView(view);


}


TDGame::~TDGame()
{
	delete hud;
}

void TDGame::Draw()
{
	window->clear();

	

		activeScreen->Draw();

		if (activeScreen == screens["single"])
			hud->draw(window);
	
		if (in_transition && transition_time < transition_speed)
		{
			window->draw(last_trans_spr);

		}
	window->display();
}

void TDGame::Update()
{
	sf::Time elapsed = clock.restart();
	float elapsed_seconds = elapsed.asSeconds();
	
	if (in_transition && transition_time < transition_speed)
	{
		transition_time += elapsed_seconds;
		last_trans_spr.move(WINDOW_WIDTH* elapsed_seconds / transition_speed, 0);
		last_trans_spr.setColor(sf::Color(255, 255, 255, 255 - 255 * transition_time / transition_speed));
	}

	activeScreen->Update();
	if (activeScreen == screens["single"])
		hud->update(window);

}

void TDGame::LoadContent()
{
	map1 = World::Map(window);
	map1.SetPlayers(player1, player2);
	map1.SetConnection(nullptr);

	hud = new HUD(&map1, player1,player2);
	Gallant::Signal1< int > updateLabel;
		
	hud->on_tower_add.Connect(&map1, &World::Map::AddNewTower);

	map1.on_new_wave.Connect(hud, &HUD::OnNewWave);
	map1.on_creep_killed.Connect(hud, &HUD::OnCreepKilled);
	map1.on_tower_added.Connect(hud, &HUD::OnTowerAdded);
	map1.on_life_lost.Connect(hud, &HUD::OnLifeLost);

	mainMenu = new MainMenuScreen(window);
	mainMenu->On_Exit.Connect(this, &TDGame::exit_clicked);
	mainMenu->On_SinglePlayer.Connect(this, &TDGame::single_clicked);

	screens["mainmenu"] = mainMenu;
	screens["single"] = &map1;

	activeScreen = mainMenu;

	
}

void TDGame::exit_clicked(int v)
{
	window->close();
}


void TDGame::single_clicked(int v)
{
	sf::Image img = window->capture();
	last_trans_tex.loadFromImage(img);
	last_trans_spr = sf::Sprite(last_trans_tex);
	//tex.update(window->capture());
	//tex.update()
	in_transition = true;
	activeScreen = screens["single"];
	transition_time = 0;
	

}