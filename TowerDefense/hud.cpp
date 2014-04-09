#include "hud.h";
#include <iostream>

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

	if (!t1_tex.loadFromFile("sprites/Upgr_1_toughnesstraining.png"))
	{
		// error...
	}
	t1_sprite.setTexture(t1_tex);
	t1_sprite.setPosition(128, 720 - 128 + 64 + 1);
	t1_sprite.setOrigin(t1_tex.getSize().x / 2, t1_tex.getSize().y / 2);

	gridRect = sf::RectangleShape(sf::Vector2f(GRID_WIDTH - 3, GRID_WIDTH - 3));
	gridRect.setFillColor(sf::Color(0, 0, 0, 25));
	gridRect.setOutlineThickness(1);
	gridRect.setOutlineColor(sf::Color(255, 255, 255, 50));

	bottomBar = sf::RectangleShape(sf::Vector2f(1280, 128));
	bottomBar.setPosition(0, 720 - 128);
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


}


HUD::HUD(World::Map *m_, Player *pl)
{
	
	current_state = NONE;
	map = m_;
	player1 = pl;

	LoadContent();
}

void HUD::draw(sf::RenderWindow *rw)
{
	rw->draw(bottomBar);
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
}

void HUD::update(sf::RenderWindow *rw)
{	
	input.UpdateFirst(rw);
	sf::Vector2i mouseVec = sf::Mouse::getPosition(*rw);
	sf::Vector2f mouseVecf = sf::Vector2f(mouseVec.x, mouseVec.y);
	mouse_x = mouseVec.x;
	mouse_y = mouseVec.y;

	//snapped coordinates
	int x = (int)(mouse_x / 32); x *= 32;
	int y = (int)(mouse_y / 32); y *= 32;
	
	sf::Rect<float> mouseRect = sf::Rect<float>(mouse_x, mouse_y, 5, 5);
	
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
		float r = selected_Tower->GetRadius();
		float curRad = towerRadiusShape.getRadius();
		float dr = r - curRad;

		if (curRad < r)
		{
			towerRadiusShape.setRadius(curRad + dr / 20);
		}
		else
		{
			//towerRadiusShape.setRadius(r);

		}
		towerRadiusShape.setOrigin(
			towerRadiusShape.getGlobalBounds().width / 2,
			towerRadiusShape.getGlobalBounds().height / 2);

	}

	if (current_state == NEW_TOWER)
	{
		active_tower_sprite.setPosition(x, y);
		active_tower_sprite.setTexture(t1_tex);

		if (input.is_left_mb_released())
		{
			int vals[] = { x, y, newTowerid };
			on_tower_add(vals);
			newTowerid = -1;
			current_state = NONE;
		}
	}

	//waveLabel.Update(rw, 0);

	input.UpdateLast();
}

void HUD::DrawGrid(sf::RenderWindow* window)
{
	for (int x = 0; x < 1024; x += GRID_WIDTH)
	{
		for (int y = 0; y < 512; y += GRID_WIDTH)
		{
			gridRect.setPosition(sf::Vector2f(x, y));
			if (x % (GRID_WIDTH * 2) == 0 || y % (GRID_WIDTH * 2) == 0)
				window->draw(gridRect);
		}
	}
}

