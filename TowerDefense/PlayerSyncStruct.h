#pragma once

#include "SFML\Network.hpp"
namespace Networking
{
	class PlayerSyncStruct
	{
	public:
		PlayerSyncStruct(){}

		sf::Int32  p1_lives;
		sf::Int32  p2_lives;
		sf::Int32  p1_kills;
		sf::Int32  p2_kills;
		sf::Int32  p1_gold;
		sf::Int32  p2_gold;
		sf::Int32  p1_passiveGold;
		sf::Int32  p2_passiveGold;
	};

}