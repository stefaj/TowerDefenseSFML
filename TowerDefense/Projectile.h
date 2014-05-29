#pragma once
#include "DrawableGameComponent.h"

#include <SFML/Graphics.hpp>
#include "PlayerObject.h"
#include "ProjectileStruct.h"

using namespace States;
using namespace sf;
namespace Game_Entities 
{
	class Projectile : public DrawableGameComponent, public PlayerObject
	{
	public:
		Projectile();
		Projectile(Networking::ProjectileStruct ps);
		~Projectile();

		void Draw(sf::RenderTarget *rw);
		void Update(float elapsed_seconds);
		const Vector2f GetPos();
		const Vector2f GetVelocity();
		const FloatRect GetBoundingBox();
		const float GetDamage();
		const float GetSpeed();
		const int GetLevel();
		
		void ChangeParameters(int lvl);

	private:
		Texture tex;
		Sprite sprite;
		Vector2f velocity;
		float damage;
		float speed;
		int level;
		const double angle_to_point(double x, double y);
	};

}