#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h";
#include "InputManager.h"
#include "Label.h"
#include "Player.h"
#include "Tower.h"
#include "Signalling\Signal.h"
#include "Constant.h"
#include "TowerStruct.h"

class HUD
{
public:
	HUD();
	HUD(World::Map *m_, Player *local, Player *remote);
	void draw(sf::RenderWindow *rw);
	void update(sf::RenderWindow *rw);
	void DrawGrid(sf::RenderWindow* window);
	Gallant::Signal1<Networking::TowerStruct> on_tower_add;
	Gallant::Signal1<Networking::EnemyStruct> on_enemy_add;
	enum HUD_STATE {NONE,NEW_TOWER, TOWER_MENU};

	//Event handlers
	void OnNewWave(int);
	void OnCreepKilled(int);
	void OnTowerAdded(Tower* tower);
	void OnLifeLost(int player_id);
	void OnGameOver(int score);

private:
	void LoadContent();

	InputManager input;
	sf::RectangleShape bottomBar;
	float tower_radius_dream_size = 0;
	sf::CircleShape towerRadiusShape;
	

	//Towers
	sf::Texture tower_box_tex;
	sf::Sprite t1_sprite;
	sf::Sprite t2_sprite;
	sf::Sprite t3_sprite;
	sf::Sprite t4_sprite;
	sf::Sprite t5_sprite;

	sf::Texture t1_tex;
	sf::Texture t2_tex;
	sf::Texture t3_tex;
	sf::Texture t4_tex;
	sf::Texture t5_tex;

	//Enemies
	sf::Sprite e1_sprite;
	sf::Sprite e2_sprite;
	sf::Sprite e3_sprite;
	sf::Sprite e4_sprite;
	sf::Sprite e5_sprite;

	sf::Texture e1_tex;
	sf::Texture e2_tex;
	sf::Texture e3_tex;
	sf::Texture e4_tex;
	sf::Texture e5_tex;


	sf::Sprite tower_box;
	int newTowerid = -1;


	sf::Sprite gameOver;
	sf::Texture gameOverTex;
	bool isGameOver;


	float mouse_x;
	float mouse_y;
	sf::Sprite active_tower_sprite;

	sf::RectangleShape gridRect;
	sf::RectangleShape towerPlaceRect;

	const static int TOWER_GRID_WIDTH = 64;
	HUD_STATE current_state;
	World::Map *map;

	Player *localPlayer;
	Player *remotePlayer;

	//UI Components
	UI::Label *waveLabel;
	UI::Label *passiveGold;
	UI::Label *goldLabel;
	UI::Label *livesLabel;
	UI::Label *killsLabel;

	int updates;


	//Helper
	void AddEnemy(int lvl);
};