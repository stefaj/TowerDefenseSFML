#pragma once
#include "Map.h"
#include <SFML/Graphics.hpp>
#include "Tower.h"
#include <tmx/MapLoader.h>
#include "GameScreen.h"
#include "tile_node.h"
#include "astar.h"
#include <vector>
#include "Enemy.h"
#include "Path.h"
#include "Projectile.h"
#include "Constant.h"
#include "Signalling\Signal.h"
#include "Connection.h"
#include "Player.h"

#include "TowerStruct.h"
#include "ProjectileStruct.h"
#include "EnemyStruct.h"
#include "PlayerSyncStruct.h"
#include "RemoveEnemyStruct.h"

using namespace Networking;
using namespace Game_Entities;

namespace World
{
	
	class SingleplayerMap : public Map
	{
	public:
		SingleplayerMap(sf::RenderWindow *rw, std::string mapname);
		~SingleplayerMap();

		void update(float elapsed_seconds);

	private:
		void LoadContent();
		//Wave Spawning Magic
		int cur_wave;
		int total_waves;
		int creeps_per_wave;
		int creeps_spawned_this_wave;
		float time_between_waves;
		float time_between_creeps;
		float current_creep_time;
		float current_wave_time;
		const int GetCurrentWave();
		const int GetMaxWaves();
		const int GetCurrentCreepNumber();
		const int GetCreepsPerWave();
		vector<TileNode> last_enemyPath;
		
		void WaveSpawnUpdate(float elapsed_seconds);

		void PostTowerAdd(Tower *t);
		void EnemyCompletedPath(Enemy *en);

		void OnNewEnemyReceived(EnemyStruct es);

	};
}

