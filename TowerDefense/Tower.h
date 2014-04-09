#pragma once
#include "DrawableGameComponent.h"
#include <SFML/Graphics.hpp>
#include <boost/signal.hpp>
#include <boost/bind.hpp>
#include <vector>
#include "Enemy.h"
#include "PlayerObject.h"

using namespace States;
namespace Game_Entities
{
	class Tower : public DrawableGameComponent, PlayerObject
	{
	public:
		Tower();
		explicit Tower(int, int, int);
		void SetEnemiesPointer(std::vector<Enemy*> *enemy_list);
		void Draw(sf::RenderWindow *rw);
		void Update(sf::RenderWindow *rw, float elapsed_seconds);
		const int GetX();
		const int GetY();
		const float GetRadius();
		const float GetAttackSpeed();
		const float GetDamage();
		const sf::Vector2f GetPosition();
		const sf::Vector2f GetCenteredPosition();
		const sf::FloatRect GetBoundingBox();
		const int GetGoldCost();
		boost::signal<void(sf::Vector2f*)> on_shoot;
	private:
		sf::Texture *tower_tex;
		sf::Sprite tower_sprite;
		int id;
		float radius;
		//Attacks every attack_speed seconds
		float attack_speed;
		float cool_down;
		float damage;
		double angle_to_point(double x, double y);
		std::vector<Enemy*> *enemies;
	protected:
		float gold_cost;


	};
}