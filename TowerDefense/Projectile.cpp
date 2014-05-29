#include "Projectile.h"
#include <cmath>

using namespace Game_Entities;

Projectile::Projectile()
{

}

Projectile::Projectile(Networking::ProjectileStruct ps) : PlayerObject(ps.owner_)
{
	sf::Vector2f pos = sf::Vector2f(ps.start_x, ps.start_y);
	sf::Vector2f destination = sf::Vector2f(ps.end_x, ps.end_y);
	sprite.setPosition(pos);
	velocity = destination - pos;
	level = ps.towerLevel;
	ChangeParameters(level);
	damage = ps.damage;
	SetOwnerID(ps.owner_);
}

Projectile::~Projectile()
{

}

void Projectile::ChangeParameters(int lvl)
{
	
	level = lvl;
	if (level == 1)
	{
		if (!tex.loadFromFile("sprites/bullet.png"))
		{
		}

		sprite.setTexture(tex);
		speed = 5.0f;
	}
}

const int  Projectile::GetLevel()
{
	return level;
}

void Projectile::Draw(sf::RenderTarget *rw)
{
	rw->draw(sprite);
}

void Projectile::Update(float elapsed_seconds)
{
	Vector2f cur_pos = GetPos();
	cur_pos += velocity * speed * elapsed_seconds;
	sprite.setPosition(cur_pos);
}

const Vector2f Projectile::GetPos()
{
	return sprite.getPosition();
}

const FloatRect Projectile::GetBoundingBox()
{
	return sprite.getGlobalBounds();
}

const double Projectile::angle_to_point(double x, double y)
{
	double dx = x - sprite.getPosition().x;
	double dy = y - sprite.getPosition().y;
	double angle = atan2(dy, dx) * 180 / (atan(1) * 4);

	return angle;
}

const float Projectile::GetDamage()
{
	return damage;
}

const float Projectile::GetSpeed()
{
	return speed;
}