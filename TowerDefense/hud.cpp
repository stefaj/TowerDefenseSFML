#include "hud.h";
#include <iostream>
#include <string>
#include<sstream>

HUD::HUD()
{
	updates = 0;

}

void HUD::LoadContent()
{
	bottomBar = sf::RectangleShape(sf::Vector2f(1280, 128));
	bottomBar.setPosition(0, 720 - 128);
	bottomBar.setFillColor(sf::Color(0, 0, 0, 100));
	bottomBar.setOutlineThickness(4);
	bottomBar.setOutlineColor(sf::Color(255, 255, 255, 100));


	isGameOver = false;
	if (!gameOverTex.loadFromFile("sprites/gameover.png")){}
	gameOver.setTexture(gameOverTex);
	gameOver.setPosition((WINDOW_WIDTH - gameOver.getGlobalBounds().width) / 2, (WINDOW_HEIGHT - gameOver.getGlobalBounds().height) / 2);

	
	if (!t1_tex.loadFromFile("sprites/towers/cannon_1.png")){}
	if (!t2_tex.loadFromFile("sprites/towers/cannon_2.png")){}
	if (!t3_tex.loadFromFile("sprites/towers/cannon_3.png")){}
	if (!t4_tex.loadFromFile("sprites/towers/cannon_4.png")){}
	if (!t5_tex.loadFromFile("sprites/towers/cannon_5.png")){}

	t1_sprite.setTexture(t1_tex); t1_sprite.setScale(0.5f, 0.5f);
	t2_sprite.setTexture(t2_tex); t2_sprite.setScale(0.5f, 0.5f);
	t3_sprite.setTexture(t3_tex); t3_sprite.setScale(0.5f, 0.5f);
	t4_sprite.setTexture(t4_tex); t4_sprite.setScale(0.5f, 0.5f);
	t5_sprite.setTexture(t5_tex); t5_sprite.setScale(0.5f, 0.5f);


	if (!e1_tex.loadFromFile("sprites/enemy_icons/enemy1.png")){}
	if (!e2_tex.loadFromFile("sprites/enemy_icons/enemy2.png")){}
	if (!e3_tex.loadFromFile("sprites/enemy_icons/enemy3.png")){}
	if (!e4_tex.loadFromFile("sprites/enemy_icons/enemy4.png")){}
	if (!e5_tex.loadFromFile("sprites/enemy_icons/enemy5.png")){}
	e1_sprite.setTexture(e1_tex); e1_sprite.setScale(0.5f, 0.5f);
	e2_sprite.setTexture(e2_tex); e2_sprite.setScale(0.5f, 0.5f);
	e3_sprite.setTexture(e3_tex); e3_sprite.setScale(0.5f, 0.5f);
	e4_sprite.setTexture(e4_tex); e4_sprite.setScale(0.5f, 0.5f);
	e5_sprite.setTexture(e5_tex); e5_sprite.setScale(0.5f, 0.5f);

	

	if (!tower_box_tex.loadFromFile("sprites/towersbox.png"))
	{
		// error...
	}
	tower_box.setTexture(tower_box_tex);

	gridRect = sf::RectangleShape(sf::Vector2f(TOWER_GRID_WIDTH - 1, TOWER_GRID_WIDTH - 1));
	gridRect.setFillColor(sf::Color(0, 0, 0, 25));
	gridRect.setOutlineThickness(1);
	gridRect.setOutlineColor(sf::Color(255, 255, 255, 30));


	towerPlaceRect = sf::RectangleShape(sf::Vector2f(32, 32 ));
	towerPlaceRect.setFillColor(sf::Color(255, 255, 0, 50));
	towerPlaceRect.setOutlineThickness(0);
	//towerPlaceRect.setOutlineColor(sf::Color(255, 255, 255, 0));

	bottomBar = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, 128));
	bottomBar.setPosition(0, WINDOW_HEIGHT - 128);
	bottomBar.setFillColor(sf::Color(0, 0, 0, 100));
	bottomBar.setOutlineThickness(4);
	bottomBar.setOutlineColor(sf::Color(255, 255, 255, 100));

	towerRadiusShape = sf::CircleShape(1);
	towerRadiusShape.setOrigin(0.5f, 0.5f);
	towerRadiusShape.setPosition(0, 0);
	towerRadiusShape.setFillColor(sf::Color(0, 255, 0, 150));
	towerRadiusShape.setOutlineThickness(4);
	towerRadiusShape.setOutlineColor(sf::Color(255, 255, 255, 50));

	waveLabel = new UI::Label();
	waveLabel->SetText("Wave 1");
	waveLabel->SetPosition(Vector2f(1050, 10));

	passiveGold = new UI::Label();
	passiveGold->SetText("Income: 0");
	passiveGold->SetPosition(Vector2f(1050, 10));

	
	std::ostringstream StrP2;
	StrP2 << "Gold " << localPlayer->GetGold();
	std::string scoreP2(StrP2.str());

	goldLabel = new UI::Label();
	goldLabel->SetText(scoreP2);
	goldLabel->SetPosition(Vector2f(1050, 74));

	
	std::ostringstream StrP3;
	StrP3 << "Lives " << localPlayer->GetLives();
	std::string scoreP3(StrP3.str());

	livesLabel = new UI::Label();
	livesLabel->SetText(scoreP3);
	livesLabel->SetPosition(Vector2f(1050, 138));

	killsLabel = new UI::Label();
	killsLabel->SetText("Kills: 0");
	killsLabel->SetPosition(Vector2f(1050, 202));
	
}


