#include "Map.h"
#include <algorithm>

using namespace World;
//test TILENODE. Created such that the pointer to this does not lose value as t_ goes out of scope
//Needs fix though
TileNode t_[TILES_X][TILES_Y];

Map::Map(sf::RenderWindow *rw) : GameScreen(rw)
{
	LoadContent();

	pathingArr = &t_[0][0];

	for (auto layer = m_loader->GetLayers().begin(); layer != m_loader->GetLayers().end(); ++layer)
	{
		if (layer->name == "Start")
		{
			for (auto object = layer->objects.begin(); object != layer->objects.end(); ++object)
			{				
				sf::Vector2f posto = object->GetPosition();
				startNode = TileNode((int)posto.x/32, (int)posto.y/32, nullptr);
			}
		}
		if (layer->name == "End")
		{
			for (auto object = layer->objects.begin(); object != layer->objects.end(); ++object)
			{
				sf::Vector2f posto = object->GetPosition();
				endNode = TileNode((int)posto.x/32, (int)posto.y/32, nullptr);
			}
		}
	}
	GeneratePathing(pathingArr);
	AStar starretjie = AStar(TILES_X, TILES_Y, &pathingArr);

//	AddEnemy(Enemy(0, 0));

}

void Map::LoadContent()
{
	m_loader = new tmx::MapLoader("maps/");
	m_loader->Load("map3.tmx");
	m_loader->UpdateQuadTree(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

	gridRect = sf::RectangleShape(sf::Vector2f(GRID_WIDTH - 3, GRID_WIDTH - 3));
	gridRect.setFillColor(sf::Color(0, 0, 0, 25));
	gridRect.setOutlineThickness(1);
	gridRect.setOutlineColor(sf::Color(255, 255, 255, 50));

	cur_wave = 0;
	total_waves = 10;
	creeps_per_wave = 10;
	creeps_spawned_this_wave = 0;
	time_between_waves = 30;
	time_between_creeps = 1;
	current_creep_time = 0;
	current_wave_time = 0;

}


Map::Map(): GameScreen(nullptr)
{

}


void Map::draw()
{
	render_window->draw(*m_loader);

	//DrawPathing();
	//DrawGrid();
}

void Map::update(float elapsed_seconds)
{
	DoProjectileCollision();
	WaveSpawnUpdate(elapsed_seconds);


}

bool Map::DoesCollideWithCollisionLayer(sf::FloatRect rect)
{
	rect.width -= 1;
	rect.height -= 1;
	sf::Vector2f top_left = sf::Vector2f(rect.left, rect.top);
	sf::Vector2f top_right = sf::Vector2f(rect.left + rect.width, rect.top);
	sf::Vector2f bottom_left = sf::Vector2f(rect.left, rect.top + rect.height);
	sf::Vector2f bottom_right = sf::Vector2f(rect.left + rect.height, rect.top + rect.height);

	for (auto layer = m_loader->GetLayers().begin(); layer != m_loader->GetLayers().end(); ++layer)
	{
		if (layer->name == "Collision")
		{

			for (auto object = layer->objects.begin(); object != layer->objects.end(); ++object)
			{

				if (object->Contains(top_left) || object->Contains(top_right) || object->Contains(bottom_left) || object->Contains(bottom_right))
					return true;
			}
		}
	}
	return false;
}

bool Map::DoesCollideWithCollisionLayer(sf::Vector2f point)
{
	for (auto layer = m_loader->GetLayers().begin(); layer != m_loader->GetLayers().end(); ++layer)
	{
		if (layer->name == "Collision")
		{
			for (auto object = layer->objects.begin(); object != layer->objects.end(); ++object)
			{
				if (object->Contains(point))
					return true;
			}
		}
	}
	return false;
}

void Map::AddNewTower(int vals[])
{
	
	int x = vals[0];
	int y = vals[1];
	int id = vals[2];
	
	Tower *t = new Tower(x, y, id);
	sf::FloatRect rect = t->GetBoundingBox();
	
	
	
	//See if there exists a path;
	x = x / 32;
	y = y / 32;
	int oldPath_topleft = pathingArr[TILES_X * y + x].type;
	int oldPath_bottomleft = pathingArr[TILES_X * (y + 1) + x].type;
	int oldPath_topright = pathingArr[TILES_X * y + (x + 1)].type;
	int oldPath_bottomright = pathingArr[TILES_X * (y + 1) + (x + 1)].type;

	pathingArr[TILES_X * y + x].type = 1;
	pathingArr[TILES_X * (y + 1) + x].type = 1;
	pathingArr[TILES_X * y + (x + 1)].type = 1;
	pathingArr[TILES_X * (y + 1) + (x + 1)].type = 1;

	AStar starretjie = AStar(TILES_X, TILES_Y, &pathingArr);
	vector<TileNode> enemyPath = starretjie.Search(startNode, endNode);
	bool path = enemyPath.size() > 0;
	pathingArr[TILES_X * y + x].type = oldPath_topleft;
	pathingArr[TILES_X * (y + 1) + x].type = oldPath_bottomleft;
	pathingArr[TILES_X * y + (x + 1)].type = oldPath_topright;
	pathingArr[TILES_X * (y + 1) + (x + 1)].type = oldPath_bottomright;

	
	//See if collision
	bool collision = DoesCollideWithCollisionLayer(rect);

	if (!collision && path)
	{
		t->SetEnemiesPointer(&enemies); 
		t->on_shoot.Connect(this, &World::Map::AddProjectile);
		on_tower_added(t);
		towers.push_back(t);
		
		AddComponent(t);
		
		UpdateEnemyPathing();
	}
	else
	{
		delete t;
	}
}

void Map::DrawGrid()
{
	
	for (int x = 0; x < 1024; x += GRID_WIDTH)
	{
		for (int y = 0; y < 512; y += GRID_WIDTH)
		{
			sf::Vector2f point = sf::Vector2f(x, y);
			if (DoesCollideWithCollisionLayer(point))
				continue;
			gridRect.setPosition(point);
			if (x % (GRID_WIDTH * 2) == 0 || y % (GRID_WIDTH * 2) == 0)
				render_window->draw(gridRect);
		}
	}
}

void Map::DrawPathing()
{

	for (int x = 0; x < TILES_X; x++)
	{
		for (int y = 0; y < TILES_Y; y++)
		{
			int ix = TILES_X*y + x;
			TileNode curNode = pathingArr[ix];

			sf::Vector2f point = sf::Vector2f(x*32, y*32);
			if (curNode.type == 1)
			{
				gridRect.setFillColor(sf::Color(255, 0, 0, 100));
				gridRect.setOutlineThickness(1);
				gridRect.setOutlineColor(sf::Color(255, 255, 255, 50));
			}
			else if (curNode.type == 0)
			{
				gridRect.setFillColor(sf::Color(0, 0, 0, 20));
				gridRect.setOutlineThickness(1);
				gridRect.setOutlineColor(sf::Color(255, 255, 255, 50));
			}
			
			gridRect.setPosition(point);
			render_window->draw(gridRect);
		}
	}

/*	for (int i = 0; i < testPath.size(); i++)
	{
		TileNode cur = testPath.at(i);
		int x = cur.x * 32;
		int y = cur.y * 32;

		gridRect.setFillColor(sf::Color(0, 255, 255, 100));
		gridRect.setOutlineThickness(1);
		gridRect.setOutlineColor(sf::Color(255, 255, 255, 50));

		gridRect.setPosition(sf::Vector2f(x,y));

		render_window->draw(gridRect);
		
	}*/

	//Start
	TileNode cur = startNode;
	int x = cur.x * 32;
	int y = cur.y * 32;
	gridRect.setFillColor(sf::Color(0, 255, 0, 100));
	gridRect.setOutlineThickness(1);
	gridRect.setOutlineColor(sf::Color(255, 255, 255, 50));
	gridRect.setPosition(sf::Vector2f(x, y));
	render_window->draw(gridRect);

	//End
	cur = endNode;
	x = cur.x * 32;
	y = cur.y * 32;
	gridRect.setFillColor(sf::Color(255, 255, 0, 100));
	gridRect.setOutlineThickness(1);
	gridRect.setOutlineColor(sf::Color(255, 255, 255, 50));
	gridRect.setPosition(sf::Vector2f(x, y));
	render_window->draw(gridRect);

}

void Map::UpdateEnemyPathing()
{
	GeneratePathing(pathingArr);

	AStar starretjie = AStar(TILES_X, TILES_Y, &pathingArr);

	for (int i = 0; i < enemies.size(); i++)
	{
		Enemy *en = enemies.at(i);
		Vector2f pos = en->GetPos();
		TileNode enemyPos = TileNode(pos.x / 32, pos.y / 32, nullptr);
		vector<TileNode> enemyPath = starretjie.Search(enemyPos, endNode);

		enemyPath.insert(enemyPath.begin(), enemyPos);
		en->UpdatePath(enemyPath);
		
	}

	
}

void Map::GeneratePathing(TileNode *pathingArr)
{
	for (int i = 0; i < TILES_X; i++)
	{
		for (int j = 0; j<TILES_Y; j++)
		{
			pathingArr[j*TILES_X + i] = TileNode(i, j, nullptr);
					
			int t = 0;

			sf::Vector2f point(i * GRID_WIDTH, j * GRID_WIDTH);

			sf::FloatRect rect = sf::FloatRect(i * GRID_WIDTH, j * GRID_WIDTH, GRID_WIDTH-1, GRID_WIDTH-1);
			
			
			bool collide = DoesCollideWithCollisionLayer(point);
			
			if (collide)
				t = 1;
			
			pathingArr[j*TILES_X + i].type = t;
		}
	}

	for (int i = 0; i < towers.size(); i++)
	{
		Tower *t = towers.at(i);
		int x = t->GetX() / 32;
		int y = t->GetY() / 32;

		pathingArr[TILES_X * y + x].type = 1;
		pathingArr[TILES_X * (y+1) + x].type = 1;
		pathingArr[TILES_X * y + (x+1)].type = 1;
		pathingArr[TILES_X * (y+1) + (x+1)].type = 1;
	}	
}

Tower* Map::GetTower(sf::Vector2f point)
{
	sf::Vector2f mouseSize = sf::Vector2f(5, 5);
	sf::FloatRect mouseRec = sf::FloatRect(point, mouseSize);

	for (int i = 0; i < towers.size(); i++)
	{
		Tower *t = towers.at(i);
		sf::FloatRect boundingBox = t->GetBoundingBox();
		if (boundingBox.intersects(mouseRec))
		{
			return t;
		}
	}
	return nullptr;
}


void Map::AddProjectile(sf::Vector2f vals[])
{
	Vector2f projPos = vals[0];
	Vector2f enemyPos = vals[1];
	Vector2f dmg = vals[2];

	Projectile *p = new Projectile(projPos, enemyPos,dmg);
	projectiles.push_back(p);

	AddComponent(p);
}

void Map::DoProjectileCollision()
{
	
	FloatRect playArea(0, 0, m_loader->GetMapSize().x, m_loader->GetMapSize().y);
	//Doth enemy get hit?
	for (int j = 0; j < projectiles.size(); j++)
	{
		Projectile *p = projectiles.at(j);
		for (int i = 0; i < enemies.size(); i++)
		{
			Enemy *en = enemies.at(i);
			if (p->GetBoundingBox().intersects(en->GetBoundingBox()))
			{
				en->ReduceHealth(p->GetDamage());

				//Destroy dead enemy
				if (en->IsDead())
				{
					on_creep_killed(en->GetBounty());
					RemoveComponent(en);
					RemoveEnemyFromList(en);
					delete en;
				}

				//Destroy Projectile
				OnProjectileDie(p->GetPos());
				RemoveComponent(p);
				RemoveProjectileFromList(p);
				delete p;
				break;
			}
		}		
	}

	for (int j = 0; j < projectiles.size(); j++)
	{
		Projectile *p = projectiles.at(j);
		if (p)
		{

			if (!playArea.intersects(p->GetBoundingBox()))
			{
				RemoveComponent(p);
				RemoveProjectileFromList(p);
				delete p;
			}
		}
	}

	//Remove unneeded projectiles
}

void Map::OnProjectileDie(Vector2f point)
{

}


//TO DO
//Make generic
void Map::RemoveEnemyFromList(Enemy *en)
{
	auto item = std::find(enemies.begin(), enemies.end(), en);
	enemies.erase(item);
}

void Map::RemoveProjectileFromList(Projectile *proj)
{
	auto item = std::find(projectiles.begin(), projectiles.end(), proj);
	projectiles.erase(item);
}

void Map::RemoveTowerFromList(Tower *t)
{
	auto item = std::find(towers.begin(), towers.end(), t);
	towers.erase(item);
}

sf::Vector2f Map::GetSize()
{
	if (m_loader)
		return sf::Vector2f(m_loader->GetMapSize().x, m_loader->GetMapSize().y);
}

void Map::AddEnemy(Enemy en)
{
	Enemy *new_en = new Enemy(en);
	new_en->SetPosition(Vector2f(startNode.x * 32, startNode.y * 32));


	AStar starretjie = AStar(TILES_X, TILES_Y, &pathingArr);
	Vector2f pos = new_en->GetPos();
	vector<TileNode> enemyPath = starretjie.Search(startNode, endNode);

	enemyPath.insert(enemyPath.begin(), startNode);
	new_en->UpdatePath(enemyPath);

	new_en->on_path_completed.Connect(this, &Map::EnemyCompletedPath);

	AddComponent(new_en);
	enemies.push_back(new_en);	

}


void Map::WaveSpawnUpdate(float elapsed_seconds)
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
		
	}
	else if (current_creep_time > time_between_creeps)
	{
		current_creep_time = 0;
		Game_Entities::Enemy en(0, 0);
		en.SetMaxHealth(100 + 30 * (cur_wave + 1));
		AddEnemy(en);
		creeps_spawned_this_wave++;
		
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

const int Map::GetCurrentWave()
{
	return cur_wave;
}

const int Map::GetMaxWaves()
{
	return total_waves;
}

const int Map::GetCurrentCreepNumber()
{
	return creeps_spawned_this_wave;
}

const int Map::GetCreepsPerWave()
{
	return creeps_per_wave;
}

void Map::EnemyCompletedPath(Enemy *en)
{
	on_creep_killed(0); //Creep dies, get 0 bounty
	RemoveComponent(en);
	RemoveEnemyFromList(en);

	en->MarkForDeletion();
	//delete en;

	on_life_lost(1);
}