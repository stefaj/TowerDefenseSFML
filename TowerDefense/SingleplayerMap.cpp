#include "SingleplayerMap.h"
#include "Wave.h"
#include "WaveList.h"

using namespace World;
SingleplayerMap::SingleplayerMap(sf::RenderWindow *rw, std::string mapname) : Map(rw,mapname)
{
	pathingArr = &t_[0][0];

	LoadContent();

	GeneratePathing(pathingArr);

	last_enemy_uid = 0;

	this->on_tower_added.Connect(this, &SingleplayerMap::PostTowerAdd);
}

void SingleplayerMap::LoadContent()
{
	

	gridRect = sf::RectangleShape(sf::Vector2f(GRID_WIDTH - 3, GRID_WIDTH - 3));
	gridRect.setFillColor(sf::Color(0, 0, 0, 25));
	gridRect.setOutlineThickness(1);
	gridRect.setOutlineColor(sf::Color(255, 255, 255, 50));

	cur_wave = 0;
	total_waves = noWaves;
	creeps_per_wave = waves[0].amount;;
	creeps_spawned_this_wave = 0;
	time_between_waves = 30;
	time_between_creeps = 1;
	current_creep_time = 0;
	current_wave_time = 0;

	for (int i = 0; i < TILES_X; i++)
	{
		for (int j = 0; j < TILES_Y; j++)
		{
			pathingArr[j*TILES_X + i] = TileNode(i, j, nullptr);
		}
	}

	for (auto layer = m_loader->GetLayers().begin(); layer != m_loader->GetLayers().end(); ++layer)
	{
		if (layer->name == "Start")
		{
			for (auto object = layer->objects.begin(); object != layer->objects.end(); ++object)
			{
				sf::Vector2f posto = object->GetPosition();
				startNode = TileNode((int)posto.x / 32, (int)posto.y / 32, nullptr);
			}
		}
		if (layer->name == "End")
		{
			for (auto object = layer->objects.begin(); object != layer->objects.end(); ++object)
			{
				sf::Vector2f posto = object->GetPosition();
				endNode = TileNode((int)posto.x / 32, (int)posto.y / 32, nullptr);
			}
		}
	}
}


SingleplayerMap::~SingleplayerMap()
{
}
//Single Player Wave Spawning
void SingleplayerMap::WaveSpawnUpdate(float elapsed_seconds)
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

		on_new_wave(cur_wave);

		creeps_per_wave = waves[cur_wave].amount;
		time_between_creeps = 15.0f / creeps_per_wave;

	}
	else if (current_creep_time > time_between_creeps)
	{
		current_creep_time = 0;

		Game_Entities::Enemy en(0, 0, last_enemy_uid, 2);
		en.SetPosition(Vector2f(startNode.x * 32, startNode.y * 32));
		en.ChangeType(cur_wave);
		if (last_enemyPath.size() == 0)
		{
			last_enemyPath = pathfinder->Search(startNode, endNode);
			last_enemyPath.insert(last_enemyPath.begin(), startNode);
		}
		en.UpdatePath(last_enemyPath);
		AddEnemy(en);
		creeps_spawned_this_wave++;
		last_enemy_uid++;
		on_creep_spawned(creeps_spawned_this_wave);

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

const int SingleplayerMap::GetCurrentWave()
{
	return cur_wave;
}

const int SingleplayerMap::GetMaxWaves()
{
	return total_waves;
}

const int SingleplayerMap::GetCurrentCreepNumber()
{
	return creeps_spawned_this_wave;
}

const int SingleplayerMap::GetCreepsPerWave()
{
	return creeps_per_wave;
}

void SingleplayerMap::OnNewEnemyReceived(EnemyStruct es)
{
	
}

void SingleplayerMap::update(float elapsed_seconds)
{
	if (localPlayer->GetLives() == 0)
	{
		on_game_over(localPlayer->GetCreepsKilled());
		localPlayer->RemoveLives(1);
	}
	if (localPlayer->GetLives() < 0)
	{
		

		return; //Pause if dead
	}

	DoProjectileCollision();
	WaveSpawnUpdate(elapsed_seconds);
}

void SingleplayerMap::PostTowerAdd(Tower *t)
{
	last_enemyPath.clear();
}

void SingleplayerMap::EnemyCompletedPath(Enemy *en)
{
	on_creep_killed(0); //Creep dies, get 0 bounty
	RemoveComponent(en);
	RemoveEnemyFromList(en);

	en->MarkForDeletion();

	localPlayer->RemoveLives(1);

	on_life_lost(1);

	if (localPlayer <= 0)
	{
		on_game_over(localPlayer->GetCreepsKilled());
	}

}