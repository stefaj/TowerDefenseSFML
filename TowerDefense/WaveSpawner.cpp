#include "WaveSpawner.h"

using namespace Game_Entities;

WaveSpawner::WaveSpawner()
{
}
/*
EnemySpawner::EnemySpawner(World::Map *m)
{
	//map = m;
	
	cur_wave=0;
	total_waves=10;

	creeps_per_wave=10;
	creeps_spawned_this_wave=0;

	time_between_waves=60;
	time_between_creeps=1;

	current_creep_time=0;
	current_wave_time=0;
}*/


WaveSpawner::~WaveSpawner()
{
}

void WaveSpawner::Draw(sf::RenderWindow* window)
{
	
}

void WaveSpawner::Update(sf::RenderWindow *rw, float elapsed_time)
{
	//We done
	if (cur_wave > total_waves)
	{
		return;
	}

	if (current_wave_time > time_between_waves)
	{
		//Spawn New Wave
		current_wave_time = 0;
		cur_wave++;
		creeps_spawned_this_wave = 0;
	}
	else if (current_creep_time > time_between_creeps)
	{
		current_creep_time = 0;
		//map->AddEnemy(Game_Entities::Enemy(0, 0));
		//Spawn Creep
	}
	else if (creeps_spawned_this_wave >= creeps_per_wave)
	{
		current_wave_time += elapsed_time;
	}
	else
	{
		current_creep_time += elapsed_time;
	}
	
}