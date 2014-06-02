#pragma once
#include "DrawableGameComponent.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.h"
#include "PlayerObject.h"
#include "Signalling\Signal.h";
#include "ProjectileStruct.h";

using namespace States;
namespace Game_Entities
{
	class Tower : public DrawableGameComponent, public PlayerObject
	{
	public:
		Tower();
		explicit Tower(int x, int y, int lvl, int playerID);
		void SetEnemiesPointer(std::vector<Enemy*> *enemy_list);
		void Draw(sf::RenderTarget *rw);
		void Update(float elapsed_seconds);
		const int GetX();
		const int GetY();
		const float GetRadius();
		const float GetAttackSpeed();
		const float GetDamage();
		const sf::Vector2f GetPosition();
		const sf::Vector2f GetCenteredPosition();
		const sf::FloatRect GetBoundingBox();
		const int GetUpgradeLevel();
		const int GetGoldCost();
		void SetTint(const sf::Color &col);
		Gallant::Signal1<Networking::ProjectileStruct> on_shoot;
		void ChangeParameters(int lvl);
		static int GetGoldCost(int level);
	private:
		sf::Texture *tower_tex;
		sf::Sprite tower_sprite;
		int level;
		float radius;
		//Attacks every attack_speed seconds
		float attack_speed;
		float cool_down;
		float damage;
		double angle_to_point(double x, double y);
		std::vector<Enemy*> *enemies;

		int upgrade_level;
	protected:
		float gold_cost;


	};
}