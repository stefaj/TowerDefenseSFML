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

	class MultiplayerMap : public Map
	{
	public:
		MultiplayerMap(sf::RenderWindow *rw, std::string mapname);
		~MultiplayerMap();

		void update(float elapsed_seconds);

		void OnAddEnemy(EnemyStruct e);

	private:
		void LoadContent();
		void EnemyCompletedPath(Enemy *en);
		void OnNewEnemyReceived(EnemyStruct es);
		void UpdateEnemyPathing();

		float passiveIncomeCD;
		const float SECONDS_PER_PASSIVE_INCOME = 30;

		int updates;

	};
}

