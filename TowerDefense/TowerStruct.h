#pragma once
#include "SFML\Network.hpp"
namespace Networking
{
	struct TowerStruct
	{
	public:
		TowerStruct(){}

		sf::Int32  type_; //type of tower and upgrade
		sf::Int32  owner_; //owner of the tower
		sf::Int32  x; //x position
		sf::Int32  y; //y position

		static int GetGoldCost(int level)
		{
			switch (level)
			{
			case 1:
				return 20;
			case 2:
				return 40;
			case 3:
				return 80;
			case 4:
				return 160;
			case 5:
				return 320;
			default:
				return 100;
			}
		}

	};
}