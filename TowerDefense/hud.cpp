#include "hud.h";
#include <iostream>
#include <string>
#include<sstream>

HUD::HUD()
{
	

}

void HUD::LoadContent()
{
	bottomBar = sf::RectangleShape(sf::Vector2f(1280, 128));
	bottomBar.setPosition(0, 720 - 128);
	bottomBar.setFillColor(sf::Color(0, 0, 0, 100));
	bottomBar.setOutlineThickness(4);
	bottomBar.setOutlineColor(sf::Color(255, 255, 255, 100));

	if (!t1_tex.loadFromFile("sprites/CANNON_TOWER_STRUCTURE.png"))
	{
		// error...
	}
	t1_sprite.setTexture(t1_tex);
	t1_sprite.setPosition(128, WINDOW_HEIGHT - 128 + 64 + 1);
	t1_sprite.setOrigin(t1_tex.getSize().x / 2, t1_tex.getSize().y / 2);


	if (!tower_box_tex.loadFromFile("sprites/towersbox.png"))
	{
		// error...
	}
	tower_box.setTexture(tower_box_tex);

	gridRect = sf::RectangleShape(sf::Vector2f(TOWER_GRID_WIDTH - 3, TOWER_GRID_WIDTH - 3));
	gridRect.setFillColor(sf::Color(0, 0, 0, 25));
	gridRect.setOutlineThickness(1);
	gridRect.setOutlineColor(sf::Color(255, 255, 255, 50));

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

	
	std::ostringstream StrP2;
	StrP2 << "Gold " << player1->GetGold();
	std::string scoreP2(StrP2.str());

	goldLabel = new UI::Label();
	goldLabel->SetText(scoreP2);
	goldLabel->SetPosition(Vector2f(1050, 74));

	
	std::ostringstream StrP3;
	StrP3 << "Lives " << player1->GetLives();
	std::string scoreP3(StrP3.str());

	livesLabel = new UI::Label();
	livesLabel->SetText(scoreP3);
	livesLabel->SetPosition(Vector2f(1050, 138));
	
}


HUD::HUD(World::Map *m_, Player *pl)
{
	
	current_state = NONE;
	map = m_;
	player1 = pl;
	players.push_back(player1);

	LoadContent();
}

void HUD::draw(sf::RenderWindow *rw)
{
	sf::View prevView = rw->getView();
	sf::FloatRect viewPort = prevView.getViewport();
	sf::Vector2f size = prevView.getSize();
	sf::Vector2f center = prevView.getCenter();
	float rotation = prevView.getRotation();
	float left = center.x - size.x / 2;
	float top = center.y - size.y / 2;

	//bottomBar.setPosition(left, top + size.y - 128);
	t1_sprite.setPosition(left + 64, top + size.y - tower_box.getGlobalBounds().height + 72);

	tower_box.setPosition(left, top + size.y - tower_box.getGlobalBounds().height);
	rw->draw(tower_box);

	//rw->draw(bottomBar);
	rw->draw(t1_sprite);

	if (current_state==NEW_TOWER)
	{	
		DrawGrid(rw);
		rw->draw(active_tower_sprite);
	}

	if (current_state == TOWER_MENU)
	{
		rw->draw(towerRadiusShape);
	}

	waveLabel->Draw(rw);
	goldLabel->Draw(rw);
	livesLabel->Draw(rw);
}

void HUD::update(sf::RenderWindow *rw)
{	
	input.UpdateFirst(rw);
	//sf::Vector2i mouseVec = sf::Mouse::getPosition(*rw);
	sf::Vector2f mouseVecf = input.GetMousePosWorld();
	mouse_x = mouseVecf.x;
	mouse_y = mouseVecf.y;

	//snapped coordinates
	int x = (int)(mouse_x / 32); x *= 32;
	int y = (int)(mouse_y / 32); y *= 32;
	
	sf::Rect<float> mouseRect = sf::Rect<float>(mouse_x-1, mouse_y-1, 5, 5);
	
	if (t1_sprite.getGlobalBounds().intersects(mouseRect))
	{
		if (input.is_left_mb_clicked())
		{
			newTowerid = 1;
			current_state = NEW_TOWER;
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

	if (current_state == NONE && input.is_left_mb_pressed())
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
		active_tower_sprite.setTexture(t1_tex);
		int tower_cost = 10;
		if (input.is_left_mb_released() && player1->GetGold() >= tower_cost)
		{
			int vals[] = { x, y, newTowerid };
			on_tower_add(vals);
			newTowerid = -1;
			current_state = NONE;
		}
		if (player1->GetGold() < tower_cost)
		{
			//Play insufficient gold sound
		}
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
			gridRect.setPosition(sf::Vector2f(x, y));
			if (x % (GRID_WIDTH * 2) == 0 || y % (GRID_WIDTH * 2) == 0)
				window->draw(gridRect);

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

void HUD::OnCreepKilled(int bounty)
{
	player1->AddGold(bounty);
	std::ostringstream StrP2;
	StrP2 << "Gold " << player1->GetGold();
	std::string txt(StrP2.str());
	goldLabel->SetText(txt);
}

void HUD::OnTowerAdded(Tower* tower)
{
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i]->GetID() == tower->GetOwnerID())
		{
			players[i]->RemoveGold(tower->GetGoldCost());
			OnCreepKilled(0);
		}
	}
}

void HUD::OnLifeLost(int player_id)
{
	player1->RemoveLives(1);
	std::ostringstream StrP2;
	StrP2 << "Lives " << player1->GetLives();
	std::string txt(StrP2.str());
	livesLabel->SetText(txt);
}