HUD::HUD(World::Map *m_, Player *local, Player *remote)
{
	
	current_state = NONE;
	map = m_;
	localPlayer = local;
	remotePlayer = remote;

	LoadContent();
}

void HUD::OnGameOver(int score)
{
	isGameOver = true;
	

}

void HUD::draw(sf::RenderWindow *rw)
{
	sf::View prevView = rw->getView();
	sf::FloatRect viewPort = prevView.getViewport();
	sf::Vector2f size = prevView.getSize();
	sf::Vector2f center = prevView.getCenter();
	float rotation = prevView.getRotation();
	float left = center.x - size.x / 2 + 800;
	float top = center.y - size.y / 2;

	//bottomBar.setPosition(left, top + size.y - 128);
	t1_sprite.setPosition(left + 16, top + size.y - tower_box.getGlobalBounds().height + 20);
	t2_sprite.setPosition(left + 54, top + size.y - tower_box.getGlobalBounds().height + 20);
	t3_sprite.setPosition(left + 92, top + size.y - tower_box.getGlobalBounds().height + 20);
	t4_sprite.setPosition(left + 132, top + size.y - tower_box.getGlobalBounds().height + 20);
	t5_sprite.setPosition(left + 174, top + size.y - tower_box.getGlobalBounds().height + 20);

	e1_sprite.setPosition(left + 16, top + size.y - tower_box.getGlobalBounds().height + 57);
	e2_sprite.setPosition(left + 57, top + size.y - tower_box.getGlobalBounds().height + 57);
	e3_sprite.setPosition(left + 98, top + size.y - tower_box.getGlobalBounds().height + 57);
	e4_sprite.setPosition(left + 136, top + size.y - tower_box.getGlobalBounds().height + 57);
	e5_sprite.setPosition(left + 174, top + size.y - tower_box.getGlobalBounds().height + 57);

	tower_box.setPosition(left, top + size.y - tower_box.getGlobalBounds().height);
	rw->draw(tower_box);

	//rw->draw(bottomBar);
	
	rw->draw(t1_sprite);
	rw->draw(t2_sprite);
	rw->draw(t3_sprite);
	rw->draw(t4_sprite);
	rw->draw(t5_sprite);
	if (map->IsMultiPlayerGame())
	{
		rw->draw(e1_sprite);
		rw->draw(e2_sprite);
		rw->draw(e3_sprite);
		rw->draw(e4_sprite);
		rw->draw(e5_sprite);
	}


	if (current_state==NEW_TOWER)
	{	
		DrawGrid(rw);
		rw->draw(active_tower_sprite);
	}

	if (current_state == TOWER_MENU)
	{
		rw->draw(towerRadiusShape);
	}
	if (!map->IsMultiPlayerGame())
		waveLabel->Draw(rw);
	if (map->IsMultiPlayerGame())
		passiveGold->Draw(rw);
	goldLabel->Draw(rw);
	livesLabel->Draw(rw);
	killsLabel->Draw(rw);

	if (isGameOver)
		rw->draw(gameOver);
}

