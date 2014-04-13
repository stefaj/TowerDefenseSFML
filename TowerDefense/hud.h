#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h";
#include "InputManager.h"
#include "Label.h"
#include "Player.h"
#include "Tower.h"
#include "Signalling\Signal.h"

class HUD
{
public:
	HUD();
	HUD(World::Map *m_, Player *player);
	void draw(sf::RenderWindow *rw);
	void update(sf::RenderWindow *rw);
	void DrawGrid(sf::RenderWindow* window);
	Gallant::Signal1<int*> on_tower_add;
	enum HUD_STATE {NONE,NEW_TOWER, TOWER_MENU};

	//Event handlers
	void OnNewWave(int);
	void OnCreepKilled(int bounty);
	void OnTowerAdded(Tower* tower);

private:
	void LoadContent();

	InputManager input;
	sf::RectangleShape bottomBar;
	float tower_radius_dream_size = 0;
	sf::CircleShape towerRadiusShape;
	sf::Texture t1_tex;
	sf::Sprite t1_sprite;
	int newTowerid = -1;



	float mouse_x;
	float mouse_y;
	sf::Sprite active_tower_sprite;

	sf::RectangleShape gridRect;
	const static int GRID_WIDTH = 64;
	HUD_STATE current_state;
	World::Map *map;

	Player *player1;

	vector<Player*> players;

	//UI Components
	UI::Label *waveLabel;
	UI::Label *goldLabel;
};