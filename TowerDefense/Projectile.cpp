#include "Projectile.h"
#include <cmath>
using namespace Game_Entities;

Projectile::Projectile()
{

}

Projectile::Projectile(Vector2f pos, Vector2f destination, Vector2f dmg) : PlayerObject(1)
{
	if (!tex.loadFromFile("sprites/bullet.png"))
	{


	}

	velocity = destination - pos;
	sprite.setPosition(pos);
	sprite.setTexture(tex);
	speed = 5.0f;

	damage = sqrtf(dmg.x*dmg.x + dmg.y*dmg.y);
}

Projectile::~Projectile()
{

}

void Projectile::Draw(sf::RenderTarget *rw)
{
	rw->draw(sprite);
}

void Projectile::Update(sf::RenderTarget *rw, float elapsed_seconds)
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