void HUD::AddEnemy(int lvl)
{
	EnemyStruct es;
	es.owner_ = localPlayer->GetID();
	es.type_ = lvl;
	if (localPlayer->GetID() == 1)
	{
		es.x = map->GetStartingNode().x * GRID_WIDTH;
		es.y = map->GetStartingNode().y * GRID_WIDTH;
	}
	else
	{
		es.x = map->GetEndNode().x * GRID_WIDTH;
		es.y = map->GetEndNode().y * GRID_WIDTH;
	}
	on_enemy_add(es);
	OnCreepKilled(0);
	
}

void HUD::update(sf::RenderWindow *rw)
{	
	if (isGameOver)
		return;
	updates++;
	input.UpdateFirst(rw);
	
	//sf::Vector2i mouseVec = sf::Mouse::getPosition(*rw);
	sf::Vector2f mouseVecf = input.GetMousePosWorld();
	mouse_x = mouseVecf.x;
	mouse_y = mouseVecf.y;

	//snapped coordinates
	int x = (int)(mouse_x / 32); x *= 32;
	int y = (int)(mouse_y / 32); y *= 32;
	
	sf::Rect<float> mouseRect = sf::Rect<float>(mouse_x-1, mouse_y-1, 5, 5);

	// 
	// Spawning the enemies
	//
	if (e1_sprite.getGlobalBounds().intersects(mouseRect) && input.is_left_mb_clicked())
	{
		int lvl = 21;
		if (localPlayer->GetGold() >= EnemyStruct::GetGoldCost(lvl) && updates > 10)
		{
			AddEnemy(lvl);
			updates = 0;
		}
		
	}
	if (e2_sprite.getGlobalBounds().intersects(mouseRect) && input.is_left_mb_clicked())
	{
		int lvl = 22;
		if (localPlayer->GetGold() >= EnemyStruct::GetGoldCost(lvl) && updates > 10)
		{
			AddEnemy(lvl);
			updates = 0;
		}

	}
	if (e3_sprite.getGlobalBounds().intersects(mouseRect) && input.is_left_mb_clicked())
	{
		int lvl = 23;
		if (localPlayer->GetGold() >= EnemyStruct::GetGoldCost(lvl) && updates > 10)
		{
			AddEnemy(lvl);
			updates = 0;
		}

	}
	if (e4_sprite.getGlobalBounds().intersects(mouseRect) && input.is_left_mb_clicked())
	{
		int lvl = 24;
		if (localPlayer->GetGold() >= EnemyStruct::GetGoldCost(lvl) && updates > 10)
		{
			AddEnemy(lvl);
			updates = 0;
		}

	}
	if (e5_sprite.getGlobalBounds().intersects(mouseRect) && input.is_left_mb_clicked())
	{
		int lvl = 25;
		if (localPlayer->GetGold() >= EnemyStruct::GetGoldCost(lvl) && updates > 10)
		{
			AddEnemy(lvl);
			updates = 0;
		}

	}
	
	if (t1_sprite.getGlobalBounds().intersects(mouseRect) && input.is_left_mb_clicked())
	{
		if (localPlayer->GetGold() < Networking::TowerStruct::GetGoldCost(1))
		{
			return;
		}
		newTowerid = 1;
		current_state = NEW_TOWER;
		active_tower_sprite.setTexture(t1_tex);
	}
	if (t2_sprite.getGlobalBounds().intersects(mouseRect) && input.is_left_mb_clicked())
	{
		if (localPlayer->GetGold() < Networking::TowerStruct::GetGoldCost(2))
		{
			return;
		}
		newTowerid = 2;
		current_state = NEW_TOWER;
		active_tower_sprite.setTexture(t2_tex);
	}
	if (t3_sprite.getGlobalBounds().intersects(mouseRect) && input.is_left_mb_clicked())
	{
		if (localPlayer->GetGold() < Networking::TowerStruct::GetGoldCost(3))
		{
			return;
		}
		newTowerid = 3;
		current_state = NEW_TOWER;
		active_tower_sprite.setTexture(t3_tex);
	}
	if (t4_sprite.getGlobalBounds().intersects(mouseRect) && input.is_left_mb_clicked())
	{
		if (localPlayer->GetGold() < Networking::TowerStruct::GetGoldCost(4))
		{
			return;
		}
		newTowerid = 4;
		current_state = NEW_TOWER;
		active_tower_sprite.setTexture(t4_tex);
	}
	if (t5_sprite.getGlobalBounds().intersects(mouseRect) && input.is_left_mb_clicked())
	{
		if (localPlayer->GetGold() < Networking::TowerStruct::GetGoldCost(5))
		{
			return;
		}
			
		newTowerid = 5;
		current_state = NEW_TOWER;
		active_tower_sprite.setTexture(t5_tex);
	}


	if (current_state == NONE && input.is_left_mb_pressed() && !tower_box.getGlobalBounds().intersects(mouseRect))
	{
		sf::View prevView = rw->getView();
		sf::Vector2f oldcenter = prevView.getCenter();
		
		sf::Vector2f dcenter = mouseVecf - oldcenter;
		
		sf::View oldView = rw->getView();

		sf::Vector2f size = oldView.getSize();
		
		sf::Vector2f new_center = oldcenter + dcenter / 50.0f;

		float rotation = oldView.getRotation();
		float left = new_center.x - size.x / 2;
		float top = new_center.y - size.y / 2;

		if (left < 0)
			new_center.x = size.x / 2;
		if (top < 0)
			new_center.y = size.y / 2;
		if (left + size.x > TILES_X*GRID_WIDTH)
			new_center.x = TILES_X*GRID_WIDTH - size.x / 2;
		if (top + size.y > TILES_Y*GRID_WIDTH)
			new_center.y = TILES_Y*GRID_WIDTH - size.y / 2;
		oldView.setCenter(new_center);
		
		rw->setView(oldView);
	}

	
	if (current_state == NEW_TOWER)
	{
		active_tower_sprite.setPosition(x, y);
		//active_tower_sprite.setTexture(*t1_sprite.getTexture());
		
		int tower_cost = Networking::TowerStruct::GetGoldCost(newTowerid);
		if (input.is_left_mb_released() && localPlayer->GetGold() >= tower_cost)
		{
			if (map->IsMultiPlayerGame())
			{
				if (localPlayer->GetID() == 1)
				{
					if (y >= (TILES_Y - 1)*GRID_WIDTH / 2)
						return;;
				}
				if (localPlayer->GetID() == 2)
				{
					if (y < TILES_Y*GRID_WIDTH / 2)
						return;
				}
			}

			Networking::TowerStruct ts;
			ts.x = x;
			ts.y = y;
			ts.type_ = newTowerid;
			ts.owner_ = localPlayer->GetID();

			on_tower_add(ts);
			newTowerid = -1;
			current_state = NONE;
		}
		if (input.is_left_mb_released() && localPlayer->GetGold() < tower_cost)
		{
			//Play insufficient gold sound
		}
	}

	Tower *selected_Tower = map->GetTower(mouseVecf);
	if (selected_Tower && input.is_left_mb_clicked())
	{
		float r = selected_Tower->GetRadius();
		sf::Vector2f pos = selected_Tower->GetCenteredPosition();

		towerRadiusShape.setPosition(pos);
		towerRadiusShape.setRadius(1);

		current_state = TOWER_MENU;
	}
	if (input.is_right_mb_released())
		current_state = NONE;

	if (current_state == TOWER_MENU && selected_Tower)
	{
		tower_radius_dream_size = selected_Tower->GetRadius();

	}

	float curRad = towerRadiusShape.getRadius();
	if (current_state == TOWER_MENU && curRad < tower_radius_dream_size)
	{
		towerRadiusShape.setRadius(curRad*1.2);
		float curRad = towerRadiusShape.getRadius();
		float dr = tower_radius_dream_size - curRad;

		towerRadiusShape.setOrigin(
			towerRadiusShape.getGlobalBounds().width / 2,
			towerRadiusShape.getGlobalBounds().height / 2);
	}




	//waveLabel.Update(rw, 0);

	input.UpdateLast();
}

