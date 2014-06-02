#include "Tower.h"
#include <cmath>
#include "TowerStruct.h"
using namespace Game_Entities;

Tower::Tower(int x, int y, int lvl, int playerId) : PlayerObject(playerId)
{
	tower_sprite = sf::Sprite();

	tower_tex = new sf::Texture();

	ChangeParameters(lvl);

	tower_sprite.setPosition(x, y);

	SetOwnerID(playerId);
	cool_down = 0;
}

Tower::Tower()
{
	radius = 128.0f;
}

void Tower::ChangeParameters(int lvl)
{
	level = lvl;
	if (lvl == 1)
	{
		if (!tower_tex->loadFromFile("sprites/towers/cannon_1.png"))
		{
		}

		tower_sprite.setTexture(*tower_tex);
		radius = 128;
		attack_speed = 1.0f;
		damage = 15;
		gold_cost = Networking::TowerStruct::GetGoldCost(lvl);
	}
	if (lvl == 2)
	{
		if (!tower_tex->loadFromFile("sprites/towers/cannon_2.png"))
		{
		}

		tower_sprite.setTexture(*tower_tex);
		radius = 256;
		attack_speed = 0.5f;
		damage = 10;
		gold_cost = Networking::TowerStruct::GetGoldCost(lvl);
	}
	if (lvl == 3)
	{
		if (!tower_tex->loadFromFile("sprites/towers/cannon_3.png"))
		{
		}

		tower_sprite.setTexture(*tower_tex);
		radius = 128;
		attack_speed = 1.0f;
		damage = 15;
		gold_cost = Networking::TowerStruct::GetGoldCost(lvl);
	}
	if (lvl == 4)
	{
		if (!tower_tex->loadFromFile("sprites/towers/cannon_4.png"))
		{
		}

		tower_sprite.setTexture(*tower_tex);
		radius = 128;
		attack_speed = 1.0f;
		
		damage = 15;
		gold_cost = Networking::TowerStruct::GetGoldCost(lvl);
	}
	if (lvl == 5)
	{
		if (!tower_tex->loadFromFile("sprites/towers/cannon_5.png"))
		{
		}

		tower_sprite.setTexture(*tower_tex);
		radius = 128;
		attack_speed = 1.0f;
		damage = 15;
		gold_cost = Networking::TowerStruct::GetGoldCost(lvl);
	}
	
}

void Tower::SetTint(const sf::Color &col)
{
	tower_sprite.setColor(col);
}


double Tower::angle_to_point(double x, double y)
{
	double dx = x - (tower_sprite.getPosition().x);
	double dy = y - (tower_sprite.getPosition().y);
	double angle = atan2(dy, dx) * 180 / (atan(1) * 4);

	return angle;
}

void Tower::Update(float elapsed_seconds)
{
	
	cool_down += elapsed_seconds;
	if (cool_down > attack_speed && enemies)
	{
		for (int i = 0; i < enemies->size(); i++)
		{
			Enemy *en = enemies->at(i);
			if (en->GetOwnerID() == this->GetOwnerID())
				continue;
			Vector2f dPos = en->GetPos() - GetPosition();
			float length = sqrtf(dPos.x*dPos.x + dPos.y * dPos.y);

			if (length < radius)
			{
				//Commence shooting
				Vector2f enemyPos = en->GetPos();
				Vector2f towerPos = GetPosition();
				enemyPos.x += en->GetBoundingBox().width / 2;
				enemyPos.y += en->GetBoundingBox().height / 2;
				Vector2f dmg(damage, 0);
				sf::Vector2f vals[] = { towerPos, enemyPos, dmg };
				
				Networking::ProjectileStruct ps;
				ps.damage = damage;
				ps.start_x = towerPos.x;
				ps.start_y = towerPos.y;
				ps.end_x = enemyPos.x;
				ps.end_y = enemyPos.y;
				ps.towerLevel = level;
				ps.owner_ = GetOwnerID();

				on_shoot(ps);
				
				cool_down = 0;
				break;
			}
		}
	}

	//Uncomment if towers need to point to mouse cursor
	//double angle = angle_to_point(sf::Mouse::getPosition(*rw).x, sf::Mouse::getPosition(*rw).y);
	//tower_sprite.setRotation(angle - 90);
}

void Tower::Draw(sf::RenderTarget *rw)
{
	rw->draw(tower_sprite);
}

const int Tower::GetX()
{
	return (int)tower_sprite.getPosition().x;
}

const int Tower::GetY()
{
	return (int)tower_sprite.getPosition().y;
}

const float Tower::GetRadius()
{
	return radius;
}

const float Tower::GetAttackSpeed()
{
	return attack_speed;
}

const float Tower::GetDamage()
{
	return damage;
}

const sf::FloatRect Tower::GetBoundingBox()
{
	return tower_sprite.getGlobalBounds();
}

const sf::Vector2f Tower::GetPosition()
{
	return tower_sprite.getPosition();
}

const sf::Vector2f Tower::GetCenteredPosition()
{
	sf::Vector2f vec = tower_sprite.getPosition();
	vec.x += GetBoundingBox().width/2;
	vec.y += GetBoundingBox().height / 2;
	return vec;
}

void Tower::SetEnemiesPointer(std::vector<Enemy*> *enemy_list)
{
	this->enemies = enemy_list;
}


const int Tower::GetGoldCost()
{
	return gold_cost;
}

const int Tower::GetUpgradeLevel()
{
	return upgrade_level;
}