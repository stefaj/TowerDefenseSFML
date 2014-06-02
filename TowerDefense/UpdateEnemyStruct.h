#pragma once
#include "SFML\Network.hpp"
namespace Networking
{
	class UpdateEnemyStruct
	{
	public:
		UpdateEnemyStruct(){}

		sf::Int32 UID;
		float health;
		float x; 
		float y; 

	};

}