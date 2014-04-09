#pragma once
#include <SFML/Graphics.hpp>
#include "DrawableGameComponent.h"
#include "EnemyFab.h"
#include "Map.h"

using namespace sf;
using namespace std;
using namespace States;


	class WaveFabAllocator
	{
	public:
		WaveFabAllocator();
		DrawableGameComponent* buildFab(World::Map *map);
		EnemyFab* buildFab2(World::Map *map);


	};
