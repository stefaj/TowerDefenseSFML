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
#include "HighscoreScreen.h"
#include "SingleplayerMap.h"
#include "MultiplayerMap.h"
#include "ScreenManager.h"
#include "LobbyScreen.h"
#include "SFML/Network.hpp"
#include "GameOverScreen.h"
#include <memory>
#include "WinnerScreen.h"

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
	ScreenManager screenMan;
	
	HUD *hud;

	//Screens
	World::Map *map1;
	MainMenuScreen *mainMenu;
	LobbyScreen *lobby;
	HighscoreScreen *hsScreen;
	GameOverScreen *gameOverScreen;
	WinnerScreen *winnerScreen;

	sf::Clock clock;

	Player *player1;
	Player *player2;

	sf::View view;

	
	

	void exit_clicked(int v);
	void single_clicked(int v);
	void highscore_clicked(int v);
	void multiplayer_clicked(int v);
	void game_joined(sf::TcpSocket *sock, bool isHost);
	void single_player_gameover(int score);
	void multi_player_gameover(bool didwin);

	void cleanup_after_game();

	void transition_to_main(int v);

	void ProcessEvent(sf::Event *e);
	

};

