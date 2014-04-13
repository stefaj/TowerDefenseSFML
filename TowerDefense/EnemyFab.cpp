#include "EnemyFab.h"

EnemyFab::EnemyFab()
{

}

EnemyFab::EnemyFab(World::Map *m_)
{
	map = m_;

	cur_wave = 0;
	total_waves = 10;

	creeps_per_wave = 10;
	creeps_spawned_this_wave = 0;

	time_between_waves = 60;
	time_between_creeps = 1;

	current_creep_time = 0;
	current_wave_time = 0;
}

void EnemyFab::Draw(sf::RenderWindow *rw)
{

}

void EnemyFab::Update(sf::RenderWindow *rw, float elapsed_seconds)
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
		map->AddEnemy(Game_Entities::Enemy(0, 0));
		//Spawn Creep
	}
	else if (creeps_spawned_this_wave >= creeps_per_wave)
	{
		current_wave_time += elapsed_seconds;
	}
	else
	{
		current_creep_time += elapsed_seconds;
	}
}