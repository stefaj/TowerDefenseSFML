#include "TDGame.h"


//TO DO
//Refactor into gamescreen
//Specifically one for single player

TDGame::TDGame()
{
	

	view = sf::View(sf::FloatRect(0, 0, 1280, 720));
	//view.zoom(TILES_X * GRID_WIDTH / 1280.0f);
	//view.rotate(10);
	window->setView(view);

	screenMan = ScreenManager(window);

	LoadContent();

}


TDGame::~TDGame()
{

}

void TDGame::Draw()
{
	window->clear();

	screenMan.Draw();

	window->display();
}

void TDGame::Update()
{
	sf::Time elapsed = clock.restart();
	float elapsed_seconds = elapsed.asSeconds();
	
	screenMan.Update(elapsed_seconds);

}

void TDGame::LoadContent()
{
	window->clear();
	window->display();

	mainMenu = new MainMenuScreen(window);
	mainMenu->On_Exit.Connect(this, &TDGame::exit_clicked);
	mainMenu->On_SinglePlayer.Connect(this, &TDGame::single_clicked);
	mainMenu->On_Highscore.Connect(this, &TDGame::highscore_clicked);
	mainMenu->On_Multiplayer.Connect(this, &TDGame::multiplayer_clicked);

	hsScreen = new HighscoreScreen(window);
	hsScreen->On_Close.Connect(this, &TDGame::transition_to_main);
	lobby = new LobbyScreen(window);
	lobby->On_JoinGame.Connect(this, &TDGame::game_joined);

	gameOverScreen = new GameOverScreen(window);
	gameOverScreen->SetScore(50);
	gameOverScreen->On_Close.Connect(this, &TDGame::transition_to_main);

	winnerScreen = new WinnerScreen(window);
	winnerScreen->SetWinner(false);
	winnerScreen->On_Close.Connect(this, &TDGame::transition_to_main);

	screenMan.AddScreen("lobby", lobby);
	screenMan.AddScreen("mainmenu", mainMenu);
	screenMan.AddScreen("highscores",hsScreen);
	screenMan.AddScreen("winner", winnerScreen);
	screenMan.AddScreen("gameover", gameOverScreen);
	
	
	screenMan.TransitionToScreen("mainmenu");
	
	
	
}

void TDGame::exit_clicked(int v)
{
	window->close();
}

void TDGame::highscore_clicked(int v)
{
	screenMan.TransitionToScreen("highscores");
}


void TDGame::multiplayer_clicked(int v)
{
	screenMan.TransitionToScreen("lobby");
}

void TDGame::game_joined(sf::TcpSocket *sock, bool isHost)
{
	map1 = new World::MultiplayerMap(window, "multiplayer2.tmx");

	player1 = new Player(1, true);
	player1->AddGold(100);
	player1->AddPassiveIncome(10);

	player2 = new Player(2, false);
	player2->AddGold(100);
	player2->AddPassiveIncome(10);
	
	if (isHost)
	{
		

		hud = new HUD(map1, player1, player2);
		map1->SetPlayers(player1, player2);
	}
	else
	{
		hud = new HUD(map1, player2, player1);
		map1->SetPlayers(player2, player1);
	}

	

	Connection *conn = new Connection(sock);
	
	map1->SetConnection(conn);

	map1->on_new_wave.Connect(hud, &HUD::OnNewWave);
	map1->on_creep_killed.Connect(hud, &HUD::OnCreepKilled);
	map1->on_tower_added.Connect(hud, &HUD::OnTowerAdded);
	map1->on_life_lost.Connect(hud, &HUD::OnLifeLost);
	map1->on_game_over.Connect(hud, &HUD::OnGameOver);
	map1->on_show_winner.Connect(this, &TDGame::multi_player_gameover);

	
	hud->on_enemy_add.Connect(map1, &World::Map::OnAddEnemy);
	hud->on_tower_add.Connect(map1, &World::Map::AddNewTower);
	screenMan.PostMapDraw.Connect(hud, &HUD::draw);
	screenMan.PostMapUpdate.Connect(hud, &HUD::update);


	screenMan.AddScreen("map", map1);

	screenMan.TransitionToScreen("map");
}

void TDGame::ProcessEvent(sf::Event *e)
{
	screenMan.ProcessEvent(e);
}

void TDGame::single_clicked(int v)
{
	player1 = new Player(1, true);
	player1->AddGold(50);

	player2 = new Player(2, false);
	player2->AddGold(50);
	player2->SetActive(false);

	map1 = new World::SingleplayerMap(window, "sp1.tmx");
	hud = new HUD(map1, player1, player2);

	map1->SetPlayers(player1, player2);
	map1->SetConnection(nullptr);

	map1->on_new_wave.Connect(hud, &HUD::OnNewWave);
	map1->on_creep_killed.Connect(hud, &HUD::OnCreepKilled);
	map1->on_tower_added.Connect(hud, &HUD::OnTowerAdded);
	map1->on_life_lost.Connect(hud, &HUD::OnLifeLost);
	map1->on_game_over.Connect(hud, &HUD::OnGameOver);
	map1->on_game_over.Connect(this, &TDGame::single_player_gameover);

	hud->on_tower_add.Connect(map1, &World::Map::AddNewTower);
	screenMan.PostMapDraw.Connect(hud, &HUD::draw);
	screenMan.PostMapUpdate.Connect(hud, &HUD::update);


	screenMan.AddScreen("map", map1);

	screenMan.TransitionToScreen("map");

	
}

void TDGame::transition_to_main(int v)
{
	screenMan.TransitionToScreen("mainmenu");
}

void TDGame::multi_player_gameover(bool didwin)
{
	sf::View view = sf::View(sf::FloatRect(0, 0, 1280, 720));
	window->setView(view);

	winnerScreen->SetWinner(didwin);
	screenMan.TransitionToScreen("winner");

	cleanup_after_game();
}


void TDGame::single_player_gameover(int score)
{

	sf::View view = sf::View(sf::FloatRect(0, 0, 1280, 720));
	window->setView(view);

	screenMan.TransitionToScreen("gameover");
	gameOverScreen->SetScore(score);

	cleanup_after_game();
}


void TDGame::cleanup_after_game()
{
	
	screenMan.PostMapDraw.Clear();
	screenMan.PostMapUpdate.Clear();
	
	delete player1;
	delete player2;
	screenMan.RemoveScreen("map");
	delete hud;
	//delete map1;
}