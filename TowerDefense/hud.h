#pragma once
#include <SFML/Graphics.hpp>
#include <boost/signals.hpp>
#include <boost/bind.hpp>
#include "Map.h";
#include "InputManager.h"
#include "Label.h"
#include "Player.h"

class HUD
{
public:
	HUD();
	HUD(World::Map *m_, Player *player);
	void draw(sf::RenderWindow *rw);
	void update(sf::RenderWindow *rw);
	void DrawGrid(sf::RenderWindow* window);
	boost::signal <void(int*)> on_tower_add;

	enum HUD_STATE {NONE,NEW_TOWER, TOWER_MENU};

private:
	void LoadContent();

	InputManager input;
	sf::RectangleShape bottomBar;
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

	//UI Components
	UI::Label *waveLabel;
	UI::Label *goldLabel;
};