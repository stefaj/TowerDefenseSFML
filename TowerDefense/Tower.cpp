#include "Tower.h"
#include <cmath>
using namespace Game_Entities;

Tower::Tower(int x, int y, int _id) : PlayerObject(1)
{
	tower_sprite = sf::Sprite();
	tower_tex = new sf::Texture();
	if (!tower_tex->loadFromFile("sprites/CANNON_TOWER_STRUCTURE.png"))
	{


	}
	tower_sprite.setPosition(x, y);

	tower_sprite.setTexture(*tower_tex);
	

	this->radius = 256;

	this->id = _id;

	attack_speed = 1.0f;
	cool_down = 0;
	damage = 20;
	gold_cost = 10;
}

Tower::Tower()
{
	radius = 128.0f;
	id = 0;
}

double Tower::angle_to_point(double x, double y)
{
	double dx = x - (tower_sprite.getPosition().x);
	double dy = y - (tower_sprite.getPosition().y);
	double angle = atan2(dy, dx) * 180 / (atan(1) * 4);

	return angle;
}

void Tower::Update(sf::RenderWindow *rw, float elapsed_seconds)
{
	
	cool_down += elapsed_seconds;
	if (cool_down > attack_speed && enemies)
	{
		for (int i = 0; i < enemies->size(); i++)
		{
			Enemy *en = enemies->at(i);
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
				on_shoot(vals);
				cool_down = 0;
				break;
			}
		}
	}

	//Uncomment if towers need to point to mouse cursor
	//double angle = angle_to_point(sf::Mouse::getPosition(*rw).x, sf::Mouse::getPosition(*rw).y);
	//tower_sprite.setRotation(angle - 90);
}

void Tower::Draw(sf::RenderWindow *rw)
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