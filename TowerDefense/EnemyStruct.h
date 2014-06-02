#pragma once
#include "SFML\Network.hpp"
namespace Networking
{
	class EnemyStruct
	{
	public:
		EnemyStruct(){}

		sf::Int32 type_; //type and upgrade of enemy
		sf::Int32 owner_; //owner of the tower
		sf::Int32 UID;
		float x; //x position
		float y; //y position
		

		static int GetGoldCost(int level)
		{
			switch (level)
			{
			case 21:
				return 5;
			case 22:
				return 10;
			case 23:
				return 15;
			case 24:
				return 30;
			case 25:
				return 50;
			default:
				return 100;
			}
		}
	};

}