#include "Enemy.h"
#include <cmath>

using namespace Game_Entities;
Enemy::Enemy(int x, int y)
{
	speed = 50.0f;
	LoadContent();

	health = 100;
	maxHealth = 100;
	bounty = 1;

	velocity.x += 1;
	healthBar = HealthBar(25,5);

	

	stage_pos = 0;
	stage_index = 0;

	sprite.SetPosition(sf::Vector2f(x, y));
}

void Enemy::LoadContent()
{
	anim_up = new Animation::CharacterAnim();
	anim_down = new Animation::CharacterAnim();
	anim_left = new Animation::CharacterAnim();
	anim_right = new Animation::CharacterAnim();

	sf::String fileName = "sprites/Animations/Characters/052-Undead02.png";

	anim_up->SetParameters(40, 56);
	anim_down->SetParameters(40, 56);
	anim_left->SetParameters(40, 56);
	anim_right->SetParameters(40, 56);

	anim_up->LoadTexture(fileName, 3);
	anim_down->LoadTexture(fileName, 0);
	anim_left->LoadTexture(fileName, 1);
	anim_right->LoadTexture(fileName, 2);
	
	float anim_speed = 0.3f * (speed/60.0f);

	anim_up->SetFrameTime(anim_speed);
	anim_down->SetFrameTime(anim_speed);
	anim_left->SetFrameTime(anim_speed);
	anim_right->SetFrameTime(anim_speed);

	sprite.PlayAnimation(anim_up);
	sprite.SetScale(32 / 50.0f);

}

void Enemy::Update(float elapsed_seconds)
{
	UpdatePathing(elapsed_seconds);
	sprite.Update(elapsed_seconds);
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
	{
		//We arrived at our destination
		on_path_completed(this);
		return;
	}
	while (stage_pos > lengths[stage_index])
	{
		stage_pos -= lengths[stage_index];
		stage_index++;

		if (stage_index == points.size() - 1)
		{
			sprite.SetPosition(points[stage_index]);
			return;
		}
	}
	
	//Set Correct animations

	UpdateAnimation(directions[stage_index]);
	sprite.SetPosition(points[stage_index] + directions[stage_index] * stage_pos);
}

void Enemy::UpdateAnimation(sf::Vector2f direction)
{
	if (std::abs(direction.x) > std::abs(direction.y))
	{
		if (direction.x < 0)
			sprite.PlayAnimation(anim_left);
		else
			sprite.PlayAnimation(anim_right);
	}
	else
	{
		if (direction.y < 0)
			sprite.PlayAnimation(anim_up);
		else
			sprite.PlayAnimation(anim_down);
	}
}

void Enemy::Draw(sf::RenderTarget *rw)
{
	sprite.Draw(rw);
	sf::Vector2f pos = sprite.GetPosition();
	sf::FloatRect bounds = sprite.GetGlobalBounds();
	healthBar.Draw(pos.x + bounds.width / 4, pos.y - bounds.height / 8, (float)health / (float)maxHealth, rw);
}

void Enemy::UpdatePath(vector<TileNode> node_path)
{
	Path p = Path(node_path);
	UpdatePath(p);
}


void Enemy::UpdatePath(Path p)
{
	/*bool all_same = true;
	auto points_other = p.GetPoints();
	int s_other = points_other.size();

	auto points_this = path.GetPoints();
	int s_this = points_this.size();
	if (s_this > s_other)
	{
		for (int i = 0; i < s_other; i++)
		{
			if (points_other[i].x != points_this[s_this - s_other + i].x
				|| points_other[i].y != points_this[s_this - s_other + i].y)
			{
				all_same = false;
			}
		}
	}
	if (s_this == 0 || s_other == 0)
		all_same = false;
	if (all_same)
		return;*/

	//stage_pos = 0;
	stage_index = 0;
	path = p;
}

const Vector2f Enemy::GetPos()
{
	return sprite.GetPosition();

}

const FloatRect Enemy::GetBoundingBox()
{
	return sprite.GetGlobalBounds();
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
	sprite.SetPosition(pos);
}

const int Enemy::GetBounty()
{
	return bounty;
}

void Enemy::SetMaxHealth(float h)
{
	maxHealth = h;
	health = h;
}