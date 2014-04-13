#pragma once
#include <string.h>

namespace Pathfinding
{
	class TileNode
	{
	public:
		TileNode();
		TileNode(int px, int py, TileNode *parentNode);
		float g;
		float h;
		int x;
		int y;

		//Types of tiles
		enum TILENODE_TYPES {FREE_PATH=0, WALL=1, START=5, END=6};

		int type;

		TileNode *parent;

		const int f();

	};
}