void HUD::DrawGrid(sf::RenderWindow* window)
{

	for (int x = 0; x < TILES_X*GRID_WIDTH; x += GRID_WIDTH)
	{
		for (int y = 0; y < TILES_Y*GRID_WIDTH; y += GRID_WIDTH)
		{
			if (map->IsMultiPlayerGame())
			{
				if (localPlayer->GetID() == 1)
				{
					if (y >= (TILES_Y - 1)*GRID_WIDTH / 2)
						continue;
				}
				if (localPlayer->GetID() == 2)
				{
					if (y < TILES_Y*GRID_WIDTH / 2)
						continue;
				}
			}
			gridRect.setPosition(sf::Vector2f(x, y));
			if (x % (GRID_WIDTH * 2) == 0 || y % (GRID_WIDTH * 2) == 0)
				window->draw(gridRect);

			

		}
	}

	int x = mouse_x / 32;
	int y = mouse_y / 32;
	x *= 32;
	y *= 32;

	for (int i = x; i < x + 64; i += 32)
	{
		for (int j = y; j < y + 64; j += 32)
		{
			bool wall = map->IsWall(Vector2f(i, j));
			if (wall)
			{
				towerPlaceRect.setFillColor(sf::Color(255, 0, 0, 50));
			}
			else
			{
				towerPlaceRect.setFillColor(sf::Color(0, 255, 0, 50));
			}
			if (map->IsMultiPlayerGame())
			{
				if (localPlayer->GetID() == 1)
				{
					if (y >= (TILES_Y - 1)*GRID_WIDTH / 2)
						towerPlaceRect.setFillColor(sf::Color(255, 0, 0, 50));
				}
				if (localPlayer->GetID() == 2)
				{
					if (y < TILES_Y*GRID_WIDTH / 2)
						towerPlaceRect.setFillColor(sf::Color(255, 0, 0, 50));
				}
			}
			towerPlaceRect.setPosition(i, j);
			window->draw(towerPlaceRect);
		}
	}

	
	
}


void HUD::OnNewWave(int n)
{
	std::ostringstream StrP2;
	StrP2 << "Wave " << n+1;
	std::string txt(StrP2.str());
	waveLabel->SetText(txt);

}

void HUD::OnCreepKilled(int n)
{
	//play sound?
	std::ostringstream StrP2;
	if (localPlayer)
		StrP2 << "Gold " << localPlayer->GetGold();
	std::string txt(StrP2.str());
	goldLabel->SetText(txt);

	std::ostringstream StrP3;
	StrP3 << "Income: " << localPlayer->GetPassiveIncome();
	passiveGold->SetText(StrP3.str());

	std::ostringstream StrP4;
	StrP4 << "Kills: " << localPlayer->GetCreepsKilled();
	killsLabel->SetText(StrP4.str());
}

void HUD::OnTowerAdded(Tower* tower)
{
	OnCreepKilled(0); //Update display
}

void HUD::OnLifeLost(int player_id)
{
	std::ostringstream StrP2;
	StrP2 << "Lives " << localPlayer->GetLives();
	std::string txt(StrP2.str());
	livesLabel->SetText(txt);
}