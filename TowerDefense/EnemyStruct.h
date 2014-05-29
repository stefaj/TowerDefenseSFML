#pragma once
#include "SFML\Network.hpp"
namespace Networking
{
	class EnemyStruct
	{
	public:
		EnemyStruct(){}

		int type_; //type and upgrade of enemy
		int owner_; //owner of the tower
		float x; //x position
		float y; //y position
	};

}