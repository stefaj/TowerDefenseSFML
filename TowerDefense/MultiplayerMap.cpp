#include "MultiplayerMap.h"

using namespace World;
MultiplayerMap::MultiplayerMap(sf::RenderWindow *rw, std::string mapname) : Map(rw, mapname)
{
	pathingArr = &t_[0][0];

	LoadContent();

	GeneratePathing(pathingArr);

	last_enemy_uid = 0;

	passiveIncomeCD = 0;

	updates = 0;

}

void MultiplayerMap::LoadContent()
{


	gridRect = sf::RectangleShape(sf::Vector2f(GRID_WIDTH - 3, GRID_WIDTH - 3));
	gridRect.setFillColor(sf::Color(0, 0, 0, 25));
	gridRect.setOutlineThickness(1);
	gridRect.setOutlineColor(sf::Color(255, 255, 255, 50));

	for (int i = 0; i < TILES_X; i++)
	{
		for (int j = 0; j < TILES_Y; j++)
		{
			pathingArr[j*TILES_X + i] = TileNode(i, j, nullptr);
		}
	}


	
	for (auto layer = m_loader->GetLayers().begin(); layer != m_loader->GetLayers().end(); ++layer)
	{
		//startnode is player 1 base
		if (layer->name == "Base1")
		{
			for (auto object = layer->objects.begin(); object != layer->objects.end(); ++object)
			{
				sf::Vector2f posto = object->GetPosition();
				startNode = TileNode((int)posto.x / 32, (int)posto.y / 32, nullptr);
			}
		}
		//end node is player 2 base
		if (layer->name == "Base2")
		{
			for (auto object = layer->objects.begin(); object != layer->objects.end(); ++object)
			{
				sf::Vector2f posto = object->GetPosition();
				endNode = TileNode((int)posto.x / 32, (int)posto.y / 32, nullptr);
			}
		}
	}
}


MultiplayerMap::~MultiplayerMap()
{
}

//From UI
void MultiplayerMap::OnAddEnemy(EnemyStruct e)
{
	localPlayer->RemoveGold(EnemyStruct::GetGoldCost(e.type_));
	localPlayer->AddPassiveIncome(EnemyStruct::GetGoldCost(e.type_) / 5);

	Game_Entities::Enemy en(e.x, e.y, ++last_enemy_uid, e.owner_);
	
	en.ChangeType(e.type_);
	en.SetPosition(sf::Vector2f(e.x, e.y));

	std::vector<TileNode> enemyPath;
	if (e.x == startNode.x *GRID_WIDTH && e.y == startNode.y*GRID_WIDTH)
	{
		enemyPath = pathfinder->Search(startNode, endNode);
		enemyPath.insert(enemyPath.begin(), startNode);
	}
	else
	{
		enemyPath = pathfinder->Search(endNode, startNode);
		enemyPath.insert(enemyPath.begin(), endNode);
	}
	en.UpdatePath(enemyPath);

	AddEnemy(en);
	on_creep_spawned(0);

	if (peerConnection)
	{
		e.UID = last_enemy_uid;
		peerConnection->Send(e);
		SendPlayerSync();
	}
}

//Receive from Network
void MultiplayerMap::OnNewEnemyReceived(EnemyStruct e)
{
	if (remotePlayer->GetID() == e.owner_)
	{
		remotePlayer->RemoveGold(EnemyStruct::GetGoldCost(e.type_));
		remotePlayer->AddPassiveIncome(EnemyStruct::GetGoldCost(e.type_) / 5);
	}
	

	Game_Entities::Enemy en(e.x, e.y, e.UID, e.owner_);

	en.ChangeType(e.type_);
	en.SetPosition(sf::Vector2f(e.x, e.y));

	std::vector<TileNode> enemyPath;
	if (e.x == startNode.x *GRID_WIDTH && e.y == startNode.y*GRID_WIDTH)
	{
		enemyPath = pathfinder->Search(startNode, endNode);
		enemyPath.insert(enemyPath.begin(), startNode);
	}
	else
	{
		enemyPath = pathfinder->Search(endNode, startNode);
		enemyPath.insert(enemyPath.begin(), endNode);
	}
	en.UpdatePath(enemyPath);

	sf::Color red = sf::Color(255, 0, 0, 255);
	sf::Color blue = sf::Color(0, 0, 255, 255);
	if (e.owner_ == 1)
	{
		en.SetTint(red);
	}
	else
	{
		en.SetTint(blue);
	}

	
	AddEnemy(en);
	on_creep_spawned(0);
	last_enemy_uid++;
}



void MultiplayerMap::update(float elapsed_seconds)
{
	if (updates++ % 30 == 0)
	{
		SendPlayerSync();

		for (int i = 0; i < enemies.size(); i++)
		{
			Enemy *en = enemies[i];

			UpdateEnemyStruct ues;
			ues.health = en->GetHealth();
			ues.UID = en->GetUID();
			ues.x = en->GetPos().x;
			ues.y = en->GetPos().y;
			if (peerConnection)
				peerConnection->Send(ues);
		}
	}

	
	if (localPlayer->GetLives() <= 0)
	{
		on_show_winner(false);
		return;
	}
	else if (remotePlayer->GetLives() <= 0)
	{
		on_show_winner(true);
		return;
	}


	passiveIncomeCD += elapsed_seconds;
	if (passiveIncomeCD > SECONDS_PER_PASSIVE_INCOME)
	{
		localPlayer->AddGold(localPlayer->GetPassiveIncome());
		remotePlayer->AddGold(remotePlayer->GetPassiveIncome());
		//SendPlayerSync();
		passiveIncomeCD = 0;
		on_creep_killed(0);
	}


	DoProjectileCollision();

	if (peerConnection)
		peerConnection->Update(elapsed_seconds);
}


void MultiplayerMap::EnemyCompletedPath(Enemy *en)
{
	on_creep_killed(0); //Creep dies, get 0 bounty
	RemoveComponent(en);
	RemoveEnemyFromList(en);

	en->MarkForDeletion();

	int player_id = localPlayer->GetID();

	if (en->GetOwnerID() == localPlayer->GetID())
	{
		remotePlayer->RemoveLives(1);
	}
	else
	{
		localPlayer->RemoveLives(1);
	}
	on_life_lost(1);

	if (localPlayer <= 0)
	{
		on_game_over(localPlayer->GetCreepsKilled());
	}

	RemoveEnemyStruct res;
	res.uid = en->GetUID();
	if (peerConnection)
		peerConnection->Send(res);

}


void MultiplayerMap::UpdateEnemyPathing()
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

	for (int i = 0; i < enemies.size(); i++)
	{
		Enemy *en = enemies.at(i);
		Vector2f pos = en->GetPos();
		TileNode enemyPos = TileNode(pos.x / 32, pos.y / 32, nullptr);

		TileNode destination;
		if (en->GetOwnerID() == 1)
		{
			destination = endNode;
		}
		else
			destination = startNode;

		vector<TileNode> enemyPath = pathfinder->Search(enemyPos, destination);

		enemyPath.insert(enemyPath.begin(), enemyPos);
		en->UpdatePath(enemyPath);
	}
}