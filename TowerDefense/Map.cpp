#include "Map.h"
#include <algorithm>
#include "Wave.h"
#include "WaveList.h"
using namespace World;
//test TILENODE. Created such that the pointer to this does not lose value as t_ goes out of scope
//Needs fix though
TileNode t_[TILES_X][TILES_Y];


Map::Map(sf::RenderWindow *rw) : GameScreen(rw)
{
	pathingArr = &t_[0][0];

	LoadContent();	

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

	last_enemy_uid = 0;

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

void Map::AddNewTower(TowerStruct ts)
{
	
	int x = ts.x;
	int y = ts.y;
	
	Tower *t = new Tower(x,y,ts.type_,ts.owner_);
	t->ChangeParameters(ts.type_);
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

	for (int i = 0; i < towers.size(); i++)
	{
		Tower *ti = towers[i];
		if (ti->GetBoundingBox().intersects(rect))
		{
			collision = true;
			break;
		}
	}
	
	if (!collision && path)
	{
		t->SetEnemiesPointer(&enemies); 
		t->on_shoot.Connect(this, &World::Map::AddProjectile);
		
		
		
		towers.push_back(t);

		if (ts.owner_ == localPlayer->GetID())
		{
			localPlayer->RemoveGold(t->GetGoldCost());
		}
		if (ts.owner_ == remotePlayer->GetID())
		{
			remotePlayer->RemoveGold(t->GetGoldCost());
		}

		on_tower_added(t);

		if (peerConnection)
			peerConnection->Send(ts);
		
		AddComponent(t);
		
		UpdateEnemyPathing();


	}
	else
	{
		delete t;
	}

	peerConnection = NULL;
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
	for (int i = 0; i < towers.size(); i++)
	{
		Tower *t = towers.at(i);
		int x = t->GetX() / 32;
		int y = t->GetY() / 32;

		pathingArr[TILES_X * y + x].type = 1;
		pathingArr[TILES_X * (y + 1) + x].type = 1;
		pathingArr[TILES_X * y + (x + 1)].type = 1;
		pathingArr[TILES_X * (y + 1) + (x + 1)].type = 1;
	}

	//GeneratePathing(pathingArr);

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

	for (auto layer = m_loader->GetLayers().begin(); layer != m_loader->GetLayers().end(); ++layer)
	{
		if (layer->name == "Collision")
		{
			for (auto object = layer->objects.begin(); object != layer->objects.end(); ++object)
			{
				sf::FloatRect bb = object->GetAABB();
			
				for (int x = bb.left; x < bb.left + bb.width; x+=32)
				{
					for (int y = bb.top; y < bb.top+bb.height; y+=32)
					{
						int i = x / 32;
						int j = y / 32;
						pathingArr[j*TILES_X + i].type = TileNode::WALL;
					}
				}
				
			}
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


void Map::AddProjectile(ProjectileStruct ps)
{

	Projectile *p = new Projectile(ps);
	projectiles.push_back(p);

	if (localPlayer->IsHost())
	{
		if (peerConnection)
		{
			peerConnection->Send(ps);
		}
	}

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
					if (p->GetOwnerID() == localPlayer->GetID())
					{
						localPlayer->AddGold(en->GetBounty());
					}
					else
					{
						remotePlayer->AddGold(en->GetBounty());
					}

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

	if (localPlayer->IsHost())
	{
		Networking::EnemyStruct es;
		es.owner_ = 0;
		es.type_ = 0;
		es.x = en.GetPos().x;
		es.y = en.GetPos().y;
		if (peerConnection)
			peerConnection->Send(es);
	}


	AStar starretjie = AStar(TILES_X, TILES_Y, &pathingArr);
	Vector2f pos = new_en->GetPos();
	vector<TileNode> enemyPath = starretjie.Search(startNode, endNode);

	enemyPath.insert(enemyPath.begin(), startNode);
	new_en->UpdatePath(enemyPath);

	new_en->on_path_completed.Connect(this, &Map::EnemyCompletedPath);

	AddComponent(new_en);
	enemies.push_back(new_en);	


}

//Single Player Wave Spawning
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

		/*
		creeps_per_wave = 10;
		cur_wave = 0;
		total_waves = noWaves;
		
		creeps_spawned_this_wave = 0;
		time_between_waves = 30;
		time_between_creeps = 1;
		current_creep_time = 0;
		current_wave_time = 0;*/
		creeps_per_wave = waves[cur_wave].amount;
		time_between_creeps = 15.0f / creeps_per_wave;
		
	}
	else if (current_creep_time > time_between_creeps)
	{
		current_creep_time = 0;
		
		Game_Entities::Enemy en(0, 0,last_enemy_uid, 2);
		en.SetPosition(Vector2f(startNode.x * 32, startNode.y * 32));
		en.ChangeType(cur_wave);
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

	

	int player_id = localPlayer->GetID();

	if (player_id == localPlayer->GetID())
	{
		localPlayer->RemoveLives(1);
	}
	if (player_id == remotePlayer->GetID())
	{
		remotePlayer->RemoveLives(1);
	}
	on_life_lost(1);

}

void Map::SetPlayers(Player *local, Player *remote)
{
	this->localPlayer = local;
	this->remotePlayer = remote;

}
void Map::SetConnection(Connection *conn)
{
	this->peerConnection = conn;
	if (peerConnection)
	{

		peerConnection->OnNewEnemyReceived.Connect(this, &World::Map::OnNewEnemyReceived);
		peerConnection->OnNewProjectileRecieved.Connect(this, &World::Map::OnNewProjectileReceived);
		peerConnection->OnNewPSyncRecieved.Connect(this, &World::Map::OnNewPSyncReceived);
		peerConnection->OnNewTowerReceived.Connect(this, &World::Map::OnNewTowerReceived);
		peerConnection->OnRemoveEnemyReceived.Connect(this, &World::Map::OnRemoveEnemyReceived);
	}

}


void Map::SendPlayerSync()
{
	PlayerSyncStruct ps;
	localPlayer->GetLives();

	if (localPlayer->IsHost())
	{
		ps.p1_lives = localPlayer->GetLives();
		ps.p1_gold = localPlayer->GetGold();
		ps.p1_kills = localPlayer->GetCreepsKilled();
		ps.p2_gold = remotePlayer->GetGold();
		ps.p2_kills = remotePlayer->GetCreepsKilled();
	}
	else
	{
		ps.p1_lives = remotePlayer->GetLives();
		ps.p1_gold = remotePlayer->GetGold();
		ps.p1_kills = remotePlayer->GetCreepsKilled();
		ps.p2_gold = localPlayer->GetGold();
		ps.p2_kills = localPlayer->GetCreepsKilled();
	}

	if (peerConnection)
		peerConnection->Send(ps);
}

void Map::OnNewTowerReceived(TowerStruct ts)
{
	Tower *t = new Tower(ts.x, ts.y, ts.owner_,ts.owner_);
	t->ChangeParameters(ts.type_);
	t->SetEnemiesPointer(&enemies);
	t->on_shoot.Connect(this, &World::Map::AddProjectile);
	
	towers.push_back(t);
	AddComponent(t);
	UpdateEnemyPathing();

	if (ts.owner_ == localPlayer->GetID())
	{
		localPlayer->RemoveGold(t->GetGoldCost());
	}
	else
	{
		remotePlayer->RemoveGold(t->GetGoldCost());
	}

	on_tower_added(t);

}

void Map::OnNewEnemyReceived(EnemyStruct es)
{
	Game_Entities::Enemy en(0, 0,last_enemy_uid,es.owner_);
	en.SetPosition(sf::Vector2f(es.x,es.y));
	AddEnemy(en);
	creeps_spawned_this_wave++;
	on_creep_spawned(creeps_spawned_this_wave);
	last_enemy_uid++;
}

void Map::OnNewProjectileReceived(ProjectileStruct p)
{
	Vector2f projPos = sf::Vector2f(p.start_x, p.start_y);
	Vector2f enemyPos = sf::Vector2f(p.end_x, p.end_y);
	float dmg = p.damage;

	Projectile *proj = new Projectile(p);
	projectiles.push_back(proj);

	AddComponent(proj);
}

void Map::OnNewPSyncReceived(PlayerSyncStruct s)
{
	if (localPlayer->IsHost())
	{
		remotePlayer->SetLives(s.p2_lives);
		remotePlayer->SetCreepsKilled(s.p2_kills);
		remotePlayer->SetGold(s.p2_gold);
	}
	else
	{
		//player 1 host
		//player 2 client
		//We are player 2
		//If we are client we need to sync everything

		localPlayer->SetLives(s.p2_lives);
		localPlayer->SetCreepsKilled(s.p2_kills);
		localPlayer->SetGold(s.p2_gold);

		remotePlayer->SetLives(s.p1_lives);
		remotePlayer->SetCreepsKilled(s.p1_kills);
		remotePlayer->SetGold(s.p1_gold);
	}

}

void Map::OnRemoveEnemyReceived(RemoveEnemyStruct en)
{
	//only sync if we are client
	if (localPlayer->IsHost() == 1)
		return;

	for (int i = 0; i< enemies.size(); i++)
	{
		Enemy *e = enemies[i];
		if (e->GetUID() == en.uid)
		{
			e->MarkForDeletion();
			enemies.erase(enemies.begin() + i);
			delete e;
			return;
		}
	}
}