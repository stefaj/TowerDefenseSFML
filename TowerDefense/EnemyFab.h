#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h";
#include "Enemy.h";
#include "DrawableGameComponent.h"
using namespace States;

class EnemyFab : public DrawableGameComponent
{
public:
	EnemyFab();
	EnemyFab(World::Map *m_);
	void Draw(sf::RenderWindow *rw);
	void Update(sf::RenderWindow *rw, float elapsed_seconds);

private:
	World::Map *map;
	int cur_wave;
	int total_waves;
	int creeps_per_wave;
	int creeps_spawned_this_wave;
	float time_between_waves;
	float time_between_creeps;
	float current_creep_time;
	float current_wave_time;
};