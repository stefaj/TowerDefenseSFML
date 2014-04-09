#include "Enemy.h"

using namespace Game_Entities;
Enemy::Enemy(int x, int y)
{
	if (!tex.loadFromFile("sprites/creatures/devil-monster-small.png"))
	{


	}
	sprite.setPosition(x, y);

	sprite.setTexture(tex);

	health = 100;
	maxHealth = 100;

	velocity.x += 1;
	healthBar = HealthBar(25,5);

	speed = 100.0f;
}

void Enemy::Update(sf::RenderWindow *rw, float elapsed_seconds)
{
	UpdatePathing(elapsed_seconds);
}

void Enemy::UpdatePathing(float seconds)
{
	vector<Vector2f> points = path.GetPoints();
	vector<float> lengths = path.GetLengths();
	vector<Vector2f> directions = path.GetDirections();

	if (points.size() == 0)
		return;

	if (stage_index != points.size() - 1)
	{
		stage_pos += speed * seconds;

	}
	else
		return;
	while (stage_pos > lengths[stage_index])
	{
		stage_pos -= lengths[stage_index];
		stage_index++;

		if (stage_index == points.size() - 1)
		{
			sprite.setPosition(points[stage_index]);
			return;
		}
	}

	sprite.setPosition(points[stage_index] + directions[stage_index] * stage_pos);
}

void Enemy::Draw(sf::RenderWindow *rw)
{
	sprite.setTexture(tex);
	rw->draw(sprite);
	sf::Vector2f pos = sprite.getPosition();

	healthBar.Draw(pos.x + tex.getSize().x / 4, pos.y - tex.getSize().y / 8, (float)health / (float)maxHealth, rw);
}

void Enemy::UpdatePath(vector<TileNode> node_path)
{
	Path p = Path(node_path);
	UpdatePath(p);
}


void Enemy::UpdatePath(Path p)
{
	stage_pos = 0;
	stage_index = 0;
	path = p;
}

const Vector2f Enemy::GetPos()
{
	return sprite.getPosition();

}

const FloatRect Enemy::GetBoundingBox()
{
	return sprite.getGlobalBounds();
}

void Enemy::ReduceHealth(float amount)
{
	health -= amount;
}

const bool Enemy::IsDead()
{
	return health <= 0;
}

const float Enemy::GetHealth()
{
	return health;
}

const float Enemy::GetMaxHealth()
{
	return maxHealth;
}

void Enemy::SetPosition(Vector2f pos)
{
	sprite.setPosition(pos);
}