#pragma once
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
	class Map : public GameScreen
	{

	public:
		explicit Map(sf::RenderWindow *rw, std::string map_name);
		Map();
		~Map();
		void draw();
				
		void SetPlayers(Player *local, Player *remote);

		//called with boost
		//event handling
		void AddNewTower(TowerStruct ts);
		void AddEnemy(Enemy en);
		virtual void OnAddEnemy(EnemyStruct e);
		virtual void EnemyCompletedPath(Enemy *en);

		bool IsWall(sf::Vector2f point);
		void SetConnection(Connection *conn);

		sf::Vector2f GetSize();

		Tower* GetTower(sf::Vector2f point);

		//Wave Spawning Logic

		//Wave Spawning events
		//Note that int* is an array

		Gallant::Signal1<int> on_game_over;
		Gallant::Signal1<bool> on_show_winner;
		
		//Networking signals
		Gallant::Signal1<int> on_creep_spawned;
		Gallant::Signal1<int> on_new_wave;
		Gallant::Signal1<int> on_creep_killed; //
		Gallant::Signal1<Tower*> on_tower_added; //Parameter gives new tower
		Gallant::Signal1<int> on_life_lost; //Parameter gives player id

		virtual void OnNewTowerReceived(TowerStruct);
		virtual void OnNewEnemyReceived(EnemyStruct);
		virtual void OnNewProjectileReceived(ProjectileStruct);
		virtual void OnNewPSyncReceived(PlayerSyncStruct);
		virtual void OnRemoveEnemyReceived(RemoveEnemyStruct);
		virtual void OnUpdateEnemyReceived(UpdateEnemyStruct);

		const TileNode GetStartingNode();
		const TileNode GetEndNode();
		const bool IsMultiPlayerGame();

	protected:
		virtual void update(float elapsed_seconds);
		virtual void LoadContent();

		//called with boost
		void AddProjectile(ProjectileStruct ps);

		tmx::MapLoader *m_loader;
			
		vector<Tower*> towers;
		vector<Enemy*> enemies;
		vector<Projectile*> projectiles;
		
		bool DoesCollideWithCollisionLayer(sf::Vector2f point);
		bool DoesCollideWithCollisionLayer(sf::FloatRect rect);
		
		AStar *pathfinder;

		//DEBUGGING PURPOSES
		void DrawGrid();
		void DrawPathing();
		sf::RectangleShape gridRect;
		virtual void UpdateEnemyPathing();

		//PathFinding
		//Array of pathing information
		TileNode *pathingArr;
		//Where creeps spawn
		TileNode startNode;
		//The destination of the creeperss
		TileNode endNode;
		//Updates the pathingGrid
		void GeneratePathing(TileNode *pathingGrid);

		//Collision
		virtual void DoProjectileCollision();
		virtual void OnProjectileDie(Vector2f point);

		void RemoveEnemyFromList(Enemy *en);
		void RemoveProjectileFromList(Projectile *proj);
		void RemoveTowerFromList(Tower *t);

		int last_enemy_uid;

		//Networking
		Connection *peerConnection;
		Player *localPlayer;
		Player *remotePlayer;

		//Networking slots
		
		
		void SendPlayerSync();
		TileNode t_[TILES_X][TILES_Y];

	};
}