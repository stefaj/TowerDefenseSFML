#pragma once
#include "DrawableGameComponent.h"

#include <SFML/Graphics.hpp>
#include "PlayerObject.h"

using namespace States;
using namespace sf;
namespace Game_Entities 
{
	class Projectile : public DrawableGameComponent, PlayerObject
	{
	public:
		Projectile();
		Projectile(Vector2f position, Vector2f destination, Vector2f dmg);
		~Projectile();

		void Draw(sf::RenderWindow *rw);
		void Update(sf::RenderWindow *rw, float elapsed_seconds);
		const Vector2f GetPos();
		const Vector2f GetVelocity();
		const FloatRect GetBoundingBox();
		const float GetDamage();
		const float GetSpeed();
		
	private:
		Texture tex;
		Sprite sprite;
		Vector2f velocity;
		float damage;
		float speed;
		const double angle_to_point(double x, double y);
	};

}