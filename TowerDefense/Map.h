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


using namespace Game_Entities;
namespace World
{
	class Map : public GameScreen
	{

	public:
		explicit Map(sf::RenderWindow *rw);
		Map();
		void draw();

		
		//called with boost
		void AddNewTower(int vals[]);
		void AddEnemy(Enemy en);

		sf::Vector2f GetSize();

		Tower* GetTower(sf::Vector2f point);

		//Wave Spawning Logic
		const int GetCurrentWave();
		const int GetMaxWaves();
		const int GetCurrentCreepNumber();
		const int GetCreepsPerWave();
		//Wave Spawning events
		//Note that int* is an array
		
		Gallant::Signal1<int> on_creep_spawned;
		Gallant::Signal1<int> on_new_wave;
		Gallant::Signal1<int> on_creep_killed;
		Gallant::Signal1<Tower*> on_tower_added;

	private:
		void update(float elapsed_seconds);
		void LoadContent();

		//called with boost
		void AddProjectile(sf::Vector2f vals[]);

		tmx::MapLoader *m_loader;
			
		vector<Tower*> towers;
		vector<Enemy*> enemies;
		vector<Projectile*> projectiles;
		
		bool DoesCollideWithCollisionLayer(sf::Vector2f point);
		bool DoesCollideWithCollisionLayer(sf::FloatRect rect);

		//DEBUGGING PURPOSES
		void DrawGrid();
		void DrawPathing();
		sf::RectangleShape gridRect;
		void UpdateEnemyPathing();
		DrawableGameComponent *fab;
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
		void DoProjectileCollision();
		void OnProjectileDie(Vector2f point);

		void RemoveEnemyFromList(Enemy *en);
		void RemoveProjectileFromList(Projectile *proj);
		void RemoveTowerFromList(Tower *t);

		//Wave Spawning Magic
		int cur_wave;
		int total_waves;
		int creeps_per_wave;
		int creeps_spawned_this_wave;
		float time_between_waves;
		float time_between_creeps;
		float current_creep_time;
		float current_wave_time;
		void WaveSpawnUpdate(float elapsed_seconds);
	};
}