#pragma once
#include "SFML\Network.hpp"

namespace Networking
{
	struct ProjectileStruct
	{
	public:
		ProjectileStruct(){}

		float start_x;
		float start_y;
		float end_x;
		float end_y;
		sf::Int32 owner_;
		sf::Int32  damage;
		sf::Int32 towerLevel; //type
	};

}
